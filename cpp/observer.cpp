#include "../headers/observer.hpp"

void LoggingObserver::update(const std::string &request) const noexcept
{
    std::cout << "New entry: " << request << '\n';
}

void AutentificationObserver::update(const std::string &request) const noexcept
{
    std::cout << "Authentification request: " << request << '\n';
}

void ProblemObserver::update(const std::string &request) const noexcept
{
    std::ofstream file("Logs", std::ios::app);
    if(!file.is_open())
    {
        std::cerr << "Could not open log file!!!\n";
        return;
    }

    file << request;
    
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    file << "Action time: " << std::put_time(std::localtime(&currentTime), "%Y-%m-%d %H:%M:%S") << '\n';

    file.close();
}