<?php
header("Cache-Control: no-cache");
header("Content-Type: text/html");

session_start();

$_SESSION = [];
if (ini_get("session.use_cookies")) {
    $params = session_get_cookie_params();
    setcookie(session_name(), "", time() - 42000, $params["path"], $params["domain"], $params["secure"], $params["httponly"]);
}

session_destroy();
?>

<!DOCTYPE html>
<html>
<head>
    <title>PHP Session Destroyed</title>
</head>
<body>
    <h1>Session Destroyed</h1>
    <a href="/hw2/cgiform-php.html">Back to the PHP CGI Form</a><br />
    <a href="/hw2/sessions-1-php.php">Back to Page 1</a><br />
    <a href="/hw2/sessions-2-php.php">Back to Page 2</a>
</body>
</html>
