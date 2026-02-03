#include <iostream>
#include <cstdlib>

extern char **environ;

int main()
{
    // HTTP headers
    std::cout << "Cache-Control: no-cache\n";
    std::cout << "Content-type: text/html\n\n";

    // HTML header
    std::cout << "<!DOCTYPE html>\n";
    std::cout << "<html><head><title>Environment Variables</title></head>\n";
    std::cout << "<body>\n";
    std::cout << "<h1 align=\"center\">Environment Variables</h1>\n";
    std::cout << "<hr>\n";

    // Loop through environment variables
    for (char **env = environ; *env != nullptr; env++)
    {
        std::cout << "<b>" << *env << "</b><br />\n";
    }

    // HTML footer
    std::cout << "</body></html>\n";

    return 0;
}