#include "netendpointcreator.h"
#include "server/tcp/tcpserver.h"
#include "server/udp/udpserver.h"
#include "client/tcp/tcpclient.h"
#include "client/udp/udpclient.h"
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

	if( std::string( serverArgsPtr->getTransport()) == Transport::UDP)
	{
		return IServerPtr( new UDPServer( serverArgsPtr));
	}

	return 0;
}

IClientPtr NetEndpointCreator::createClient( ClientArgsPtr clientArgsPtr)
{
	if( std::string( clientArgsPtr->getTransport()) == Transport::TCP)
	{
		return IClientPtr( new TCPClient( clientArgsPtr));
	}

	if( std::string( clientArgsPtr->getTransport()) == Transport::UDP)
	{
		return IClientPtr( new UDPClient( clientArgsPtr));
	}

	return 0;
}
