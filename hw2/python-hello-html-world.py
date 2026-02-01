#!/usr/bin/env python3
import os
import time

print("Cache-Control: no-cache")
print("Content-Type: text/html\n")

print("<!DOCTYPE html>")
print("<html>")
print("<head>")
print("<title>Hello CGI World</title>")
print("</head>")
print("<body>")

print("<h1 align='center'>Hello HTML World</h1><hr/>")
print("<h3>Python Hello World by Yeunwook and Kevin</h3>")
print("<p>Hello World</p>")
print("<p>This page was generated with the Python programming language</p>")

current_time = time.ctime()
print(f"<p>This program was generated at: {current_time}</p>")

address = os.environ.get('REMOTE_ADDR', 'Unknown')
print(f"<p>Your current IP Address is: {address}</p>")

print("</body>")
print("</html>")