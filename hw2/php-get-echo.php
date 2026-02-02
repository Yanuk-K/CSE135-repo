<?php
// HTTP headers
header("Cache-Control: no-cache");
header("Content-Type: text/html");

// getting the raw string from the url 
$query_string = $_SERVER['QUERY_STRING'] ?? '';
?>

<!DOCTYPE html>
<html>
<head>
    <title>GET Request Echo (PHP)</title>
</head>
<body>
    <h1 align="center">GET Request Echo</h1>
    <hr>

    <b>Raw Query String:</b> <?= htmlspecialchars($query_string) ?><br /><br />

    <b>Parsed Query String:</b><br />
    <ul>
        <?php
        // parsing the string which came from the raw string
        foreach ($_GET as $key => $value) {
            if (is_array($value)) {
                $value = implode(", ", $value);
            }
            echo "<li>$key = " . htmlspecialchars($value) . "</li>";
        }
        ?>
    </ul>

</body>
</html>