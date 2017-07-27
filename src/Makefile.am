bin_PROGRAMS = transporter
AM_CPPFLAGS = -I$(top_srcdir)
transporter_SOURCES = main.cpp \
					  args/argsparser.cpp \
					  args/serverargs.cpp \
					  args/clientargs.cpp \
					  \
					  net/netendpointcreator.cpp	\
					  net/transport.cpp \
					  net/server/iserver.cpp	\
					  net/server/tcp/session.cpp \
					  net/server/tcp/tcpserver.cpp \
					  net/client/iclient.cpp \
					  net/client/tcp/tcpclient.cpp \
					  net/client/udp/udpclient.cpp \
					  \
					  file/filemanager.cpp \
					  file/file.cpp