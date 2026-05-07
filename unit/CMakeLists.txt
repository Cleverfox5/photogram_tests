cmake_minimum_required(VERSION 3.20)

project(unit_test_photogram)

set(TARGET_NAME http_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

#google_tests
set(GTest_ROOT ${LIB_PLACE}/googletest/lib/cmake/GTest)
find_package(GTest REQUIRED)

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
)

set(tests ${CMAKE_SOURCE_DIR}/tests/http_test.cpp)


source_group(TREE ${auth_src_dir} 
    PREFIX "src"
    FILES ${src_files}
)

source_group(TREE ${CMAKE_SOURCE_DIR}/tests 
    PREFIX "tests"
    FILES ${tests}
)


enable_testing()

add_executable(${TARGET_NAME} ${tests} ${src_files})

target_include_directories(${TARGET_NAME} PRIVATE ${auth_src_dir})

target_link_libraries(
    ${TARGET_NAME}
    PRIVATE
    GTest::gtest_main
    nlohmann_json::nlohmann_json
)
