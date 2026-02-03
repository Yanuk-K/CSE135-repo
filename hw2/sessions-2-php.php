<?php
header("Cache-Control: no-cache");
header("Content-Type: text/html");

session_start();

$name = $_SESSION["username"] ?? "";
?>

<!DOCTYPE html>
<html>
<head>
    <title>PHP Sessions</title>
</head>
<body>
    <h1>PHP Sessions Page 2</h1>

    <?php if ($name !== ""): ?>
        <p><b>Name:</b> <?php echo htmlspecialchars($name); ?></p>
    <?php else: ?>
        <p><b>Name:</b> You do not have a name set</p>
    <?php endif; ?>

    <br/><br/>
    <a href="/hw2/sessions-1-php.php">Session Page 1</a><br/>
    <a href="/hw2/cgiform-php.html">PHP CGI Form</a><br />
    <form style="margin-top:30px" action="/hw2/destroy-session-php.php" method="get">
        <button type="submit">Destroy Session</button>
    </form>
</body>
</html>
