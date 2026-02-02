#include <iostream>
#include <cstdlib>
#include <string>

int main()
{
    // HTTP headers
    std::cout << "Cache-Control: no-cache\n";
    std::cout << "Content-Type: text/html\n\n";

    std::cout << "<!DOCTYPE html><html><head><title>GET Echo</title></head><body>";
    std::cout << "<h1 align='center'>GET Request Echo</h1><hr>";

    const char *query = getenv("QUERY_STRING");
    if (!query)
        query = "";

    std::cout << "<b>Raw Query String:</b> " << query << "<br/><br/>";

    // Parse key=value&key2=value2
    std::string qs(query);
    size_t pos = 0;

    std::cout << "<b>Formatted Query String:</b><br/>";
    while ((pos = qs.find('&')) != std::string::npos)
    {
        std::string token = qs.substr(0, pos);
        std::cout << token << "<br/>";
        qs.erase(0, pos + 1);
    }
    if (!qs.empty())
        std::cout << qs << "<br/>";

    std::cout << "</body></html>";
    return 0;
}