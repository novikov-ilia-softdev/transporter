#include <iostream>
#include "args/argsparser.h"
#include "net/netendpointcreator.h"

int main( int argc, char* argv[])
{
	ArgsParser argsParser( argc, argv);
	NetEndpointCreator netEndpointCreator;

	ServerArgsPtr serverArgsPtr = argsParser.getServerArgs();
	if( serverArgsPtr)
	{
		IServerPtr serverPtr = netEndpointCreator.createServer( serverArgsPtr);
		serverPtr->run();
		return 0;
	}

	ClientArgsPtr clientArgsPtr = argsParser.getClientArgs();
	if( clientArgsPtr)
	{
		IClientPtr clientPtr = netEndpointCreator.createClient( clientArgsPtr);
		clientPtr->run();
		return 0;
	}

	std::cerr << "unknown args!" << std::endl;
}
