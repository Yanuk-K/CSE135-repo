#!/usr/bin/env python3
import os
import sys
import urllib.parse

print("Cache-Control: no-cache")
print("Content-type: text/html \n")

# print HTML file top
print("""<!DOCTYPE html>
<html><head><title>POST Request Echo</title>
</head><body><h1 align="center">POST Request Echo</h1>
<hr>""")

content_length = os.environ.get('CONTENT_LENGTH')

if content_length:
    length = int(content_length)
    form_data = sys.stdin.read(length)
    
    parsed_data = urllib.parse.parse_qs(form_data)

    print("<b>Message Body:</b><br />")
    print("<ul>")

    for key, values in parsed_data.items():
        value_str = ", ".join(values)
        print(f"<li>{key} = {value_str}</li>")

    print("</ul>")
else:
    print("<p>No POST data received.</p>")

# Print the HTML file bottom
print("</body></html>")