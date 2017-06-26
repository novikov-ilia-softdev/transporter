#include <iostream>
#include "args/argsparser.h"
#include "args/serverargs.h"

int main( int argc, char* argv[])
{
	ArgsParser argsParser( argc, argv);

	ServerArgs* serverArgsPtr = argsParser.getServerArgs();
	if( serverArgsPtr)
	{
		std::cout << "server" << std::endl;
		//std::cout << "ServerArgs: " << serverArgs << std::endl;
	}

	if( argsParser.isClient())
	{
		std::cout << "client" << std::endl;
	}
}
