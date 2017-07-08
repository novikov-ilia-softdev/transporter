#include "tcpclient.h"
#include <iostream>
#include "file/filemanager.h"
#include <boost/archive/text_oarchive.hpp>

TCPClient::TCPClient( ClientArgsPtr clientArgsPtr):
	IClient( clientArgsPtr),
	clientArgsPtr_( clientArgsPtr),
	socket_( ioService_),
	resolver_( ioService_)
{
	std::cout << "TCPClient" << std::endl;
}
/*
void TCPClient::run()
{
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
*/
void TCPClient::run()
{
	try
	{
		FileManager fileManager;
		File file = fileManager.getFile( clientArgsPtr_->getFilePath());

		std::cout << "connecting... ";
		boost::asio::connect( socket_, resolver_.resolve( { clientArgsPtr_->getAddressToConnect(), clientArgsPtr_->getPortToConnect() } ));
		std::cout << "OK!" << std::endl;

		// Serialize the data first so we know how large it is.

		std::ostringstream archive_stream;
		boost::archive::text_oarchive archive(archive_stream);
		archive << file;
		std::string outbound_data_;
		std::string outbound_header_;
		outbound_data_ = archive_stream.str();

		// Format the header.
		std::ostringstream header_stream;

		const std::size_t header_length = 8;

		header_stream << std::setw(header_length) << std::hex << outbound_data_.size();
		if (!header_stream || header_stream.str().size() != header_length)
		{
		  std::cout << "error" << std::endl;
		  return;
		}
		outbound_header_ = header_stream.str();

		// Write the serialized data to the socket. We use "gather-write" to send
		// both the header and the data in a single write operation.
		std::vector<boost::asio::const_buffer> buffers;
		buffers.push_back(boost::asio::buffer(outbound_header_));
		buffers.push_back(boost::asio::buffer(outbound_data_));
		std::cout << "writing... ";
		boost::asio::write(socket_, buffers);
		std::cout << "OK!" << std::endl;

		std::cout << file << std::endl;
	}
	catch( std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
