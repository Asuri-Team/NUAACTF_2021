<?php
function render_tags($str) {
  $str = preg_replace('/script|img|svg|on|document|window/i', "" ,$str);
  return $str;
}

function get_nonce() {
  return base64_encode(random_bytes(16));
}

function sha256($str) {
  return hash('sha256', $str);
}

function uuid4() {
  return sprintf('%04x%04x-%04x-%04x-%04x-%04x%04x%04x',
    mt_rand(0, 0xffff),
    mt_rand(0, 0xffff),
    mt_rand(0, 0xffff),
    mt_rand(0, 0xfff) | 0x4000,
    mt_rand(0, 0x3fff) | 0x8000,
    mt_rand(0, 0xffff),
    mt_rand(0, 0xffff),
    mt_rand(0, 0xffff)
  );
}