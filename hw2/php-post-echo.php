<?php
// HTTP headers
header("Cache-Control: no-cache");
header("Content-Type: text/html");
?>

<!DOCTYPE html>
<html>
<head>
    <title>POST Request Echo (PHP)</title>
</head>
<body>
    <h1 align="center">POST Request Echo</h1>
    <hr>

    <b>Message Body:</b><br />

    <?php
    // Using print logic to actually show on the page
    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        echo "<ul>";
        foreach ($_POST as $key => $value) {
            if (is_array($value)) {
                $value = implode(", ", $value);
            }
            echo "<li>$key = " . htmlspecialchars($value) . "</li>";
        }
        echo "</ul>";
    } else {
        echo "<p>No POST data received.</p>";
    }
    ?>

</body>
</html>
