#pragma once
#include <string>
#include <cstring>

enum class HTTPMethods{
    POST,
    GET,
    DELETE,
    HEAD
};

enum class StatusCode{
    OK = 200,
    CREATED = 201,
    ACCEPTED = 202,
    BAD_RESULT = 400,
    UNAUTHORIZED = 401,
    NOT_FOUND = 404
};

struct HTTPHeader
{
    HTTPMethods type;
    size_t length;
    char message[256];
};

struct HTTPResponse
{
    bool status;
    StatusCode statusCode;
    char message[256];
    char body[256];
};
