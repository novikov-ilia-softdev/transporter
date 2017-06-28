#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <memory>
#include <iostream>
#include <boost/asio.hpp>
#include "iserver.h"

class TCPServer: public IServer{
public:
	TCPServer( ServerArgsPtr serverArgsPtr);
	void run();

private:
	void accept_();

private:
	ServerArgsPtr serverArgsPtr_;
	boost::asio::io_service ioService_;
	boost::asio::ip::tcp::acceptor acceptor_;
	boost::asio::ip::tcp::socket socket_;
};

typedef std::shared_ptr<TCPServer> TCPServerPtr;

#endif // TCPSERVER_H
