#include "../headers/factory.hpp"

HTTPResponse createResponse(StatusCode code, const std::string &message) noexcept
{
    HTTPResponse response;

    response.statusCode = code;
    switch (code)
    {
    case StatusCode::OK:
        response.status = true;
        std::strncpy(response.message, "OK", sizeof(response.message));
        std::strncpy(response.body, message.c_str(), sizeof(response.body));
        break;

    case StatusCode::ACCEPTED:
        response.status = true;
        std::strncpy(response.message, "Accepted", sizeof(response.message));
        std::strncpy(response.body, message.c_str(), sizeof(response.body));
        break;

    case StatusCode::CREATED:
        response.status = true;
        std::strncpy(response.message, "Created", sizeof(response.message));
        std::strncpy(response.body, message.c_str(), sizeof(response.body));
        break;

    case StatusCode::BAD_RESULT:
        response.status = false;
        std::strncpy(response.message, "Bad Result", sizeof(response.message));
        std::strncpy(response.body, message.c_str(), sizeof(response.body));
        break;

    case StatusCode::UNAUTHORIZED:
        response.status = false;
        std::strncpy(response.message, "Unauthorized", sizeof(response.message));
        std::strncpy(response.body, message.c_str(), sizeof(response.body));
        break;

    case StatusCode::NOT_FOUND:
        response.status = false;
        std::strncpy(response.message, "Not Found", sizeof(response.message));
        std::strncpy(response.body, message.c_str(), sizeof(response.body));
        break;

    default:
        response.status = false;
        std::strncpy(response.message, "Unknown", sizeof(response.message));
        std::strncpy(response.body, message.c_str(), sizeof(response.body));
        break;
    }

    return response;
}