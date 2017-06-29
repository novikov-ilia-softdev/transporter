#include "netendpointcreator.h"
#include "tcpserver.h"
#include "tcpclient.h"
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

IClientPtr NetEndpointCreator::createClient( ClientArgsPtr clientArgsPtr)
{
	if( std::string( clientArgsPtr->getTransport()) == Transport::TCP)
	{
		return IClientPtr( new TCPClient( clientArgsPtr));
	}

	return 0;
}
