#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>

class Server
{
public:
	Server( boost::asio::io_service& ioService, short port);
	void handleReceiveFrom( const boost::system::error_code& error, size_t bytesRecvd);
	void handleSendTo( const boost::system::error_code& error, size_t bytesSent);

private:
	boost::asio::ip::udp::socket socket_;
	boost::asio::ip::udp::endpoint senderEndpoint_;
	enum { maxLength = 1024 };
	char data_[maxLength];
};

#endif // SERVER_H
