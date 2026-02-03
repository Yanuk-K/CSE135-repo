#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

namespace {
const std::string kSessionCookie = "CGISESSID";
const std::string kSessionPrefix = "/tmp/cse135_session_";

std::string trim(const std::string &value) {
    size_t start = value.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) {
        return "";
    }
    size_t end = value.find_last_not_of(" \t\n\r");
    return value.substr(start, end - start + 1);
}

std::unordered_map<std::string, std::string> parse_pairs(const std::string &input, char delimiter) {
    std::unordered_map<std::string, std::string> params;
    std::istringstream stream(input);
    std::string part;
    while (std::getline(stream, part, delimiter)) {
        if (part.empty()) {
            continue;
        }
        size_t eq = part.find('=');
        if (eq == std::string::npos) {
            params[trim(part)] = "";
            continue;
        }
        std::string key = trim(part.substr(0, eq));
        std::string value = trim(part.substr(eq + 1));
        params[key] = value;
    }
    return params;
}

std::unordered_map<std::string, std::string> parse_cookies() {
    const char *raw = std::getenv("HTTP_COOKIE");
    if (!raw) {
        return {};
    }
    return parse_pairs(raw, ';');
}

void delete_session_value(const std::string &sid) {
    if (sid.empty()) {
        return;
    }
    std::remove((kSessionPrefix + sid).c_str());
}
} // namespace

int main() {
    auto cookies = parse_cookies();

    std::string sid;
    auto cookie_it = cookies.find(kSessionCookie);
    if (cookie_it != cookies.end() && !cookie_it->second.empty()) {
        sid = cookie_it->second;
    }

    delete_session_value(sid);

    std::cout << "Cache-Control: no-cache\n";
    std::cout << "Set-Cookie: " << kSessionCookie
              << "=deleted; Expires=Thu, 01 Jan 1970 00:00:00 GMT; Path=/\n";
    std::cout << "Content-Type: text/html\n\n";

    std::cout << "<!DOCTYPE html>\n";
    std::cout << "<html>\n";
    std::cout << "<head>\n";
    std::cout << "<title>C++ Session Destroyed</title>\n";
    std::cout << "</head>\n";
    std::cout << "<body>\n";
    std::cout << "<h1>Session Destroyed</h1>\n";
    std::cout << "<a href=\"/hw2/cpp-cgiform.html\">Back to the C++ CGI Form</a><br />\n";
    std::cout << "<a href=\"/hw2/cpp-sessions-1.cgi\">Back to Page 1</a><br />\n";
    std::cout << "<a href=\"/hw2/cpp-sessions-2.cgi\">Back to Page 2</a>\n";
    std::cout << "</body>\n";
    std::cout << "</html>\n";

    return 0;
}
