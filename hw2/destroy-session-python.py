#!/usr/bin/env python3
import os
from http import cookies

SESSION_COOKIE = "CGISESSID"
SESSION_PREFIX = "/tmp/cse135_session_"


def load_cookies():
    jar = cookies.SimpleCookie()
    raw = os.environ.get("HTTP_COOKIE", "")
    if raw:
        jar.load(raw)
    return jar


def delete_session(sid):
    if not sid:
        return
    path = SESSION_PREFIX + sid
    try:
        os.remove(path)
    except FileNotFoundError:
        pass


jar = load_cookies()
sid = jar.get(SESSION_COOKIE)
sid_value = sid.value if sid else ""

delete_session(sid_value)

print("Cache-Control: no-cache")
print(
    f"Set-Cookie: {SESSION_COOKIE}=deleted; Expires=Thu, 01 Jan 1970 00:00:00 GMT; Path=/"
)
print("Content-type: text/html\n")

print("<!DOCTYPE html>")
print("<html>")
print("<head>")
print("<title>Python Session Destroyed</title>")
print("</head>")
print("<body>")
print("<h1>Session Destroyed</h1>")
print('<a href="/hw2/cgiform-python.html">Back to the Python CGI Form</a><br />')
print('<a href="/hw2/sessions-1-python.py">Back to Page 1</a><br />')
print('<a href="/hw2/sessions-2-python.py">Back to Page 2</a>')
print("</body>")
print("</html>")
