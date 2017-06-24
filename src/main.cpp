#include <iostream>
#include "args/argsparser.h"

int main( int argc, char* argv[])
{
	ArgsParser argsParser( argc, argv);

	if( argsParser.isServer())
	{
		std::cout << "server" << std::endl;
	}

	if( argsParser.isClient())
	{
		std::cout << "client" << std::endl;
	}
}
