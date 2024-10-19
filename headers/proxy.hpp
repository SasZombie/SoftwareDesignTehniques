#pragma once
#include "strategy.hpp"

class AuthProxy : public HttpRequestHandler
{
private:
    std::shared_ptr<HttpRequestHandler> realStrategy;

public:
    AuthProxy(std::shared_ptr<HttpRequestHandler> strategy) noexcept;
    HTTPResponse handleRequest(const HTTPHeader&request) const noexcept override;
};
