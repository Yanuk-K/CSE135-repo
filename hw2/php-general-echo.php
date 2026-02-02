<?php
// Prevent caching
header("Cache-Control: no-cache");
header("Content-Type: text/html");

// Basic request info
$method   = $_SERVER['REQUEST_METHOD'] ?? 'N/A';
$protocol = $_SERVER['SERVER_PROTOCOL'] ?? 'N/A';
$query    = $_SERVER['QUERY_STRING'] ?? '';
$ip       = $_SERVER['REMOTE_ADDR'] ?? 'N/A';
$agent    = $_SERVER['HTTP_USER_AGENT'] ?? 'N/A';

// Read raw body (works for POST, PUT, DELETE)
$rawBody = file_get_contents("php://input");
?>

<!DOCTYPE html>
<html>
<head>
    <title>General Request Echo (PHP)</title>
</head>
<body>
    <h1 align="center">General Request Echo</h1>
    <hr>

    <p><b>HTTP Protocol:</b> <?= htmlspecialchars($protocol) ?></p>
    <p><b>HTTP Method:</b> <?= htmlspecialchars($method) ?></p>
    <p><b>Query String:</b> <?= htmlspecialchars($query) ?></p>
    <p><b>User Agent:</b> <?= htmlspecialchars($agent) ?></p>
    <p><b>Your IP Address:</b> <?= htmlspecialchars($ip) ?></p>

    <hr>
    <b>Message Body:</b><br />

    <?php if (!empty($rawBody)): ?>
        <pre><?= htmlspecialchars($rawBody) ?></pre>
    <?php else: ?>
        <i>(No message body)</i>
    <?php endif; ?>

</body>
</html>