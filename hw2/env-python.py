#!/usr/bin/env python3
import os
import time

print("Cache-Control: no-cache")
print("Content-type: text/html \n")

# print HTML file top
print("<!DOCTYPE html>")
print("<html>")
print("<head>")
print("<title>Environment Variables</title>")
print("</head>")
print("<body>")
print('<h1 align="center">Environment Variables</h1>')
print("<hr>")


# Loop over the environment variables and print each variable and its value
for variable in sorted(os.environ.keys()):
  print(f"<b>{variable}:</b> {os.environ[variable]}<br />")

# Print the HTML file bottom
print("</body></html>")
