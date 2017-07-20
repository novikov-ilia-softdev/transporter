#include "tcpclient.h"
#include <iostream>

TCPClient::TCPClient( ClientArgsPtr clientArgsPtr):
	IClient( clientArgsPtr),
	clientArgsPtr_( clientArgsPtr),
	socket_( ioService_),
	resolver_( ioService_)
{
}

void TCPClient::run()
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

		std::cout << "connecting... ";
		boost::asio::connect( socket_, resolver_.resolve( { clientArgsPtr_->getAddressToConnect(), clientArgsPtr_->getPortToConnect() } ));
		std::cout << "OK!" << std::endl;

		std::cout << "writing... ";
		Buffers buffers = fileManager_.serialize( file);
		std::cout << buffers[ 0].get() << std::endl;
		boost::asio::write( socket_, buffers);
		std::cout << "OK!" << std::endl;
	}
	catch( std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
