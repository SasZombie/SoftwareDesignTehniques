#include "../headers/strategy.hpp"

HTTPResponse GetRequestHandler::handleRequest(const HTTPHeader &request) const noexcept
{
    std::ifstream file(request.message);

    if (!file.is_open())
    {
        return createResponse(StatusCode::NOT_FOUND);
    }

    std::string stream;

    std::getline(file, stream);

    file.close();

    return createResponse(StatusCode::OK, stream);
}

HTTPResponse PostRequestHandler::handleRequest(const HTTPHeader &request) const noexcept
{
    std::ofstream file(request.message);

    if (!file.is_open())
    {
        return createResponse(StatusCode::NOT_FOUND);
    }

    file << request.message;
    file.close();

    return createResponse(StatusCode::OK);
}

HTTPResponse DeleteRequestHandler::handleRequest(const HTTPHeader &request) const noexcept
{
    if (remove(request.message) == 0)
    {
        return createResponse(StatusCode::OK);
    }

    return createResponse(StatusCode::NOT_FOUND);
}

HTTPResponse HeadRequestHandler::handleRequest(const HTTPHeader &request) const noexcept
{
    std::ifstream file(request.message);

    if (!file.is_open())
    {
        return createResponse(StatusCode::NOT_FOUND);
    }

    std::string stream;
    std::getline(file, stream);

    file.close();

    return createResponse(StatusCode::OK);
}