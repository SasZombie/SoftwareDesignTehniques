#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#include "headers/header.hpp"
#include "headers/context.hpp"

#define PORT 8080
#define MAX_CLIENTS 10

HTTPResponse handleRequest(const HTTPHeader &head)
{

    HttpRequestContext context(std::make_shared<LoggingObserver>());

    switch (head.type)
    {
    case HTTPMethods::GET:
        context.setHandler(std::make_shared<GetRequestHandler>());
        return context.processRequest(head);

    case HTTPMethods::POST:
        context.setHandler(std::make_shared<PostRequestHandler>());
        return context.processRequest(head);

    case HTTPMethods::DELETE:
        context.setHandler(std::make_shared<DeleteRequestHandler>());
        return context.processRequest(head);

    case HTTPMethods::HEAD:
        context.setHandler(std::make_shared<HeadRequestHandler>());
        return context.processRequest(head);

    default:
        std::cerr << "Unknonw TYPE\n";
        return HTTPResponse{};
    }
}
void handle_client(int client_socket)
{
    HTTPHeader head;
    while (true)
    {
        ssize_t valread = read(client_socket, &head, sizeof(HTTPHeader));

        if (valread <= 0)
        {
            std::cout << "Client disconnected.\n";
            return;
        }
        else
        {
            HTTPResponse response = handleRequest(head);

            send(client_socket, &response, sizeof(response), 0);            
        }

    }

    close(client_socket);
}

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cerr << "Socket creation failed: " << strerror(errno) << '\n';
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        std::cerr << "setsockopt failed: " << strerror(errno) << '\n';
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        std::cerr << "Bind failed: " << strerror(errno) << '\n';
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_CLIENTS) < 0)
    {
        std::cerr << "Listen failed: " << strerror(errno) << '\n';
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is listening on port " << PORT << '\n';

    std::vector<std::jthread> client_threads;

    while (true)
    {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            std::cerr << "Accept failed: " << strerror(errno) << '\n';
            exit(EXIT_FAILURE);
        }

        std::cout << "New client connected.\n";
        client_threads.push_back(std::jthread(handle_client, new_socket));
    }

    return 0;
}
