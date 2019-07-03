# image for compiling languages and sass
FROM ubuntu:latest as build

# Stop the Ubuntu image from prompting us about timezone
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=America/Indiana/Indianapolis
RUN ln -snf /usr/share/zoneinfo/America/$TZ /etc/localtime \
    && echo $TZ > /etc/timezone

RUN apt update -y && apt -y install \
    gettext \
    sassc

WORKDIR /build

# add entire context to /build
# .dockerignore ensures that we end up with
# the same state as the rsync command+buildignore in build.sh
ADD . .

WORKDIR /build/language
RUN chmod +x build_lang.sh && ./build_lang.sh

WORKDIR /build/public/css/local
RUN sassc --style compact screen.scss screen.css


## Start new image
FROM ubuntu:latest

# Stop the Ubuntu image from prompting us about timezone
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=America/Indiana/Indianapolis
RUN ln -snf /usr/share/zoneinfo/America/$TZ /etc/localtime \
 && echo $TZ > /etc/timezone

RUN apt-get update && apt-get install -y apache2
RUN a2enmod alias \
 && a2enmod headers \
 && a2enmod remoteip \
 && a2enmod rewrite

RUN apt-get install -y \
        php-common \
        php-cli \
        php-json \
        php-readline \
        php-mbstring \
        php-intl \
        php-curl \
        php-mysql \
        # the app does have support for ldap, so might as well include it
        php-ldap \
        php-xsl \
        libapache2-mod-php

# Copy the built app from the build stage and put in /srv/sites
COPY --from=build /build /srv/sites/meter_monitor
RUN chown -R www-data:staff /srv/sites/meter_monitor
ADD docker/apache.conf /etc/apache2/sites-available/000-default.conf

EXPOSE 80

ENTRYPOINT ["apachectl", "-D", "FOREGROUND"]
