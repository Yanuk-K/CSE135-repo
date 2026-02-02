#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    // HTTP headers
    std::cout << "Cache-Control: no-cache\r\n";
    std::cout << "Content-Type: application/json\r\n\r\n";

    // Time
    std::time_t now = std::time(nullptr);
    char *timeStr = std::ctime(&now);

    // IP address
    const char *ip = std::getenv("REMOTE_ADDR");
    if (!ip)
        ip = "Unknown";

    // JSON output
    std::cout << "{\n";
    std::cout << "  \"title\": \"Hello, C++!\",\n";
    std::cout << "  \"heading\": \"Hello, C++!\",\n";
    std::cout << "  \"message\": \"This page was edited by Yeunwook and Kevin\",\n";
    std::cout << "  \"time\": \"" << timeStr << "\",\n";
    std::cout << "  \"IP\": \"" << ip << "\"\n";
    std::cout << "}\n";

    return 0;
}
