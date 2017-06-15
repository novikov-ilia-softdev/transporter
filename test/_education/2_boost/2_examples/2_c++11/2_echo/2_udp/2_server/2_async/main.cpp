// g++ -std=c++11 -o server.out main.cpp server.cpp -lboost_system

#include <iostream>
#include <boost/asio.hpp>
#include "server.h"

int main( int argc, char* argv[])
{
	try
	{
		if( argc != 2)
		{
			std::cerr << "Usage: async_udp_echo_server <port>\n";
			return 1;
		}

		boost::asio::io_service ioService;
		Server server( ioService, std::atoi(argv[1]));
		ioService.run();
	}
	catch( std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
