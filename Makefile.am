ACLOCAL_AMFLAGS = -I m4 --install     

lib_LTLIBRARIES = libobj/libuhp.la
libobj_libuhp_la_SOURCES =  include/error.c \
                            include/uhp_data.c \
                    	    include/uhp_loop.c \
                    	    include/uhp_log.c \
                            include/uhp_messages.c \
                            include/uhp_net.c \
                            include/uhp_protocol.c 
							
libobj_libuhp_la_LIBADD = $(libevent_LIBS) \
			  -lssl -lcrypto \
			  $(jansson_LIBS) 
							
libobj_libuhp_la_LDFLAGS = -version-info 0:0:0
include_HEADERS =   include/error.h \
                    include/punch.h \
                    include/uhp.h 

#bin_PROGRAMS = punchctl
#punchctl_SOURCES = src/punchctl.c
#punchctl_CPPFLAGS = -DDEBUG
#punchctl_LDADD = $(lib_LTLIBRARIES) \
#	     $(libevent_LIBS) 

bin_PROGRAMS = proto_test
proto_test_SOURCES = src/proto_test.c
proto_test_CPPFLAGS = -DDEBUG
proto_test_LDADD = $(lib_LTLIBRARIES) \
	     $(libevent_LIBS) 
EXTRA_DIST = m4/NOTES                                                           
