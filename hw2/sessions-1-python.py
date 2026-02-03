#!/usr/bin/env python3
import os
import uuid
from urllib.parse import parse_qs
from http import cookies

SESSION_COOKIE = "CGISESSID"
SESSION_PREFIX = "/tmp/cse135_session_"


def load_cookies():
    jar = cookies.SimpleCookie()
    raw = os.environ.get("HTTP_COOKIE", "")
    if raw:
        jar.load(raw)
    return jar


def get_param(name):
    method = os.environ.get("REQUEST_METHOD", "").upper()
    if method == "POST":
        length = int(os.environ.get("CONTENT_LENGTH", "0") or "0")
        body = ""
        if length > 0:
            body = os.read(0, length).decode("utf-8", "ignore")
        params = parse_qs(body, keep_blank_values=True)
    else:
        query = os.environ.get("QUERY_STRING", "")
        params = parse_qs(query, keep_blank_values=True)
    values = params.get(name)
    if not values:
        return ""
    return values[0]


def read_session_value(sid):
    if not sid:
        return ""
    path = SESSION_PREFIX + sid
    try:
        with open(path, "r", encoding="utf-8") as handle:
            return handle.read().strip()
    except FileNotFoundError:
        return ""


def write_session_value(sid, value):
    if not sid:
        return
    path = SESSION_PREFIX + sid
    with open(path, "w", encoding="utf-8") as handle:
        handle.write(value)


jar = load_cookies()
sid = jar.get(SESSION_COOKIE)
sid_value = sid.value if sid else ""
if not sid_value:
    sid_value = uuid.uuid4().hex

name = get_param("username")
if name:
    write_session_value(sid_value, name)
else:
    name = read_session_value(sid_value)

print("Cache-Control: no-cache")
print(f"Set-Cookie: {SESSION_COOKIE}={sid_value}; Path=/")
print("Content-type: text/html\n")

print("<!DOCTYPE html>")
print("<html>")
print("<head>")
print("<title>Python Sessions</title>")
print("</head>")
print("<body>")

print("<h1>Python Sessions Page 1</h1>")

if name:
    print(f"<p><b>Name:</b> {name}</p>")
else:
    print("<p><b>Name:</b> You do not have a name set</p>")
print("<br/><br/>")
print('<a href="/hw2/sessions-2-python.py">Session Page 2</a><br/>')
print('<a href="/hw2/cgiform-python.html">Python CGI Form</a><br />')
print('<form style="margin-top:30px" action="/hw2/destroy-session-python.py" method="get">')
print("<button type=\"submit\">Destroy Session</button>")
print("</form>")

print("</body>")
print("</html>")
