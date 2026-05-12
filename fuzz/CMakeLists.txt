cmake_minimum_required(VERSION 3.20)

project(fuzzing_test_photogram)

set(TARGET_NAME fuzz_http)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")

add_link_options(/DEBUG)

#set paths
if (WIN32)
    set(DEV_ROOT c:/dev)
elseif(UNIX)
    set(DEV_ROOT /usr/lib)
else()
    message(FATAL_ERROR "Don't support this OS")
endif()
set(LIB_PLACE ${DEV_ROOT}/common)

#common find libs

#nlohmann_json
set(nlohmann_json_DIR ${LIB_PLACE}/json/build)
find_package(nlohmann_json 3.12.0 REQUIRED)

#src
get_filename_component(auth_src_dir "${CMAKE_SOURCE_DIR}/../../auth_server_src/" ABSOLUTE)
set(src_files       ${auth_src_dir}/HttpDef.hpp
                    ${auth_src_dir}/HttpParser.hpp
                    ${auth_src_dir}/HttpParser.cpp
                    ${auth_src_dir}/Request.hpp
                    ${auth_src_dir}/Request.cpp
                    ${auth_src_dir}/FormData.cpp
                    ${auth_src_dir}/FormData.hpp
)

set(tests ${CMAKE_SOURCE_DIR}/tests/fuzz_http.cpp)


source_group(TREE ${auth_src_dir} 
    PREFIX "src"
    FILES ${src_files}
)

source_group(TREE ${CMAKE_SOURCE_DIR}/tests 
    PREFIX "tests"
    FILES ${tests}
)

if(MSVC)
    get_filename_component(MSVC_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
    file(GLOB ASAN_DLL_TO_COPY "${MSVC_BIN_DIR}/clang_rt.asan_dynamic-x86_64.dll")
    file(COPY ${ASAN_DLL_TO_COPY} DESTINATION ${CMAKE_BINARY_DIR}/Release)
endif()


enable_testing()

add_executable(${TARGET_NAME} ${tests} ${src_files})
target_compile_options(${TARGET_NAME} PRIVATE /fsanitize=fuzzer /fsanitize=address)

target_include_directories(${TARGET_NAME} PRIVATE ${auth_src_dir})

target_link_libraries(
    ${TARGET_NAME}
    PRIVATE
    nlohmann_json::nlohmann_json
)
