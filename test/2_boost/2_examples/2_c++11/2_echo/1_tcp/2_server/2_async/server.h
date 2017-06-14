#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>

class Server
{
public:
	Server( boost::asio::io_service& ioService, short port);

private:
	void accept_();

private:
	boost::asio::ip::tcp::acceptor acceptor_;
	boost::asio::ip::tcp::socket socket_;
};

#endif // SERVER_H
