<?php
// HTTP headers
header("Cache-Control: no-cache");
header("Content-Type: text/html");

// getting the raw string from the url 
$query_strings = $_SERVER['QUERY_STRING'] ?? '';
?>

<!DOCTYPE html>
<html>
<head>
    <title>GET Request Echo (PHP)</title>
</head>
<body>
    <h1 align="center">GET Request Echo</h1>
    <hr>

    <b>Raw Query String:</b> <?= htmlspecialchars($query_strings) ?><br /><br />

    <b>Parsed Query String:</b><br />
    <ul>
        <?php
        // parsing the string which came from the raw string
        // make automatically array and read key and value separately.
        foreach ($_GET as $key => $value) {
            if (is_array($value)) {
                // change it to string from array.
                $value = implode(", ", $value);
            }
            // prevent to show the actual script on the page
            echo "<li>$key = " . htmlspecialchars($value) . "</li>";
        }
        ?>
    </ul>

</body>
</html>