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
