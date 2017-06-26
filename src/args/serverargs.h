#ifndef SERVERARGS_H
#define SERVERARGS_H

class ServerArgs{
public:
	ServerArgs( int argc, char** argv);

private:
	int argc_;
	char** argv_;

	char* port_;
	char* transport_;
};

#endif // SERVERARGS_H
