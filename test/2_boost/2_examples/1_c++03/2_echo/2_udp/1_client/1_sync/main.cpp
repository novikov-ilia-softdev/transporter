// g++ -o client.out main.cpp -lboost_system -lpthread

#include <iostream>
#include <boost/asio.hpp>

enum { maxLength = 1024 };

int main( int argc, char* argv[])
{
	try
	{
		if (argc != 3)
		{
			std::cerr << "Usage: blocking_boost::asio::ip::udp_echo_client <host> <port>\n";
			return 1;
		}

		boost::asio::io_service ioService;
		boost::asio::ip::udp::socket socket( ioService, boost::asio::ip::udp::endpoint( boost::asio::ip::udp::v4(), 0));
		boost::asio::ip::udp::resolver resolver( ioService);
		boost::asio::ip::udp::resolver::query query( boost::asio::ip::udp::v4(), argv[1], argv[2]);
		boost::asio::ip::udp::resolver::iterator iterator = resolver.resolve( query);

		std::cout << "Enter message: ";
		char request[ maxLength];
		std::cin.getline( request, maxLength);
		size_t request_length = strlen( request);
		socket.send_to( boost::asio::buffer( request, request_length), *iterator);

		char reply[ maxLength];
		boost::asio::ip::udp::endpoint senderEndpoint;
		size_t reply_length = socket.receive_from( boost::asio::buffer( reply, maxLength), senderEndpoint);
		std::cout << "Reply is: ";
		std::cout.write( reply, reply_length);
		std::cout << "\n";
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
