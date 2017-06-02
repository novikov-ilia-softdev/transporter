#ifndef TCPCONNECTION
#define TCPCONNECTION

#include "utils.h"
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

class tcp_connection: public boost::enable_shared_from_this<tcp_connection>
{
public:
	typedef boost::shared_ptr<tcp_connection> pointer;

	static pointer create( boost::asio::io_service& io_service)
	{
		return pointer( new tcp_connection( io_service));
	}

	boost::asio::ip::tcp::socket& socket()
	{
		return socket_;
	}

	void start()
	{
		message_ = make_daytime_string();

		boost::asio::async_write( socket_, boost::asio::buffer(message_),
				boost::bind( &tcp_connection::handle_write, shared_from_this(),
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
	}

private:
	tcp_connection(boost::asio::io_service& io_service): socket_(io_service)
	{
	}

	void handle_write(const boost::system::error_code&, size_t)
	{
	}

	boost::asio::ip::tcp::socket socket_;
	std::string message_;
};

#endif // TCPCONNECTION
