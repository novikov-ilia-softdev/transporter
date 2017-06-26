#include "argsparser.h"

const int ArgsParser::MODE_INDEX = 1;

const int ArgsParser::SERVER_ARGS_COUNT = 4;
const int ArgsParser::SERVER_PORT_INDEX = 2;
const int ArgsParser::SERVER_TRANSPORT_INDEX = 3;

const int ArgsParser::CLIENT_ARGS_COUNT = 5;
const int ArgsParser::CLIENT_ADDRESS_TO_CONNECT_INDEX = 2;
const int ArgsParser::CLIENT_TRASNPORT_INDEX = 3;
const int ArgsParser::CLIENT_FILE_INDEX = 4;

ArgsParser::ArgsParser( int argc, char* argv[]):
	argc_( argc), argv_( argv)
{
}

ServerArgsPtr ArgsParser::getServerArgs() const
{
	// ./transporter -s port tcp/udp
	if( argc_ == SERVER_ARGS_COUNT &&
		std::string( argv_[ MODE_INDEX]) == "-s")
	{
		return ServerArgsPtr( new ServerArgs( argv_[ SERVER_PORT_INDEX],
											  argv_[ SERVER_TRANSPORT_INDEX]));
	}

	return 0;
}

ClientArgsPtr ArgsParser::getClientArgs() const
{
	// ./transporter -c ip:port tcp/udp file
	if( argc_ == CLIENT_ARGS_COUNT &&
		std::string( argv_[ MODE_INDEX]) == "-c")
	{
		return ClientArgsPtr( new ClientArgs( argv_[ CLIENT_ADDRESS_TO_CONNECT_INDEX],
											  argv_[ CLIENT_TRASNPORT_INDEX],
											  argv_[ CLIENT_FILE_INDEX]));
	}

	return 0;
}
