#include "tcpclient.h"
#include <iostream>
#include "file/filemanager.h"

TCPClient::TCPClient( ClientArgsPtr clientArgsPtr):
	IClient( clientArgsPtr),
	clientArgsPtr_( clientArgsPtr),
	socket_( ioService_),
	resolver_( ioService_)
{
	std::cout << "TCPClient" << std::endl;
}

void TCPClient::run()
{
	FileManager fileManager;
	File file = fileManager.getFile( clientArgsPtr_->getFilePath());

	try
	{
		boost::asio::connect( socket_, resolver_.resolve( { clientArgsPtr_->getAddressToConnect(), clientArgsPtr_->getPortToConnect() } ));

		std::cout << "Enter message: ";
		char request[ maxLength_];
		std::cin.getline( request, maxLength_);
		size_t requestLength = strlen( request);
		boost::asio::write( socket_, boost::asio::buffer( request, requestLength));

		char reply[ maxLength_];
		size_t replyLength = boost::asio::read( socket_,
												boost::asio::buffer( reply, requestLength));
		std::cout << "Reply is: ";
		std::cout.write( reply, replyLength);
		std::cout << "\n";
	}
	catch( std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
