#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <map>

int main()
{
    // HTTP headers
    std::cout << "Cache-Control: no-cache\n";
    std::cout << "Content-Type: text/html\n\n";

    // HTML top
    std::cout << "<!DOCTYPE html>\n";
    std::cout << "<html><head><title>POST Request Echo</title></head>\n";
    std::cout << "<body><h1 align='center'>POST Request Echo</h1><hr>\n";

    // Read CONTENT_LENGTH
    const char *content_length = getenv("CONTENT_LENGTH");

    if (content_length)
    {
        int len = atoi(content_length);
        std::string body;

        // Read POST body from stdin
        for (int i = 0; i < len; i++)
        {
            char c;
            std::cin.get(c);
            body += c;
        }

        std::cout << "<b>Message Body:</b><br />\n";
        std::cout << "<ul>\n";

        // Parsing the msg which contains with key and value parameters.
        std::stringstream ss(body);
        std::string pair;

        while (std::getline(ss, pair, '&'))
        {
            size_t eq = pair.find('=');
            if (eq != std::string::npos)
            {
                std::string key = pair.substr(0, eq);
                std::string value = pair.substr(eq + 1);
                std::cout << "<li>" << key << " = " << value << "</li>\n";
            }
        }

        std::cout << "</ul>\n";
    }
    else
    {
        std::cout << "<b>Message Body:</b><br />\n<ul></ul>\n";
    }

    // HTML bottom
    std::cout << "</body></html>\n";
    return 0;
}