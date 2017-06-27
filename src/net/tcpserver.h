#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <memory>
#include <iostream>
#include "iserver.h"

class TCPServer: public IServer{
public:
	TCPServer( ServerArgsPtr serverArgsPtr);

private:
	ServerArgsPtr serverArgsPtr_;
};

typedef std::shared_ptr<TCPServer> TCPServerPtr;

#endif // TCPSERVER_H
