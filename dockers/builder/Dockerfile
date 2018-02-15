FROM debian:jessie

MAINTAINER Gurwall

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
	pkg-config \
	autoconf \
	automake \
	build-essential \
	linux-headers-`uname -r` \
	libssl-dev \
	make \
	libjansson4 \ 
	libjansson-dev \
 	libtool \
	tar \
	wget \
	libgtk2.0-dev 


RUN cd /opt && wget https://github.com/libevent/libevent/releases/download/release-2.0.22-stable/libevent-2.0.22-stable.tar.gz &&\
	tar xvzf libevent-2.0.22-stable.tar.gz &&\ 
	cd /opt/libevent-2.0.22-stable &&\
	./configure --libdir=/usr/lib &&\
	make &&\
	make install


ADD build.sh /opt/
ADD entrypoint /opt/

