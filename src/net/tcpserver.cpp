#include "tcpserver.h"

TCPServer::TCPServer( ServerArgsPtr serverArgsPtr):
	IServer( serverArgsPtr)
{
	std::cout << "TCPServer" << std::endl;
}
