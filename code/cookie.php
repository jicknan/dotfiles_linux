<?php 
$ret = setcookie("user", "Alex Porter", time()+3600);
?>

<html>
<body>
<p>
<?php
echo "ret: $ret <br />\n";
// Print a cookie
echo $_COOKIE["user"] . "<br />";

// A way to view all cookies
print_r($_COOKIE);
?>
</p>

<p>
<?php
if (isset($_COOKIE["user"]))
      echo "Welcome " . $_COOKIE["user"] . "!<br />";
else
      echo "Welcome guest!<br />";
?>
</p>

</body>
</html>
