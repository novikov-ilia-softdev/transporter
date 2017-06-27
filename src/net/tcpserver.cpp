#include "tcpserver.h"

TCPServer::TCPServer( ServerArgsPtr serverArgsPtr):
	IServer( serverArgsPtr)
{
	std::cout << "TCPServer" << std::endl;
}

void TCPServer::run()
{
	std::cout << "TCPServer::run" << std::endl;
}
