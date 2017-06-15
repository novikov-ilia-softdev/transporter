#ifndef SESSION_H
#define SESSION_H

#include <boost/asio.hpp>

class Session
{
public:
	Session( boost::asio::io_service& ioService);
	boost::asio::ip::tcp::socket& getSocket();
	void start();

private:
	void handleRead_( const boost::system::error_code& error, size_t bytesTransferred);
	void handleWrite_( const boost::system::error_code& error);

private:
	boost::asio::ip::tcp::socket socket_;
	enum { maxLength = 1024 };
	char data_[ maxLength];
};

#endif // SESSION_H
