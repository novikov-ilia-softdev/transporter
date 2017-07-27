#include "udpclient.h"
#include <iostream>

UDPClient::UDPClient( ClientArgsPtr clientArgsPtr):
	IClient( clientArgsPtr),
	clientArgsPtr_( clientArgsPtr),
	socket_( ioService_),
	resolver_( ioService_)
{
}

void UDPClient::run()
{
	std::cout << "UDPClient::run" << std::endl;
}
