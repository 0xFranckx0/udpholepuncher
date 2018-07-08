#/bin/sh
OS=$(uname -s) 
if test "${OS}" == "OpenBSD" ; then
	echo "setting env"
	. ./openbsd.env
	autoreconf -fiv &&\
	./configure &&\
	make &&\
	doas make install
else
	autoreconf -fiv &&\
	./configure &&\
	make &&\
	make install 
fi


