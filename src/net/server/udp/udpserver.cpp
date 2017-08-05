#include "udpserver.h"
#include <iostream>
#include "file/file.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

const unsigned int UDPServer::INBOUND_DATA_BUFFER_SIZE = 1024 * 1024 * 1024 * 5; // 5Gb

UDPServer::UDPServer( ServerArgsPtr serverArgsPtr):
	IServer( serverArgsPtr),
	serverArgsPtr_( serverArgsPtr),
	socket_( ioService_, boost::asio::ip::udp::endpoint( boost::asio::ip::udp::v4(), std::atoi( serverArgsPtr->getPort()))),
	inboundData_( INBOUND_DATA_BUFFER_SIZE)
{
	receive_();
}

void UDPServer::run()
{
	ioService_.run();
}

void UDPServer::receive_()
{
	std::cout << "waiting for receive..." << std::endl;
	socket_.async_receive_from( boost::asio::buffer( inboundData_),
								senderEndpoint_,
								[ this](boost::system::error_code error, std::size_t bytesRecvd)
								{
									if (!error && bytesRecvd > 0)
									{
										try
										{
											std::string archiveData( &inboundData_[Message::headerLength], inboundData_.size());
											std::istringstream archiveStream( archiveData);
											boost::archive::text_iarchive archive( archiveStream);
											File file;
											archive >> file;
											std::cout << "received file " << file.getName() << std::endl;
											fileManager_.createFile( file);
										}
										catch( std::exception& e)
										{
											std::cerr << "Exception: " << e.what() << "\n";
										}
									}

									receive_();
								});
}
