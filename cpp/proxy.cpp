#include "../headers/proxy.hpp"

AuthProxy::AuthProxy(std::shared_ptr<HttpRequestHandler> strategy) noexcept
    : realStrategy(std::move(strategy)) {}

HTTPResponse AuthProxy::handleRequest(const HTTPHeader &request) const noexcept
{
    if(request.length > 5)
    {
        return realStrategy->handleRequest(request);
    }   
    return createResponse(StatusCode::UNAUTHORIZED);
}