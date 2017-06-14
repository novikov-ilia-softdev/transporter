// g++ -std=c++11 -o server.out main.cpp -lboost_system -lboost_thead

#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <boost/asio.hpp>

const int maxLength = 1024;

void session( boost::asio::ip::tcp::socket sock)
{
	try
	{
		for (;;)
		{
			char data[ maxLength];

			boost::system::error_code error;
			size_t length = sock.read_some( boost::asio::buffer( data), error);
			if (error == boost::asio::error::eof)
				break;
			else if (error)
				throw boost::system::system_error(error);

			boost::asio::write( sock, boost::asio::buffer( data, length));
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception in thread: " << e.what() << "\n";
	}
}

void server( boost::asio::io_service& ioService, unsigned short port)
{
	boost::asio::ip::tcp::acceptor accept( ioService, boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), port));
	for (;;)
	{
		boost::asio::ip::tcp::socket sock( ioService);
		accept.accept( sock);
		std::thread( session, std::move( sock)).detach();
	}
}

int main( int argc, char* argv[])
{
	try
	{
		if( argc != 2)
		{
			std::cerr << "Usage: blocking_tcp_echo_server <port>\n";
			return 1;
		}

		boost::asio::io_service ioService;
		server( ioService, std::atoi(argv[1]));
	}
	catch( std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
