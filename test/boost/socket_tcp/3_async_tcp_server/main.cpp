// g++ -o server.out main.cpp -lboost_system

#include "tcpserver.h"
#include <iostream>

int main()
{
	try
	{
		boost::asio::io_service io_service;
		tcp_server server(io_service);
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
