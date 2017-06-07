// g++ -std=c++11 -o client.out main.cpp client.cpp ../message/message.cpp -lboost_system -lpthread

#include <iostream>
#include <boost/asio.hpp>
#include <thread>

#include "../message/message.h"
#include "client.h"

int main( int argc, char* argv[])
{
	try
	{
		if ( argc != 3)
		{
			std::cerr << "Usage: client <host> <port>\n";
			return 1;
		}

		boost::asio::io_service ioService;

		boost::asio::ip::tcp::resolver resolver( ioService);
		boost::asio::ip::tcp::resolver::query query( argv[1], argv[2]);
		boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve( query);

		Client client( ioService, iterator);

		std::thread thread( [ &ioService]() { ioService.run(); });

		char line[ Message::maxBodyLength + 1];
		while ( std::cin.getline( line, Message::maxBodyLength + 1))
		{
			Message msg;
			msg.setBodyLength( strlen( line));
			memcpy( msg.getBody(), line, msg.getBodyLength());
			msg.encodeHeader();
			client.write( msg);
		}

		client.close();
		thread.join();

	}
	catch ( std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
