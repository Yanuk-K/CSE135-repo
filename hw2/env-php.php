<?php
// HTTP headers
header("Cache-Control: no-cache");
header("Content-Type: text/html");
?>

<!DOCTYPE html>
<html>
<head>
    <title>Environment Variables (PHP)</title>
</head>
<body>
    <h1 align="center">Environment Variables</h1>
    <hr>

    <?php
    // $_SERVER contains CGI / server environment variables
    foreach ($_SERVER as $key => $value) {
        echo "<b>$key:</b> $value<br />\n";
    }
    ?>

</body>
</html>