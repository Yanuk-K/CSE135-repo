#!/usr/bin/env python3
import os
import urllib.parse

print("Cache-Control: no-cache")
print("Content-type: text/html \n")

# print HTML file top
print("""<!DOCTYPE html>
<html><head><title>GET Request Echo</title>
</head><body><h1 align="center">Get Request Echo</h1>
<hr>""")


# The Query String is simply an environment variable
query_string = os.environ.get('QUERY_STRING', '')
print(f"<b>Query String:</b> {query_string}<br />\n")

# Credit for this code to parse the Query string:
parsed_query = urllib.parse.parse_qs(query_string)

for key, values in parsed_query.items():
    value_str = ", ".join(values)
    print(f"{key} = {value_str}<br/>\n")

# Print the HTML file bottom
print("</body></html>")