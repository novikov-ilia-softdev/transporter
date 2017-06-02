// g++ -o server.out main.cpp -lboost_system

#include "udpserver.h"
#include <iostream>
#include <boost/asio.hpp>

int main()
{
	try
	{
		boost::asio::io_service io_service;
		udp_server server( io_service);
		io_service.run();
	}
	catch ( std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
