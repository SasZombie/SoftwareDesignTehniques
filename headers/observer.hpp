#pragma once
#include <string>
#include <iostream>
#include <fstream>

class HttpRequestObserver
{
public:
    virtual ~HttpRequestObserver() noexcept = default;
    virtual void update(const std::string &request) const noexcept = 0;
};

class LoggingObserver : public HttpRequestObserver
{
public:
    void update(const std::string &request) const noexcept override;
};

class AutentificationObserver : public HttpRequestObserver
{
public:
    void update(const std::string &request) const noexcept override;
};

class ProblemObserver : public HttpRequestObserver
{
public:
    void update(const std::string &request) const noexcept override;
};
