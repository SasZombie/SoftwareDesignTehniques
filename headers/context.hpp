#pragma once

#include "proxy.hpp"
#include "strategy.hpp"
#include "observer.hpp"

class HttpRequestContext
{
private:
    std::shared_ptr<HttpRequestHandler> handler;
    std::vector<std::shared_ptr<HttpRequestObserver>> observers;
    void notify(const std::string &request) const noexcept;

public:
    HttpRequestContext() noexcept = default;
    HttpRequestContext(const std::shared_ptr<LoggingObserver>& obs) noexcept;
    void setHandler(std::shared_ptr<HttpRequestHandler> handl) noexcept;
    HTTPResponse processRequest(const HTTPHeader &request) noexcept;
    void attach(const std::shared_ptr<HttpRequestObserver> &observer) noexcept;
    void detach(const std::shared_ptr<HttpRequestObserver> &observer) noexcept;
};