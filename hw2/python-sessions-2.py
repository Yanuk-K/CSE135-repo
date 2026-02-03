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


def read_session_value(sid):
    if not sid:
        return ""
    path = SESSION_PREFIX + sid
    try:
        with open(path, "r", encoding="utf-8") as handle:
            return handle.read().strip()
    except FileNotFoundError:
        return ""


jar = load_cookies()
sid = jar.get(SESSION_COOKIE)
sid_value = sid.value if sid else ""
name = read_session_value(sid_value)

print("Cache-Control: no-cache")
print("Content-type: text/html\n")

print("<!DOCTYPE html>")
print("<html>")
print("<head>")
print("<title>Python Sessions</title>")
print("</head>")
print("<body>")

print("<h1>Python Sessions Page 2</h1>")

if name:
    print(f"<p><b>Name:</b> {name}</p>")
else:
    print("<p><b>Name:</b> You do not have a name set</p>")
print("<br/><br/>")
print('<a href="/hw2/python-sessions-1.py">Session Page 1</a><br/>')
print('<a href="/python-cgiform.html">Python CGI Form</a><br />')
print('<form style="margin-top:30px" action="/hw2/python-destroy-session.py" method="get">')
print("<button type=\"submit\">Destroy Session</button>")
print("</form>")

print("</body>")
print("</html>")
