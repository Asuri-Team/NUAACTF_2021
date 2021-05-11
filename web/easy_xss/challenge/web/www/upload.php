<?php
require_once 'init.php';
error_reporting(0);
if ($_SESSION['is_admin'] !== 1) {
    echo "You are not admin! You can't access this page.";
    highlight_file(__FILE__);
    die();
}

$userdir = "uploads/" . md5($_SERVER["REMOTE_ADDR"]);
if (!file_exists($userdir)) {
    mkdir($userdir, 0777, true);
}
if (isset($_POST["submit"])) {
    $tmp_name = $_FILES["upload"]["tmp_name"];
    $name = basename($_FILES["upload"]["name"]);
    if (!$tmp_name) {
        die();
    }
    if (!$name) {
        die("filename cannot be empty!");
    }
    $extension = substr($name, strrpos($name, ".") + 1);
    if (preg_match("/ph/i", $extension)) {
        die("illegal suffix!");
    }
    $upload_file_path = $userdir . "/" . $name;
    if (!move_uploaded_file($tmp_name, $upload_file_path)) {
        die("Error!");
    }
    echo "Your dir " . $userdir . ' <br>';
    echo "Your file: ";
    var_dump(scandir($userdir));
}