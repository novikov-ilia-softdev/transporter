#include <iostream>
#include <boost/asio.hpp>

// g++ -o client.out client.cpp -lboost_system

void connect_handler( const boost::system::error_code& err);

int main()
{
	boost::asio::io_service service;
	boost::asio::ip::tcp::socket socket( service);

	const std::string remoteAddress = "127.0.0.1";
	const int remotePort = 2001;
	boost::asio::ip::tcp::endpoint endpoint( boost::asio::ip::address::from_string( remoteAddress.c_str()), remotePort);

	socket.async_connect( endpoint, connect_handler);
	service.run();
}

void connect_handler( const boost::system::error_code& err)
{
	if( !err)
	{
		std::cout << "connected!" << std::endl;
		//const std::string str = "Hello, world!";
		//boost::asio::write( socket, boost::asio::buffer( str.c_str(), str.length()));
		//socket.close();
	}
	else
	{
		std::cout << "error connection!" << std::endl;
	}
}

/*

try
	{


	}
	catch( boost::system::system_error& err)
	{
		std::cout << "exception:" << std::endl;
		std::cout << err.what() << std::endl;
	}


 */
