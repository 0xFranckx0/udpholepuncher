ACLOCAL_AMFLAGS = -I m4 --install     

lib_LTLIBRARIES = libobj/libuhp.la
libobj_libuhp_la_SOURCES =  include/error.c \
                            include/jconverter.c \
                    	    include/punch.c \
                            include/uhp.c \
                            include/uhp_data.c \
                            include/uhp_ev.c \
                            include/uhp_net.c \
                            include/uhp_utils.c
							
libobj_libuhp_la_LDFLAGS = -version-info 0:0:0
include_HEADERS =   include/error.h \
                    include/punch.h 
libobj_libuhp_la_LIBADD = -lssl -lcrypto -levent_core\
			  $(jansson_LIBS) 

noinst_PROGRAMS = test
test_SOURCES = src/test.c
test_CPPFLAGS = -DDEBUG
test_LDADD = $(lib_LTLIBRARIES) 

EXTRA_DIST = m4/NOTES                                                           
