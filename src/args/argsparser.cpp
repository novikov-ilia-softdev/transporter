#include "argsparser.h"
#include <iostream>

const int ArgsParser::MODE_INDEX = 1;
const int ArgsParser::SERVER_ARGS_COUNT = 4;
const int ArgsParser::SERVER_PORT_INDEX = 2;
const int ArgsParser::SERVER_TRANSPORT_INDEX = 3;
const int ArgsParser::CLIENT_ARGS_COUNT = 5;

ArgsParser::ArgsParser( int argc, char* argv[]):
	argc_( argc), argv_( argv)
{
}

bool ArgsParser::isClient() const
{
	// transporter -c ip:port tcp/udp file
	return ( argc_ == CLIENT_ARGS_COUNT &&
			 std::string( argv_[ MODE_INDEX]) == "-c");
}

ServerArgs* ArgsParser::getServerArgs() const
{
	// transporter -s port tcp/udp
	if( argc_ == SERVER_ARGS_COUNT &&
		std::string( argv_[ MODE_INDEX]) == "-s")
	{
		return new ServerArgs( argv_[ SERVER_PORT_INDEX], argv_[ SERVER_TRANSPORT_INDEX]);
	}

	return 0;
}
