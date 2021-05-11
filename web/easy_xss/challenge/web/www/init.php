<?php
error_reporting(0);

require_once 'config.php';
require_once 'util.php';

$nonce = get_nonce();
header('X-Frame-Options: DENY');
header('X-XSS-Protection: 1; mode=block');

session_start();