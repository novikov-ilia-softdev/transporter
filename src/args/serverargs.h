#ifndef SERVERARGS_H
#define SERVERARGS_H

#include <ostream>
#include <memory>

class ServerArgs{
public:
	ServerArgs( char* port, char* transport);
	char* getTransport() const;
	friend std::ostream& operator<<( std::ostream& stream, ServerArgs* args);

private:
	char* port_;
	char* transport_;
};

typedef std::shared_ptr<ServerArgs> ServerArgsPtr;

#endif // SERVERARGS_H
