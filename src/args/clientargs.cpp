#include "clientargs.h"

ClientArgs::ClientArgs( char* addressToConnect, char* portToConnect, char* transport, char* filePath):
	addressToConnect_( addressToConnect), portToConnect_( portToConnect), transport_( transport), filePath_( filePath)
{
}

std::ostream& operator<<( std::ostream& stream, ClientArgs* args)
{
	return stream << "addressToConnect_: " << args->addressToConnect_
				  << ", transport: " << args->transport_
				  << ", filePath: " << args->filePath_;
}

char* ClientArgs::getAddressToConnect() const
{
	return addressToConnect_;
}

char* ClientArgs::getPortToConnect() const
{
	return portToConnect_;
}

char* ClientArgs::getTransport() const
{
	return transport_;
}

char* ClientArgs::getFilePath() const
{
	return filePath_;
}
