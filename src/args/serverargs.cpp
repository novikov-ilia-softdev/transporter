#include "serverargs.h"

ServerArgs::ServerArgs( char* port, char* transport):
	port_( port), transport_( transport)
{
}

std::ostream& operator<<( std::ostream& stream, ServerArgs* args)
{
	return stream << "port: " << args->port_
				  <<", transport: " << args->transport_;
}

char* ServerArgs::getPort() const
{
	return port_;
}

char* ServerArgs::getTransport() const
{
	return transport_;
}
