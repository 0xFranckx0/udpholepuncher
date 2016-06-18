ACLOCAL_AMFLAGS = -I m4 --install     
lib_LTLIBRARIES = libobj/libuhp.la
libobj_libuhp_la_SOURCES =  lib/error.c \
                            lib/jconverter.c \
                            lib/svr_udp.c \
                            lib/uhp.c 
							
libobj_libuhp_la_LDFLAGS = -version-info 0:0:0
include_HEADERS =   lib/error.h \
                    lib/uhp.h
libobj_libuhp_la_LIBADD = -lssl -lcrypto -levent \
			  $(jansson_LIBS)

bin_PROGRAMS = bin/test
bin_test_SOURCES = src/test.c
bin_test_CPPFLAGS = -DDEBUG
bin_test_LDADD = $(lib_LTLIBRARIES) 

EXTRA_DIST = m4/NOTES                                                           
