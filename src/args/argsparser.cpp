#include "argsparser.h"
#include <iostream>

const int ArgsParser::MODE_INDEX = 1;
const int ArgsParser::SERVER_ARGS_COUNT = 4;
const int ArgsParser::CLIENT_ARGS_COUNT = 5;

ArgsParser::ArgsParser( int argc, char* argv[]):
	argc_( argc), argv_( argv)
{
}

bool ArgsParser::isClient() const
{
	// -c ip:port tcp/udp file
	return ( argc_ == CLIENT_ARGS_COUNT &&
			 std::string( argv_[ MODE_INDEX]) == "-c");
}

ServerArgs* ArgsParser::getServerArgs() const
{
	// -s port tcp/udp
	if( argc_ == SERVER_ARGS_COUNT &&
		std::string( argv_[ MODE_INDEX]) == "-s")
	{
		return new ServerArgs( argc_, argv_);
	}

	return 0;
}
