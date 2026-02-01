#!/usr/bin/env python3
import os
import sys

print("Cache-Control: no-cache")
print("Content-type: text/html \n")

# print HTML file top
print("""<!DOCTYPE html>
<html><head><title>General Request Echo</title>
</head><body><h1 align="center">General Request Echo</h1>
<hr>""")

print(f"<p><b>HTTP Protocol:</b> {os.environ.get('SERVER_PROTOCOL', 'N/A')}</p>")
print(f"<p><b>HTTP Method:</b> {os.environ.get('REQUEST_METHOD', 'N/A')}</p>")
print(f"<p><b>Query String:</b> {os.environ.get('QUERY_STRING', 'N/A')}</p>")


content_length = os.environ.get('CONTENT_LENGTH', '0')
form_data = ""

if content_length and int(content_length) > 0:
    form_data = sys.stdin.read(int(content_length))

print(f"<p><b>Message Body:</b> {form_data}</p>")

# Print the HTML file bottom
print("</body></html>")