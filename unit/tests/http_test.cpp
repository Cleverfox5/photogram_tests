#include <gtest/gtest.h>
#include "HttpParser.hpp"


TEST(HttpOptions, Basic) 
{
    std::string http_request =
        "OPTIONS /login HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n"
        "Accept: */*\r\n"
        "Access-Control-Request-Method: POST\r\n"
        "Access-Control-Request-Headers: content-type\r\n"
        "Origin: http://localhost:3000\r\n"
        "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/147.0.0.0 Safari/537.36\r\n"
        "Sec-Fetch-Mode: cors\r\n"
        "Sec-Fetch-Site: same-site\r\n"
        "Sec-Fetch-Dest: empty\r\n"
        "Referer: http://localhost:3000/\r\n"
        "Accept-Encoding: gzip, deflate, br, zstd\r\n"
        "Accept-Language: ru-RU,ru;q=0.9,en-US;q=0.8,en;q=0.7\r\n"
        "\r\n";

    HttpParser::http_types_info info_block;
    HttpParser::parse(http_request, info_block);

    ASSERT_TRUE(std::holds_alternative<HttpParser::options_t_info>(info_block));

    auto& option_block = std::get<HttpParser::options_t_info>(info_block);
    EXPECT_EQ(option_block.origin, " http://localhost:3000");

}


TEST(HttpPost, login)
{
    std::string http_request =
        "POST /login HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n"
        "Content-Length: 49\r\n"
        "sec-ch-ua-platform: \"Windows\"\r\n"
        "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/147.0.0.0 Safari/537.36\r\n"
        "sec-ch-ua: \"Google Chrome\";v=\"147\", \"Not.A/Brand\";v=\"8\", \"Chromium\";v=\"147\"\r\n"
        "Content-Type: application/json\r\n"
        "sec-ch-ua-mobile: ?0\r\n"
        "Accept: */*\r\n"
        "Origin: http://localhost:3000\r\n"
        "Sec-Fetch-Site: same-site\r\n"
        "Sec-Fetch-Mode: cors\r\n"
        "Sec-Fetch-Dest: empty\r\n"
        "Referer: http://localhost:3000/\r\n"
        "Accept-Encoding: gzip, deflate, br, zstd\r\n"
        "Accept-Language: ru-RU,ru;q=0.9,en-US;q=0.8,en;q=0.7\r\n"
        "\r\n"
        "{\"login\":\"Utiho03@mail.ru\",\"password\":\"Utiho123\"}";

    HttpParser::http_types_info info_block;
    HttpParser::parse(http_request, info_block);

    ASSERT_TRUE(std::holds_alternative<HttpParser::post_t_info>(info_block));

    auto& option_block = std::get<HttpParser::post_t_info>(info_block);
    EXPECT_EQ(option_block.msg, HttpParser::e_post_msg::login);
    EXPECT_EQ(option_block.origin, " http://localhost:3000");
    EXPECT_EQ(option_block.jsonBody["login"], "Utiho03@mail.ru");
    EXPECT_EQ(option_block.jsonBody["password"], "Utiho123");
}

TEST(HttpGet, get_new_token)
{
    std::string http_request =
        "GET /getNewToken HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n"
        "sec-ch-ua-platform: \"Windows\"\r\n"
        "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/148.0.0.0 Safari/537.36\r\n"
        "sec-ch-ua: \"Chromium\";v=\"148\", \"Google Chrome\";v=\"148\", \"Not/A)Brand\";v=\"99\"\r\n"
        "sec-ch-ua-mobile: ?0\r\n"
        "Accept: */*\r\n"
        "Origin: http://localhost:3000\r\n"
        "Sec-Fetch-Site: same-site\r\n"
        "Sec-Fetch-Mode: cors\r\n"
        "Sec-Fetch-Dest: empty\r\n"
        "Referer: http://localhost:3000/\r\n"
        "Accept-Encoding: gzip, deflate, br, zstd\r\n"
        "Accept-Language: ru-RU,ru;q=0.9,en-US;q=0.8,en;q=0.7\r\n"
        "\r\n";

    HttpParser::http_types_info info_block;
    HttpParser::parse(http_request, info_block);

    ASSERT_TRUE(std::holds_alternative<HttpParser::get_t_info>(info_block));

    auto& get_block = std::get<HttpParser::get_t_info>(info_block);
    EXPECT_EQ(get_block.msg, HttpParser::e_get_msg::get_new_token);
    EXPECT_EQ(get_block.origin, " http://localhost:3000");
}

