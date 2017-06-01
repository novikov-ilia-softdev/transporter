// g++ -o server.out main.cpp -lboost_system

#include "tcpserver.h"
#include "udpserver.h"
#include <iostream>
#include <boost/asio.hpp>

int main()
{
	try
	{
		boost::asio::io_service io_service;
		tcp_server tcpServer( io_service);
		udp_server udpServer( io_service);
		io_service.run();
	}
	catch ( std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
