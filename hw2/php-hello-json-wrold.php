<?php
// HTTP headers
header("Cache-Control: no-cache");
header("Content-Type: application/json");

// Data
$response = [
    "title"   => "Hello, PHP!",
    "heading" => "Hello, PHP!",
    "message" => "This page was edited by Yeunwook and Kevin",
    "time"    => date("r"),
    "IP"      => $_SERVER['REMOTE_ADDR'] ?? 'N/A'
];

// Output JSON
echo json_encode($response, JSON_PRETTY_PRINT);