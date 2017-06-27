#ifndef ARGSPARSER_H
#define ARGSPARSER_H

#include "serverargs.h"
#include "clientargs.h"

class ArgsParser{
public:
	ArgsParser( int argc, char** argv);
	bool isClient() const;
	ServerArgsPtr getServerArgs() const;
	ClientArgsPtr getClientArgs() const;

private:
	static const int MODE_INDEX;

	static const std::string SERVER_MODE;
	static const int SERVER_ARGS_COUNT;
	static const int SERVER_PORT_INDEX;
	static const int SERVER_TRANSPORT_INDEX;

	static const std::string CLIENT_MODE;
	static const int CLIENT_ARGS_COUNT;
	static const int CLIENT_ADDRESS_TO_CONNECT_INDEX;
	static const int CLIENT_TRASNPORT_INDEX;
	static const int CLIENT_FILE_INDEX;

	int argc_;
	char** argv_;
};

#endif // ARGSPARSER_H
