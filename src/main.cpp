#include <iostream>
#include "args/argsparser.h"

int main( int argc, char* argv[])
{
	ArgsParser argsParser( argc, argv);

	ServerArgsPtr serverArgsPtr = argsParser.getServerArgs();
	if( serverArgsPtr)
	{
		std::cout << "server" << std::endl;
		std::cout << serverArgsPtr << std::endl;
	}

	/*
	if( argsParser.isClient())
	{
		std::cout << "client" << std::endl;
	}
	*/
}
