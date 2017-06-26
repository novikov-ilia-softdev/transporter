#include "clientargs.h"

ClientArgs::ClientArgs( char* addressToConnect, char* transport, char* filePath):
	addressToConnect_( addressToConnect), transport_( transport), filePath_( filePath)
{
}

std::ostream& operator<<( std::ostream& stream, ClientArgs* args)
{
	return stream << "addressToConnect_: " << args->addressToConnect_
				  << ", transport: " << args->transport_
				  << ", filePath: " << args->filePath_;
}
