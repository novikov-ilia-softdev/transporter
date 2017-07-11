#include "tcpclient.h"
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include "message/message.h"

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
		File file = fileManager_.getFile( clientArgsPtr_->getFilePath());
		std::cout << "OK!" << std::endl;

		std::cout << "connecting... ";
		boost::asio::connect( socket_, resolver_.resolve( { clientArgsPtr_->getAddressToConnect(), clientArgsPtr_->getPortToConnect() } ));
		std::cout << "OK!" << std::endl;

		std::ostringstream archiveStream;
		boost::archive::text_oarchive archive( archiveStream);
		archive << file;
		std::string outboundData;
		std::string outboundHeader;
		outboundData = archiveStream.str();

		std::ostringstream headerStream;

		const std::size_t headerLength = 8;

		headerStream << std::setw( Message::headerLength) << std::hex << outboundData.size();
		if (!headerStream || headerStream.str().size() != Message::headerLength)
		{
		  std::cout << "error" << std::endl;
		  return;
		}
		outboundHeader = headerStream.str();

		std::vector<boost::asio::const_buffer> buffers;
		buffers.push_back(boost::asio::buffer( outboundHeader));
		buffers.push_back(boost::asio::buffer( outboundData));
		std::cout << "writing... ";
		boost::asio::write( socket_, buffers);
		std::cout << "OK!" << std::endl;
	}
	catch( std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
