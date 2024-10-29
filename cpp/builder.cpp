#include "../headers/builder.hpp"

HTTPResponse ResponseBuilder::build() const noexcept
{
    return this->response;
}

ResponseBuilder& ResponseBuilder::setBody(const std::string& message) noexcept
{
    std::strncpy(this->response.body, message.c_str(), sizeof(response.body));

    return *this;
}

ResponseBuilder& ResponseBuilder::setMessage(const std::string& message) noexcept
{
    std::strncpy(this->response.message, message.c_str(), sizeof(response.message));

    return *this;
}

ResponseBuilder& ResponseBuilder::setStatus(bool status) noexcept
{
    this->response.status = status;
    return *this;
}

ResponseBuilder& ResponseBuilder::setStatusCode(StatusCode code) noexcept
{
    this->response.statusCode = code;
    return *this;
}

HTTPResponse createResponse(StatusCode code, const std::string& message) noexcept
{

    HTTPResponse response;
    ResponseBuilder builder;

    switch (code)
    {
    case StatusCode::OK:
        response = builder.setBody(message).setMessage("OK").setStatus(true).setStatusCode(code).build();
        break;

    case StatusCode::ACCEPTED:
        response = builder.setBody(message).setMessage("Accepted").setStatus(true).setStatusCode(code).build();
        break;

    case StatusCode::CREATED:
        response = builder.setBody(message).setMessage("Created").setStatus(true).setStatusCode(code).build();
        break;

    case StatusCode::BAD_RESULT:
        response = builder.setBody(message).setMessage("Bad Result").setStatus(false).setStatusCode(code).build();
        break;

    case StatusCode::UNAUTHORIZED:
        response = builder.setBody(message).setMessage("Unauthorized").setStatus(false).setStatusCode(code).build();
        break;

    case StatusCode::NOT_FOUND:
        response = builder.setBody(message).setMessage("Not Found").setStatus(false).setStatusCode(code).build();
        break;

    default:
        response = builder.setBody(message).setMessage("Unknown").setStatus(false).setStatusCode(code).build();
        break;
    }

    return response;
}