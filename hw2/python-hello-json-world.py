#!/usr/bin/env python3
import json
import os
import time

print("Cache-Control: no-cache")
print("Content-Type: application/json\n")

current_time = time.ctime()
ip_address = os.environ.get('REMOTE_ADDR')

message_data = {
    "title": "Hello, Python!",
    "heading": "Hello, Python!",
    "message": "This page was created by Yeunwook and Kevin",
    "time": current_time,
    "IP": ip_address
}

print(json.dumps(message_data))