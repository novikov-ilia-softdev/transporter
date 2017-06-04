// g++ -o client.out main.cpp chatclient.cpp ../message/chatmessage.cpp -lboost_system -lboost_thread -lpthread

#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include "../message/chatmessage.h"
#include "chatclient.h"

int main( int argc, char* argv[])
{
	try
	{
		if ( argc != 3)
		{
			std::cerr << "Usage: client <host> <port>\n";
			return 1;
		}

		boost::asio::io_service io_service;

		boost::asio::ip::tcp::resolver resolver( io_service);
		boost::asio::ip::tcp::resolver::query query( argv[1], argv[2]);
		boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve( query);

		ChatClient client( io_service, iterator);

		boost::thread thread( boost::bind( &boost::asio::io_service::run, &io_service));

		char line[ chatMessage::maxBodyLength + 1];
		while ( std::cin.getline( line, chatMessage::maxBodyLength + 1))
		{
			chatMessage msg;
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
