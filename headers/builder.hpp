#pragma once

#include "header.hpp"

// bool status;
// StatusCode statusCode;
// char message[256];
// char body[256];
    
class ResponseBuilder
{
private: 
    HTTPResponse response;

public:
    HTTPResponse build() const noexcept;
    ResponseBuilder& setStatus(bool status) noexcept;
    ResponseBuilder& setStatusCode(StatusCode statusCode) noexcept;
    ResponseBuilder& setMessage(const std::string& message) noexcept;
    ResponseBuilder& setBody(const std::string& body) noexcept;

};

HTTPResponse createResponse(StatusCode code, const std::string& message = "") noexcept;