#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include "session.h"

class Server
{
public:
	Server( boost::asio::io_service& ioService, short port);

private:
	void startAccept_();
	void handleAccept_( Session* newSession, const boost::system::error_code& error);

private:
	boost::asio::io_service& ioService_;
	boost::asio::ip::tcp::acceptor acceptor_;
};

#endif // SERVER_H
