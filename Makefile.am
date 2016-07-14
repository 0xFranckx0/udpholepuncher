ACLOCAL_AMFLAGS = -I m4 --install     
lib_LTLIBRARIES = libobj/libuhp.la
libobj_libuhp_la_SOURCES =  include/error.c \
                            include/jconverter.c \
                            include/uhp_data.c \
                            include/uhp_ev.c \
                            include/uhp_net.c \
                            include/uhp_utils.c
							
libobj_libuhp_la_LDFLAGS = -version-info 0:0:0
include_HEADERS =   include/error.h \
                    include/uhp.h
libobj_libuhp_la_LIBADD = -lssl -lcrypto -levent \
			  $(jansson_LIBS)

noinst_PROGRAMS = bin/test
bin_test_SOURCES = src/test.c
bin_test_CPPFLAGS = -DDEBUG
bin_test_LDADD = $(lib_LTLIBRARIES) 

EXTRA_DIST = m4/NOTES                                                           
