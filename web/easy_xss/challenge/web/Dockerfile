FROM php:7.4.0-apache
RUN apt-get update 
RUN apt-get install -y git
RUN git clone https://github.com/phpredis/phpredis.git /usr/src/php/ext/redis
RUN docker-php-ext-install pdo_mysql
RUN docker-php-ext-install redis
RUN echo 'flag{851f398a-3db1-4299-8dd6-6a3d2467433f}' > /flag
COPY ./www /var/www/html
RUN chmod 777 /var/www/html/uploads
EXPOSE 80
