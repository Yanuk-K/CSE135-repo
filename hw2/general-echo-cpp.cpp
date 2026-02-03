#include <iostream>
#include <cstdlib>
#include <string>

int main()
{
    // HTTP headers
    std::cout << "Cache-Control: no-cache\n";
    std::cout << "Content-Type: text/html\n\n";

    // HTML top
    std::cout << "<!DOCTYPE html>\n";
    std::cout << "<html><head><title>General Request Echo</title></head>\n";
    std::cout << "<body><h1 align='center'>General Request Echo</h1><hr>\n";

    const char *protocol = getenv("SERVER_PROTOCOL");
    const char *method = getenv("REQUEST_METHOD");
    const char *query = getenv("QUERY_STRING");
    const char *length = getenv("CONTENT_LENGTH");

    std::cout << "<p><b>HTTP Protocol:</b> "
              << (protocol ? protocol : "N/A") << "</p>\n";

    std::cout << "<p><b>HTTP Method:</b> "
              << (method ? method : "N/A") << "</p>\n";

    std::cout << "<p><b>Query String:</b> "
              << (query ? query : "N/A") << "</p>\n";

    // Read msg from string if existed.
    int len = length ? atoi(length) : 0;
    std::string body;

    for (int i = 0; i < len; i++)
    {
        char c;
        std::cin.get(c);
        body += c;
    }

    std::cout << "<p><b>Message Body:</b> " << body << "</p>\n";

    // HTML bottom
    std::cout << "</body></html>\n";
    return 0;
}
