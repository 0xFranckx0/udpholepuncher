ACLOCAL_AMFLAGS = -I m4 --install     

lib_LTLIBRARIES = libobj/libuhp.la
libobj_libuhp_la_SOURCES =  include/error.c \
                            include/jconverter.c \
                    	    include/punch.c \
                            include/uhp.c \
                            include/uhp_data.c \
                            include/uhp_net.c 
							
libobj_libuhp_la_LIBADD = $(libevent_LIBS) \
			  -lssl -lcrypto \
			  $(jansson_LIBS) 
							
libobj_libuhp_la_LDFLAGS = -version-info 0:0:0
include_HEADERS =   include/error.h \
                    include/punch.h 

noinst_PROGRAMS = test
test_SOURCES = src/test.c
test_CPPFLAGS = -DDEBUG
test_LDADD = $(lib_LTLIBRARIES) \
	     $(libevent_LIBS) 

EXTRA_DIST = m4/NOTES                                                           
