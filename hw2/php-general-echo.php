<?php
// Prevent caching
header("Cache-Control: no-cache");
header("Content-Type: text/html");

// Basic request
$method   = $_SERVER['REQUEST_METHOD'] ?? 'N/A';
$protocol = $_SERVER['SERVER_PROTOCOL'] ?? 'N/A';
$q    = $_SERVER['QUERY_STRING'] ?? '';
$ip       = $_SERVER['REMOTE_ADDR'] ?? 'N/A';
$a   = $_SERVER['HTTP_USER_AGENT'] ?? 'N/A';

// Reading the raw data for all the method.
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
    <p><b>Query String:</b> <?= htmlspecialchars($q) ?></p>
    <p><b>User Agent:</b> <?= htmlspecialchars($a) ?></p>
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