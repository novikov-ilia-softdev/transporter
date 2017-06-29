#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include "iclient.h"

class TCPClient: public IClient{
public:
	TCPClient( ClientArgsPtr clientArgsPtr);
	void run();

private:
	enum { maxLength_ = 1024 };
	ClientArgsPtr clientArgsPtr_;
	boost::asio::io_service ioService_;
	boost::asio::ip::tcp::socket socket_;
	boost::asio::ip::tcp::resolver resolver_;
};

typedef std::shared_ptr<TCPClient> TCPClientPtr;

#endif // TCPCLIENT_H
