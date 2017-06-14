#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>

class Server
{
public:
	Server( boost::asio::io_service& ioService, short port);
	void receive_();
	void send_( std::size_t length);

private:
	boost::asio::ip::udp::socket socket_;
	boost::asio::ip::udp::endpoint senderEndpoint_;
	enum { maxLength = 1024 };
	char data_[maxLength];
};

#endif // SERVER_H
