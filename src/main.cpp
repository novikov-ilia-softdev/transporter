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
		std::cout << "server" << std::endl;
		std::cout << serverArgsPtr << std::endl;
		IServerPtr serverPtr = netEndpointCreator.createServer( serverArgsPtr);
		serverPtr->run();
		return 0;
	}

	ClientArgsPtr clientArgsPtr = argsParser.getClientArgs();
	if( clientArgsPtr)
	{
		std::cout << "client" << std::endl;
		std::cout << clientArgsPtr << std::endl;
		return 0;
	}

	std::cerr << "unknown args!" << std::endl;
}
