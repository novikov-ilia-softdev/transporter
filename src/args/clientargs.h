#ifndef CLIENTARGS_H
#define CLIENTARGS_H

#include <ostream>
#include <memory>

class ClientArgs{
public:
	ClientArgs( char* addressToConnect, char* portToConnect, char* transport, char* filePath);
	char* getAddressToConnect() const;
	char* getPortToConnect() const;
	char* getTransport() const;
	char* getFilePath() const;
	friend std::ostream& operator<<( std::ostream& stream, ClientArgs* args);

private:
	char* addressToConnect_;
	char* portToConnect_;
	char* transport_;
	char* filePath_;
};

typedef std::shared_ptr<ClientArgs> ClientArgsPtr;

#endif // CLIENTARGS_H
