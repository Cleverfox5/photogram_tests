#include "HttpParser.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    try
    {
        std::string request{ reinterpret_cast<const char*>(data), size };
        HttpParser::http_types_info info_block;
        HttpParser::parse(request, info_block);
    }
    catch(std::exception&){}
        
    return 0;
}
