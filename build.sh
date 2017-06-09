#/bin/sh
OS=$(uname -s) 
if test "${OS}" == "OpenBSD" ; then
	echo "setting env"
	. ./openbsd.env
fi

autoreconf -fiv &&\
./configure &&\
make &&\
doas make install
