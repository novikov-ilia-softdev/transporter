#ifndef ARGSPARSER_H
#define ARGSPARSER_H

#include "serverargs.h"

class ArgsParser{
public:
	ArgsParser( int argc, char** argv);
	bool isClient() const;
	ServerArgs* getServerArgs() const;

private:
	static const int MODE_INDEX;
	static const int SERVER_ARGS_COUNT;
	static const int CLIENT_ARGS_COUNT;

	int argc_;
	char** argv_;
};

#endif // ARGSPARSER_H
