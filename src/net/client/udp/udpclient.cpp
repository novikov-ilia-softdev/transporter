#include "udpclient.h"
#include <iostream>

UDPClient::UDPClient( ClientArgsPtr clientArgsPtr):
	IClient( clientArgsPtr),
	clientArgsPtr_( clientArgsPtr),
	socket_( ioService_, boost::asio::ip::udp::endpoint( boost::asio::ip::udp::v4(), 0)),
	resolver_( ioService_)
{
}

void UDPClient::run()
{
	try
	{
		std::cout << "reading file... ";
		FilePtr file = fileManager_.getFile( clientArgsPtr_->getFilePath());
		if( !file)
		{
			std::cout << "error!" << std::endl;
			return;
		}
		std::cout << "OK!" << std::endl;

		std::cout << "writing... ";
		boost::asio::ip::udp::endpoint endpoint = *resolver_.resolve({boost::asio::ip::udp::v4(), clientArgsPtr_->getAddressToConnect(), clientArgsPtr_->getPortToConnect()});
		socket_.send_to( fileManager_.serialize( file), endpoint);
		std::cout << "OK!" << std::endl;
	}
	catch( std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
