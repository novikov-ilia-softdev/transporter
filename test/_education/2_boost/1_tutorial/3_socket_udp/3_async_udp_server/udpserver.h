#ifndef UDPSERVER
#define UDPSERVER

#include <ctime>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

std::string make_daytime_string()
{
	std::time_t now = std::time(0);
	return std::ctime(&now);
}

class udp_server
{
public:
	udp_server( boost::asio::io_service& io_service) : socket_(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 13))
	{
		start_receive();
	}

private:
	void start_receive()
	{
		socket_.async_receive_from( boost::asio::buffer(recv_buffer_), remote_endpoint_, boost::bind( &udp_server::handle_receive,
																						 this,
																						 boost::asio::placeholders::error,
																						 boost::asio::placeholders::bytes_transferred));
	}

	void handle_receive(const boost::system::error_code& error, std::size_t)
	{
		if (!error || error == boost::asio::error::message_size)
		{
			boost::shared_ptr<std::string> message( new std::string(make_daytime_string()));

			socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_, boost::bind( &udp_server::handle_send,
																							    this,
																							    message,
																							    boost::asio::placeholders::error,
																							    boost::asio::placeholders::bytes_transferred));

			start_receive();
		}
	}

	void handle_send(boost::shared_ptr<std::string>, const boost::system::error_code&, std::size_t /*bytes_transferred*/)
	{
	}

	boost::asio::ip::udp::socket socket_;
	boost::asio::ip::udp::endpoint remote_endpoint_;
	boost::array<char, 1> recv_buffer_;
};


#endif // UDPSERVER
