#include "netendpointcreator.h"
#include "tcpserver.h"

NetEndpointCreator::NetEndpointCreator()
{
}

IServerPtr NetEndpointCreator::createServer( ServerArgsPtr serverArgsPtr)
{
	if( std::string( serverArgsPtr->getTransport()) == std::string( "tcp"))
	{
		return IServerPtr( new TCPServer( serverArgsPtr));
	}

	return 0;
}
