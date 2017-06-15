// g++ -o server.out main.cpp server.cpp session.cpp room.cpp ../message/message.cpp -lboost_system

#include <boost/asio.hpp>
#include <iostream>
#include "server.h"

int main( int argc, char* argv[])
{
	try
	{
		if ( argc < 2)
		{
			std::cerr << "Usage: chat_server <port> [<port> ...]\n";
			return 1;
		}

		boost::asio::io_service ioService;

		ServerList servers;
		for ( int i = 1; i < argc; ++i)
		{
			boost::asio::ip::tcp::endpoint endpoint( boost::asio::ip::tcp::v4(), atoi( argv[i]));
			ServerPtr server( new Server( ioService, endpoint));
			servers.push_back( server);
		}

		ioService.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
