#include <iostream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#include "headers/header.hpp"

#define PORT 8080

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "Socket creation failed\n";
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address or address not supported\n";
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Connection failed\n";
        return -1;
    }

    const std::string messageGet = "textfile1";
    const std::string messagePost = "textfile2";
    const std::string messageDelete = "a";
    const std::string messageHead = "textfile1";

    std::string msgs[] = {messageGet, messagePost, messageDelete, messageHead};
    HTTPMethods methods[] = {HTTPMethods::GET, HTTPMethods::POST, HTTPMethods::DELETE, HTTPMethods::HEAD};
    size_t results[] = {404, 200, 401, 404};
    size_t ind = 0;

    std::cout << "===============================\nExpected Rezult | Actual Rezult\n";

    while (ind < 4)
    {
        HTTPHeader head;
        head.type = methods[ind];
        head.length = msgs[ind].length();
        strncpy(head.message, msgs[ind].c_str(), sizeof(head.message) - 1);
        send(sock, &head, sizeof(head), 0);


        HTTPResponse response;

        ssize_t valread = read(sock, &response, sizeof(response));

        if (valread <= 0)
        {
            std::cout << "No Response\n";
        }
        else
        {
            size_t code = static_cast<size_t>(response.statusCode);
            std::cout << "+      " << results[ind] << "      |";
            std::cout << "      " << code << "    +";
            if(code == results[ind])
            {
                std::cout << "   ✓\n";
            }
            else
            {
                std::cout << "   x\n";
            }

        }
        ++ind;
    }
    std::cout << "===============================\n";

    close(sock);
    return 0;
}
