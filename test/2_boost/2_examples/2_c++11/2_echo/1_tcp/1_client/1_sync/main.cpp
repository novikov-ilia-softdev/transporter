// g++ -o client.out main.cpp -lboost_system -lpthread

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

enum { maxLength = 1024 };

int main(int argc, char* argv[])
{
	try
	{
		if( argc != 3)
		{
			std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
			return 1;
		}

		boost::asio::io_service ioService;

		boost::asio::ip::tcp::resolver resolver( ioService);
		boost::asio::ip::tcp::resolver::query query( boost::asio::ip::tcp::v4(), argv[1], argv[2]);
		boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve( query);

		boost::asio::ip::tcp::socket socket( ioService);
		boost::asio::connect( socket, iterator);

		std::cout << "Enter message: ";
		char request[ maxLength];
		std::cin.getline( request, maxLength);
		size_t requestLength = strlen( request);
		boost::asio::write( socket, boost::asio::buffer( request, requestLength));

		char reply[ maxLength];
		size_t replyLength = boost::asio::read( socket,
												boost::asio::buffer( reply, requestLength));
		std::cout << "Reply is: ";
		std::cout.write( reply, replyLength);
		std::cout << "\n";
	}
	catch( std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
