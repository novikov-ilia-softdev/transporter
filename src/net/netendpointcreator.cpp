#include "netendpointcreator.h"
#include "tcpserver.h"
#include "transport.h"

NetEndpointCreator::NetEndpointCreator()
{
}

IServerPtr NetEndpointCreator::createServer( ServerArgsPtr serverArgsPtr)
{
	if( std::string( serverArgsPtr->getTransport()) == Transport::TCP)
	{
		return IServerPtr( new TCPServer( serverArgsPtr));
	}

	return 0;
}
