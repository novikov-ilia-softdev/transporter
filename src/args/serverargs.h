#ifndef SERVERARGS_H
#define SERVERARGS_H

#include <ostream>

class ServerArgs{
public:
	ServerArgs( char* port, char* transport);
	friend std::ostream& operator<<( std::ostream& stream, ServerArgs* args);

private:
	char* port_;
	char* transport_;
};

#endif // SERVERARGS_H
