#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
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

std::string url_decode(const std::string &value) {
    std::string decoded;
    decoded.reserve(value.size());
    for (size_t i = 0; i < value.size(); i++) {
        if (value[i] == '+') {
            decoded.push_back(' ');
        } else if (value[i] == '%' && i + 2 < value.size()) {
            std::string hex = value.substr(i + 1, 2);
            char ch = static_cast<char>(std::strtol(hex.c_str(), nullptr, 16));
            decoded.push_back(ch);
            i += 2;
        } else {
            decoded.push_back(value[i]);
        }
    }
    return decoded;
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
        std::string value = part.substr(eq + 1);
        params[key] = url_decode(value);
    }
    return params;
}

std::unordered_map<std::string, std::string> parse_query() {
    const char *raw = std::getenv("QUERY_STRING");
    if (!raw) {
        return {};
    }
    return parse_pairs(raw, '&');
}

std::unordered_map<std::string, std::string> parse_post() {
    const char *method = std::getenv("REQUEST_METHOD");
    if (!method || std::string(method) != "POST") {
        return {};
    }
    const char *length = std::getenv("CONTENT_LENGTH");
    int len = length ? std::atoi(length) : 0;
    if (len <= 0) {
        return {};
    }
    std::string body;
    body.reserve(static_cast<size_t>(len));
    for (int i = 0; i < len; i++) {
        char c;
        std::cin.get(c);
        body.push_back(c);
    }
    return parse_pairs(body, '&');
}

std::unordered_map<std::string, std::string> parse_cookies() {
    const char *raw = std::getenv("HTTP_COOKIE");
    if (!raw) {
        return {};
    }
    auto parsed = parse_pairs(raw, ';');
    for (auto &item : parsed) {
        item.second = trim(item.second);
    }
    return parsed;
}

std::string generate_session_id() {
    static const char *hex = "0123456789abcdef";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 15);
    std::string id;
    id.reserve(32);
    for (int i = 0; i < 32; i++) {
        id.push_back(hex[dist(gen)]);
    }
    return id;
}

std::string read_session_value(const std::string &sid) {
    if (sid.empty()) {
        return "";
    }
    std::ifstream file(kSessionPrefix + sid);
    if (!file) {
        return "";
    }
    std::string value;
    std::getline(file, value);
    return value;
}

void write_session_value(const std::string &sid, const std::string &value) {
    if (sid.empty()) {
        return;
    }
    std::ofstream file(kSessionPrefix + sid);
    if (file) {
        file << value;
    }
}
} // namespace

int main() {
    auto query = parse_query();
    auto post = parse_post();
    auto cookies = parse_cookies();

    std::string sid;
    bool set_cookie = false;
    auto cookie_it = cookies.find(kSessionCookie);
    if (cookie_it != cookies.end() && !cookie_it->second.empty()) {
        sid = cookie_it->second;
    } else {
        sid = generate_session_id();
        set_cookie = true;
    }

    std::string name;
    auto name_it = post.find("username");
    if (name_it != post.end() && !name_it->second.empty()) {
        name = name_it->second;
        write_session_value(sid, name);
    } else {
        name_it = query.find("username");
        if (name_it != query.end() && !name_it->second.empty()) {
            name = name_it->second;
            write_session_value(sid, name);
        }
    }
    if (name.empty()) {
        name = read_session_value(sid);
    }

    std::cout << "Cache-Control: no-cache\n";
    if (set_cookie) {
        std::cout << "Set-Cookie: " << kSessionCookie << "=" << sid << "; Path=/\n";
    } else {
        std::cout << "Set-Cookie: " << kSessionCookie << "=" << sid << "; Path=/\n";
    }
    std::cout << "Content-Type: text/html\n\n";

    std::cout << "<!DOCTYPE html>\n";
    std::cout << "<html>\n";
    std::cout << "<head>\n";
    std::cout << "<title>C++ Sessions</title>\n";
    std::cout << "</head>\n";
    std::cout << "<body>\n";

    std::cout << "<h1>C++ Sessions Page 1</h1>\n";

    if (!name.empty()) {
        std::cout << "<p><b>Name:</b> " << name << "</p>\n";
    } else {
        std::cout << "<p><b>Name:</b> You do not have a name set</p>\n";
    }
    std::cout << "<br/><br/>\n";
    std::cout << "<a href=\"/hw2/sessions-2-cpp.cgi\">Session Page 2</a><br/>\n";
    std::cout << "<a href=\"/hw2/cgiform-cpp.html\">C++ CGI Form</a><br />\n";
    std::cout << "<form style=\"margin-top:30px\" action=\"/hw2/destroy-session-cpp.cgi\" method=\"get\">\n";
    std::cout << "<button type=\"submit\">Destroy Session</button>\n";
    std::cout << "</form>\n";

    std::cout << "</body>\n";
    std::cout << "</html>\n";

    return 0;
}
