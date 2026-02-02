#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
    // HTTP headers (CGI)
    std::cout << "Cache-Control: no-cache\r\n";
    std::cout << "Content-Type: text/html\r\n\r\n";

    // HTML start
    std::cout << "<!DOCTYPE html>\n";
    std::cout << "<html>\n";
    std::cout << "<head>\n";
    std::cout << "<title>Hello CGI World</title>\n";
    std::cout << "</head>\n";
    std::cout << "<body>\n";

    std::cout << "<h1 align='center'>Hello HTML World</h1><hr/>\n";
    std::cout << "<h3>C++ Hello World by Yeunwook and Kevin</h3>\n";
    std::cout << "<p>Hello World</p>\n";
    std::cout << "<p>This page was generated with the C++ programming language</p>\n";

    // Time
    std::time_t now = std::time(nullptr);
    std::cout << "<p>This program was generated at: " << std::ctime(&now) << "</p>\n";

    // IP Address
    const char *address = std::getenv("REMOTE_ADDR");
    if (!address)
        address = "Unknown";
    std::cout << "<p>Your current IP Address is: " << address << "</p>\n";

    // HTML end
    std::cout << "</body>\n";
    std::cout << "</html>\n";

    return 0;
}