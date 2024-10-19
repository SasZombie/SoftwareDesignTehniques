#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include "header.hpp"
#include "factory.hpp"


class HttpRequestHandler
{
public:
    virtual ~HttpRequestHandler() noexcept = default;
    virtual HTTPResponse handleRequest(const HTTPHeader &request) const noexcept = 0;
};


class GetRequestHandler : public HttpRequestHandler
{

public:
    HTTPResponse handleRequest(const HTTPHeader &request) const noexcept override;
};


class PostRequestHandler : public HttpRequestHandler
{

public:
    HTTPResponse handleRequest(const HTTPHeader &request) const noexcept override;
};


class DeleteRequestHandler : public HttpRequestHandler
{

public:
    HTTPResponse handleRequest(const HTTPHeader &request) const noexcept override;
};


class HeadRequestHandler : public HttpRequestHandler
{

public:
    HTTPResponse handleRequest(const HTTPHeader &request) const noexcept override;
};
