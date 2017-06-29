#include "argsparser.h"

const int ArgsParser::MODE_INDEX = 1;

const std::string ArgsParser::SERVER_MODE = "-s";
const int ArgsParser::SERVER_ARGS_COUNT = 4;
const int ArgsParser::SERVER_PORT_INDEX = 2;
const int ArgsParser::SERVER_TRANSPORT_INDEX = 3;

const std::string ArgsParser::CLIENT_MODE = "-c";
const int ArgsParser::CLIENT_ARGS_COUNT = 6;
const int ArgsParser::CLIENT_ADDRESS_TO_CONNECT_INDEX = 2;
const int ArgsParser::CLIENT_PORT_TO_CONNECT_INDEX = 3;
const int ArgsParser::CLIENT_TRASNPORT_INDEX = 4;
const int ArgsParser::CLIENT_FILE_INDEX = 5;

ArgsParser::ArgsParser( int argc, char* argv[]):
	argc_( argc), argv_( argv)
{
}

ServerArgsPtr ArgsParser::getServerArgs() const
{
	// ./transporter -s 12345 tcp
	if( argc_ == SERVER_ARGS_COUNT &&
		std::string( argv_[ MODE_INDEX]) == SERVER_MODE)
	{
		return ServerArgsPtr( new ServerArgs( argv_[ SERVER_PORT_INDEX],
											  argv_[ SERVER_TRANSPORT_INDEX]));
	}

	return 0;
}

ClientArgsPtr ArgsParser::getClientArgs() const
{
	// ./transporter -c 127.0.0.1 12345 tcp filePath
	if( argc_ == CLIENT_ARGS_COUNT &&
		std::string( argv_[ MODE_INDEX]) == CLIENT_MODE)
	{
		return ClientArgsPtr( new ClientArgs( argv_[ CLIENT_ADDRESS_TO_CONNECT_INDEX],
											  argv_[ CLIENT_PORT_TO_CONNECT_INDEX],
											  argv_[ CLIENT_TRASNPORT_INDEX],
											  argv_[ CLIENT_FILE_INDEX]));
	}

	return 0;
}
