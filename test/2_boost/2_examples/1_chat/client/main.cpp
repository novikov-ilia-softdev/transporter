// g++ -o client.out main.cpp chatclient.cpp -lboost_system -lboost_thread -lpthread

#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include "../message/chatmessage.hpp"
#include "chatclient.h"

int main( int argc, char* argv[])
{
	try
	{
		if ( argc != 3)
		{
			std::cerr << "Usage: ChatClient <host> <port>\n";
			return 1;
		}

		boost::asio::io_service io_service;

		boost::asio::ip::tcp::resolver resolver( io_service);
		boost::asio::ip::tcp::resolver::query query( argv[1], argv[2]);
		boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve( query);

		ChatClient c( io_service, iterator);

		boost::thread t( boost::bind( &boost::asio::io_service::run, &io_service));

		char line[ chatMessage::max_body_length + 1];
		while ( std::cin.getline( line, chatMessage::max_body_length + 1))
		{
			chatMessage msg;
			msg.body_length( strlen(line));
			memcpy(msg.body(), line, msg.body_length());
			msg.encode_header();
			c.write( msg);
		}

		c.close();
		t.join();

	}
	catch ( std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
