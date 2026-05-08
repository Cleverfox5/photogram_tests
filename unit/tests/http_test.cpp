#include <gtest/gtest.h>
#include "HttpParser.hpp"
#include <nlohmann/json.hpp>

//OPTIONS

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

//POST

TEST(HttpPost, Login)
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

    auto& post_block = std::get<HttpParser::post_t_info>(info_block);
    EXPECT_EQ(post_block.msg, HttpParser::e_post_msg::login);
    EXPECT_EQ(post_block.origin, " http://localhost:3000");
    EXPECT_EQ(post_block.jsonBody["login"], "Utiho03@mail.ru");
    EXPECT_EQ(post_block.jsonBody["password"], "Utiho123");
}

TEST(HttpPost, updateProfileData)
{
    
    std::string http_request =
        "POST /updateProfileData HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n"
        "Content-Length: 137\r\n"
        "sec-ch-ua-platform: \"Windows\"\r\n"
        "Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3NzgyNDczNzQsImlhdCI6MTc3ODI0NjQ3NCwiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjQzIn0._wz-2xKXBH3YNs2Bd1lSQGZNjiv8bU1XFpKVKec9acE\r\n"
        "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/148.0.0.0 Safari/537.36\r\n"
        "sec-ch-ua: \"Chromium\";v=\"148\", \"Google Chrome\";v=\"148\", \"Not/A)Brand\";v=\"99\"\r\n"
        "Content-Type: text/plain;charset=UTF-8\r\n"
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
        "{\"firstname\":\"Sjoijdf\",\"lastname\":\"sdfsdf\",\"is_male\":\"false\",\"birthdate\":\"1984-12-23\",\"nickname\":\"cvdvsddvs\",\"email\":\"soadifjas@mail.ru\"}";
        
    HttpParser::http_types_info info_block;
    HttpParser::parse(http_request, info_block);
    auto& post_block = std::get<HttpParser::post_t_info>(info_block);

    EXPECT_EQ(post_block.msg, HttpParser::e_post_msg::update_profile_data);
    EXPECT_EQ(post_block.accessToken, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3NzgyNDczNzQsImlhdCI6MTc3ODI0NjQ3NCwiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjQzIn0._wz-2xKXBH3YNs2Bd1lSQGZNjiv8bU1XFpKVKec9acE");
    EXPECT_EQ(post_block.jsonBody["firstname"], "Sjoijdf");
    EXPECT_EQ(post_block.jsonBody["lastname"], "sdfsdf");
    EXPECT_EQ(post_block.jsonBody["is_male"], "false");
    EXPECT_EQ(post_block.jsonBody["birthdate"], "1984-12-23");
    EXPECT_EQ(post_block.jsonBody["nickname"], "cvdvsddvs");
    EXPECT_EQ(post_block.jsonBody["email"], "soadifjas@mail.ru");
}

TEST(HttpPost, updateProfilePassword)
{

    std::string http_request =
        "POST /updateProfilePassword HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n"
        "Content-Length: 99\r\n"
        "sec-ch-ua-platform: \"Windows\"\r\n"
        "Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3NzgyNDczNzQsImlhdCI6MTc3ODI0NjQ3NCwiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjQzIn0._wz-2xKXBH3YNs2Bd1lSQGZNjiv8bU1XFpKVKec9acE\r\n"
        "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/148.0.0.0 Safari/537.36\r\n"
        "sec-ch-ua: \"Chromium\";v=\"148\", \"Google Chrome\";v=\"148\", \"Not/A)Brand\";v=\"99\"\r\n"
        "Content-Type: text/plain;charset=UTF-8\r\n"
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
        "\"$argon2id$v=19$m=65536,t=2,p=1$5tFhiruB/6H452uV6S6E8A$/ovZUg2h1ZOiyQk6GIjbI2sO1CNbwgF9haNv5x3KsKQ\"";

    HttpParser::http_types_info info_block;
    HttpParser::parse(http_request, info_block);
    auto& post_block = std::get<HttpParser::post_t_info>(info_block);

    EXPECT_EQ(post_block.msg, HttpParser::e_post_msg::update_profile_password);
    EXPECT_EQ(post_block.accessToken, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3NzgyNDczNzQsImlhdCI6MTc3ODI0NjQ3NCwiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjQzIn0._wz-2xKXBH3YNs2Bd1lSQGZNjiv8bU1XFpKVKec9acE");
    EXPECT_EQ(post_block.jsonBody.get<std::string>(), "$argon2id$v=19$m=65536,t=2,p=1$5tFhiruB/6H452uV6S6E8A$/ovZUg2h1ZOiyQk6GIjbI2sO1CNbwgF9haNv5x3KsKQ");
}

TEST(HttpPost, updateProfilePhoto)
{
    std::string http_request =
        "POST /updateProfilePhoto HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n"
        "Content-Length: 200\r\n"
        "sec-ch-ua-platform: \"Windows\"\r\n"
        "Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3NzgyNTAyOTMsImlhdCI6MTc3ODI0OTM5MywiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjQzIn0.tivzeYhDj-jl7-Jby9UBhBHs5sAH7zeYEpjS7mfqi3U\r\n"
        "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/148.0.0.0 Safari/537.36\r\n"
        "sec-ch-ua: \"Chromium\";v=\"148\", \"Google Chrome\";v=\"148\", \"Not/A)Brand\";v=\"99\"\r\n"
        "Content-Type: multipart/form-data; boundary=----WebKitFormBoundaryvjxERkgguZ8Se3Df\r\n"
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
        "------WebKitFormBoundaryvjxERkgguZ8Se3Df\r\n"
        "Content-Disposition: form-data; name=\"photo\"; filename=\"R1-06122-035A.JPG\"\r\n"
        "Content-Type: image/jpeg\r\n"
        "\r\n"
        "RIFFl-----\r\n"
        "------WebKitFormBoundaryvjxERkgguZ8Se3Df--";

    HttpParser::http_types_info info_block;
    HttpParser::parse(http_request, info_block);
    auto& post_block = std::get<HttpParser::post_t_info>(info_block);
    EXPECT_EQ(post_block.accessToken, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3NzgyNTAyOTMsImlhdCI6MTc3ODI0OTM5MywiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjQzIn0.tivzeYhDj-jl7-Jby9UBhBHs5sAH7zeYEpjS7mfqi3U");
    EXPECT_NE(post_block.filesCoordinates.find("R1-06122-035A.JPG"), post_block.filesCoordinates.end());
    EXPECT_EQ(post_block.binaryData.size(), 10);
}

TEST(HttpPost, registration)
{
    std::string http_request =
        "POST /registration HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n"
        "Content-Length: 1032\r\n"
        "sec-ch-ua-platform: \"Windows\"\r\n"
        "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/148.0.0.0 Safari/537.36\r\n"
        "sec-ch-ua: \"Chromium\";v=\"148\", \"Google Chrome\";v=\"148\", \"Not/A)Brand\";v=\"99\"\r\n"
        "Content-Type: multipart/form-data; boundary=----WebKitFormBoundaryDwN0hPrTSunu0hxw\r\n"
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
        "------WebKitFormBoundaryDwN0hPrTSunu0hxw\r\n"
        "Content-Disposition: form-data; name=\"first_name\"\r\n"
        "\r\n"
        "FDdvd\r\n"
        "------WebKitFormBoundaryDwN0hPrTSunu0hxw\r\n"
        "Content-Disposition: form-data; name=\"last_name\"\r\n"
        "\r\n"
        "fdsffDfv\r\n"
        "------WebKitFormBoundaryDwN0hPrTSunu0hxw\r\n"
        "Content-Disposition: form-data; name=\"is_male\"\r\n"
        "\r\n"
        "true\r\n"
        "------WebKitFormBoundaryDwN0hPrTSunu0hxw\r\n"
        "Content-Disposition: form-data; name=\"birthdate\"\r\n"
        "\r\n"
        "2023-05-12\r\n"
        "------WebKitFormBoundaryDwN0hPrTSunu0hxw\r\n"
        "Content-Disposition: form-data; name=\"nickname\"\r\n"
        "\r\n"
        "SFfFwedffdfd\r\n"
        "------WebKitFormBoundaryDwN0hPrTSunu0hxw\r\n"
        "Content-Disposition: form-data; name=\"email\"\r\n"
        "\r\n"
        "SFfFwedffdfd2023@gmail.com\r\n"
        "------WebKitFormBoundaryDwN0hPrTSunu0hxw\r\n"
        "Content-Disposition: form-data; name=\"password\"\r\n"
        "\r\n"
        "$argon2id$v=19$m=65536,t=2,p=1$7aC29UTQeBcSOq3Kdq5E6g$/0JVfN9Wq8y3qWAkKMobM8V+PM7jDUyv59vOdtEjBdg\r\n"
        "------WebKitFormBoundaryDwN0hPrTSunu0hxw\r\n"
        "Content-Disposition: form-data; name=\"photo\"; filename=\"R1-06122-000A_0001.JPG\"\r\n"
        "Content-Type: image/jpeg\r\n"
        "\r\n"
        "RIFFЉ`jdlf\r\n"
        "------WebKitFormBoundaryDwN0hPrTSunu0hxw--";

    HttpParser::http_types_info info_block;
    HttpParser::parse(http_request, info_block);
    auto& post_block = std::get<HttpParser::post_t_info>(info_block);

    // Проверка текстовых полей
    EXPECT_EQ(post_block.msg, HttpParser::e_post_msg::registration);
    EXPECT_EQ(post_block.userProperties["first_name"], "FDdvd");
    EXPECT_EQ(post_block.userProperties["last_name"], "fdsffDfv");
    EXPECT_EQ(post_block.userProperties["is_male"], "true");
    EXPECT_EQ(post_block.userProperties["birthdate"], "2023-05-12");
    EXPECT_EQ(post_block.userProperties["nickname"], "SFfFwedffdfd");
    EXPECT_EQ(post_block.userProperties["email"], "SFfFwedffdfd2023@gmail.com");
    EXPECT_EQ(post_block.userProperties["password"], "$argon2id$v=19$m=65536,t=2,p=1$7aC29UTQeBcSOq3Kdq5E6g$/0JVfN9Wq8y3qWAkKMobM8V+PM7jDUyv59vOdtEjBdg");


    EXPECT_NE(post_block.filesCoordinates.find("R1-06122-000A_0001.JPG"), post_block.filesCoordinates.end());
    EXPECT_EQ(post_block.binaryData.size(), 10);
}

//GET

TEST(HttpGet, getNewToken)
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
        "Cookie: refreshToken=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3Nzg4NTQ4OTYsImlhdCI6MTc3ODI1MDA5NiwiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjQzIn0.UBC9wTiSoc2hTYQyR5QTHtd3PT3ZKdY6u7T1mN16WpM\r\n"
        "\r\n";

    HttpParser::http_types_info info_block;
    HttpParser::parse(http_request, info_block);

    ASSERT_TRUE(std::holds_alternative<HttpParser::get_t_info>(info_block));

    auto& get_block = std::get<HttpParser::get_t_info>(info_block);
    EXPECT_EQ(get_block.msg, HttpParser::e_get_msg::get_new_token);
    EXPECT_EQ(get_block.origin, " http://localhost:3000");
    EXPECT_EQ(get_block.refreshToken, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3Nzg4NTQ4OTYsImlhdCI6MTc3ODI1MDA5NiwiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjQzIn0.UBC9wTiSoc2hTYQyR5QTHtd3PT3ZKdY6u7T1mN16WpM");

}

TEST(HttpGet, getPhotoById)
{
    std::string http_request =
        "GET /getPhotoById?photo_id=21 HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n"
        "sec-ch-ua-platform: \"Windows\"\r\n"
        "Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3NzgwMzMyODQsImlhdCI6MTc3ODAzMjM4NCwiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjI5In0.isos0P-bVA1Y3iD6p-NMrhdejo13_RSeXZizkcwupfo\r\n"
        "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/147.0.0.0 Safari/537.36\r\n"
        "sec-ch-ua: \"Google Chrome\";v=\"147\", \"Not.A/Brand\";v=\"8\", \"Chromium\";v=\"147\"\r\n"
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
    EXPECT_EQ(get_block.msg, HttpParser::e_get_msg::get_photo_by_id);
    EXPECT_EQ(get_block.origin, " http://localhost:3000");
    EXPECT_EQ(get_block.accessToken, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3NzgwMzMyODQsImlhdCI6MTc3ODAzMjM4NCwiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjI5In0.isos0P-bVA1Y3iD6p-NMrhdejo13_RSeXZizkcwupfo");
    EXPECT_EQ(get_block.properties["photo_id"], "21");

}

TEST(HttpGet, getUsersList)
{
    std::string http_request =
        "GET /getUsersList?substr=na&LIMIT=5&OFFSET=0 HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n"
        "sec-ch-ua-platform: \"Windows\"\r\n"
        "Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3NzgyNDU3MTUsImlhdCI6MTc3ODI0NDgxNSwiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjI5In0.iglJmHu7DHHDjuWJIl_yNxc28JN0K9Z3ri6Vf3rwlrY\r\n"
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
    EXPECT_EQ(get_block.msg, HttpParser::e_get_msg::get_users_list);
    EXPECT_EQ(get_block.accessToken, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3NzgyNDU3MTUsImlhdCI6MTc3ODI0NDgxNSwiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjI5In0.iglJmHu7DHHDjuWJIl_yNxc28JN0K9Z3ri6Vf3rwlrY");
    EXPECT_EQ(get_block.properties["substr"], "na");
    EXPECT_EQ(get_block.properties["LIMIT"], "5");
    EXPECT_EQ(get_block.properties["OFFSET"], "0");
}

TEST(HttpGet, makeFriend)
{
    std::string http_request =
        "GET /makeFriend?friend_id=18 HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n"
        "sec-ch-ua-platform: \"Windows\"\r\n"
        "Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3NzgyNDYxNTgsImlhdCI6MTc3ODI0NTI1OCwiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjQzIn0.bjvHuqMAhdv4MXJ2ETTEMWmak7vWP_wBfbnXbBKhQCU\r\n"
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
    EXPECT_EQ(get_block.msg, HttpParser::e_get_msg::make_friend);
    EXPECT_EQ(get_block.accessToken, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3NzgyNDYxNTgsImlhdCI6MTc3ODI0NTI1OCwiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjQzIn0.bjvHuqMAhdv4MXJ2ETTEMWmak7vWP_wBfbnXbBKhQCU");
    EXPECT_EQ(get_block.origin, " http://localhost:3000");
    EXPECT_EQ(get_block.properties["friend_id"], "18");
}

TEST(HttpGet, getProfileByNickname)
{
    std::string http_request =
        "GET /getProfileByNickname?nickname=cvdvsddvs HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n"
        "sec-ch-ua-platform: \"Windows\"\r\n"
        "Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3NzgyNDYxNTgsImlhdCI6MTc3ODI0NTI1OCwiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjQzIn0.bjvHuqMAhdv4MXJ2ETTEMWmak7vWP_wBfbnXbBKhQCU\r\n"
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
    EXPECT_EQ(get_block.msg, HttpParser::e_get_msg::get_profile_by_nickname);
    EXPECT_EQ(get_block.accessToken, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3NzgyNDYxNTgsImlhdCI6MTc3ODI0NTI1OCwiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjQzIn0.bjvHuqMAhdv4MXJ2ETTEMWmak7vWP_wBfbnXbBKhQCU");
    EXPECT_EQ(get_block.origin, " http://localhost:3000");
    EXPECT_EQ(get_block.properties["nickname"], "cvdvsddvs");
}

TEST(HttpGet, getProfilePhoto)
{
    std::string http_request =
        "GET /getProfilePhoto?nickname=cvdvsddvs HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n"
        "sec-ch-ua-platform: \"Windows\"\r\n"
        "Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3NzgyNDY4OTEsImlhdCI6MTc3ODI0NTk5MSwiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjQzIn0.g7jonjvwj26LWsFge6BL9K2dz8_DnrqcSea75hlg7Gc\r\n"
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
    EXPECT_EQ(get_block.msg, HttpParser::e_get_msg::get_profile_photo);
    EXPECT_EQ(get_block.accessToken, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3NzgyNDY4OTEsImlhdCI6MTc3ODI0NTk5MSwiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjQzIn0.g7jonjvwj26LWsFge6BL9K2dz8_DnrqcSea75hlg7Gc");
    EXPECT_EQ(get_block.origin, " http://localhost:3000");
    EXPECT_EQ(get_block.properties["nickname"], "cvdvsddvs");
}


TEST(HttpGet, deleteFriend)
{
    std::string http_request =
        "GET /deleteFriend?friend_id=18 HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n"
        "sec-ch-ua-platform: \"Windows\"\r\n"
        "Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3NzgyNDY4OTEsImlhdCI6MTc3ODI0NTk5MSwiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjQzIn0.g7jonjvwj26LWsFge6BL9K2dz8_DnrqcSea75hlg7Gc\r\n"
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
    EXPECT_EQ(get_block.msg, HttpParser::e_get_msg::delete_friend);
    EXPECT_EQ(get_block.accessToken, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3NzgyNDY4OTEsImlhdCI6MTc3ODI0NTk5MSwiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjQzIn0.g7jonjvwj26LWsFge6BL9K2dz8_DnrqcSea75hlg7Gc");
    EXPECT_EQ(get_block.origin, " http://localhost:3000");
    EXPECT_EQ(get_block.properties["friend_id"], "18");
}

TEST(HttpGet, getStatus)
{
    std::string http_request =
        "GET /getStatus?id_user=43 HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n"
        "sec-ch-ua-platform: \"Windows\"\r\n"
        "Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3NzgyNDczNzQsImlhdCI6MTc3ODI0NjQ3NCwiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjQzIn0._wz-2xKXBH3YNs2Bd1lSQGZNjiv8bU1XFpKVKec9acE\r\n"
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
    EXPECT_EQ(get_block.msg, HttpParser::e_get_msg::get_status);
    EXPECT_EQ(get_block.accessToken, "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXUyJ9.eyJleHAiOjE3NzgyNDczNzQsImlhdCI6MTc3ODI0NjQ3NCwiaXNzIjoiUGhvdG9ncmFtQXV0aCIsInN1YiI6IjQzIn0._wz-2xKXBH3YNs2Bd1lSQGZNjiv8bU1XFpKVKec9acE");
    EXPECT_EQ(get_block.origin, " http://localhost:3000");
    EXPECT_EQ(get_block.properties["id_user"], "43");
}
