#ifndef ARGSPARSER_H
#define ARGSPARSER_H

class ArgsParser{
public:
	ArgsParser( int argc, char** argv);
	bool isServer() const;
	bool isClient() const;

private:
	static const int MODE_INDEX;
	static const int SERVER_ARGS_COUNT;
	static const int CLIENT_ARGS_COUNT;

	int argc_;
	char** argv_;
};

#endif // ARGSPARSER_H
