#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

// g++ -o client.out client.cpp -lboost_system -lboost_thread

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;
void connect_handler( socket_ptr socket, const boost::system::error_code& err);
void write_handler( const boost::system::error_code& error, std::size_t bytes_transferred, socket_ptr socket);

int main()
{
	boost::asio::io_service service;
	socket_ptr socket( new boost::asio::ip::tcp::socket( service));

	const std::string remoteAddress = "127.0.0.1";
	const int remotePort = 2001;
	boost::asio::ip::tcp::endpoint endpoint( boost::asio::ip::address::from_string( remoteAddress.c_str()), remotePort);

	socket->async_connect( endpoint, boost::bind( connect_handler, socket, boost::asio::placeholders::error));
	service.run();
}

void connect_handler( socket_ptr socket, const boost::system::error_code& err)
{
	if( err)
	{
		std::cout << "error connection!" << std::endl;
		return;
	}

	std::cout << "connected!" << std::endl;
	const std::string str = "Hello, world!";

	//boost::this_thread::sleep( boost::posix_time::milliseconds(5000));

	boost::asio::async_write( *socket,
							  boost::asio::buffer( str.c_str(), str.length()),
							  boost::bind( write_handler, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, socket));
}

void write_handler( const boost::system::error_code& error, std::size_t bytes_transferred, socket_ptr socket)
{
	if( error)
	{
		std::cout << "error write_handler!" << std::endl;
	}

	std::cout << "write_handler" << std::endl;
	std::cout << "bytes_transferred: " << bytes_transferred << std::endl;
	socket->close();
}
