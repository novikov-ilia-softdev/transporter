// g++ -std=c++11 -o server.out main.cpp -lboost_system

#include <iostream>
#include <boost/asio.hpp>

enum { maxLength = 1024 };

void server( boost::asio::io_service& io_service, unsigned short port)
{
	boost::asio::ip::udp::socket sock( io_service, boost::asio::ip::udp::endpoint( boost::asio::ip::udp::v4(), port));
	for (;;)
	{
		char data[ maxLength];
		boost::asio::ip::udp::endpoint senderEndpoint;
		size_t length = sock.receive_from( boost::asio::buffer( data, maxLength), senderEndpoint);
		sock.send_to( boost::asio::buffer( data, length), senderEndpoint);
	}
}

int main( int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: blocking_boost::asio::ip::udp_echo_server <port>\n";
			return 1;
		}

		boost::asio::io_service ioService;
		server( ioService, std::atoi(argv[1]));
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
