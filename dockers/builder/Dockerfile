FROM debian:jessie

MAINTAINER Gurwall

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \ 
	build-essential linux-headers-`uname -r` \
	ncurses-dev libxml2-dev \
	binutils-dev libpq-dev \
	libcurl4-openssl-dev \
	libbluetooth-dev libcorosync-dev \ 
	libedit-dev libgsm1-dev \
	libgtk2.0-dev libical-dev \
	libiksemel-dev libjack-dev \
	liblua5.1-0-dev libmysqlclient-dev \
	libneon27-dev \
	libnewt-dev libogg-dev libpopt-dev \
	libpq-dev libsnmp-dev \
	libspandsp-dev \
	libspeex-dev libspeexdsp-dev libsqlite0-dev \
	libsqlite3-dev \
	pkg-config libspandsp-dev \
	lua5.1 portaudio19-dev \
	unixodbc-dev uuid uuid-dev \
	libusb-dev libvorbis-dev \
	autoconf automake curl

RUN apt-get update && apt-get install -y \
	pkg-config libspandsp-dev \
	flex bison \
	strace valgrind gdb make gcc \
	libjansson4 libjansson-dev libjansson-doc \
	libtool wget git tar

RUN cd /opt && wget https://github.com/libevent/libevent/releases/download/release-2.0.22-stable/libevent-2.0.22-stable.tar.gz &&\
	tar xvzf libevent-2.0.22-stable.tar.gz &&\ 
	cd /opt/libevent-2.0.22-stable &&\
	./configure &&\
	make &&\
	make install

RUN ln -s /usr/local/lib/libevent-2.0.so.5 /usr/lib/libevent-2.0.so.5

RUN cd /opt &&\
	git clone https://github.com/libressl-portable/portable.git libressl &&\
	cd libressl && sh autogen.sh &&\
	./configure --prefix="${HOME}/opt/libressl" &&\
	make && make install &&\
	echo '/opt/libressl' | sudo tee /etc/ld.so.conf.d/libressl.conf &&\
	ldconfig

ENV C_INCLUDE_PATH="/opt/libressl/include" 
ENV LIBRARY_PATH="/opt/libressl/lib"
	



