#include "../headers/context.hpp"

HttpRequestContext::HttpRequestContext(const std::shared_ptr<LoggingObserver>& obs) noexcept
{
    observers.push_back(obs);
}


HTTPResponse HttpRequestContext::processRequest(const HTTPHeader &request) noexcept
{
    static const auto auth = std::make_shared<AutentificationObserver>();
    static const auto problemLogger = std::make_shared<ProblemObserver>();

    HTTPResponse response;

    if (this->handler)
    {
        if (std::dynamic_pointer_cast<GetRequestHandler>(handler) || std::dynamic_pointer_cast<DeleteRequestHandler>(handler))
        {
            attach(auth);
            AuthProxy prox(handler);
            response = prox.handleRequest(request);
            notify("Cliend used service\n");
            detach(auth);
        }
        else
        {
            response = handler->handleRequest(request);
            notify("Cliend used service\n");
        }

        if(response.statusCode == StatusCode::UNAUTHORIZED)
        {
            attach(problemLogger);

            notify("Someone tried to access while UNAUTHORIZED\nThis issue will be reposted\n");

            detach(problemLogger);
        }
    }
    else
    {
        std::cerr << "No handler set! Skipping...\n";
    }

    return response;
}

void HttpRequestContext::setHandler(std::shared_ptr<HttpRequestHandler> handl) noexcept
{
    this->handler = std::move(handl);
}
void HttpRequestContext::attach(const std::shared_ptr<HttpRequestObserver> &observer) noexcept
{
    observers.push_back(observer);
}
void HttpRequestContext::detach(const std::shared_ptr<HttpRequestObserver> &observer) noexcept
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}
void HttpRequestContext::notify(const std::string &request) const noexcept
{
    for (const auto &observer : observers)
    {
        observer->update(request);
    }
}