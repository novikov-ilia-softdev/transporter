#include "udpserver.h"
#include <iostream>

UDPServer::UDPServer( ServerArgsPtr serverArgsPtr):
	IServer( serverArgsPtr),
	serverArgsPtr_( serverArgsPtr),
	socket_( ioService_, boost::asio::ip::udp::endpoint( boost::asio::ip::udp::v4(), std::atoi( serverArgsPtr->getPort())))
{
	receive_();
}

void UDPServer::run()
{
	std::cout << "UDPServer::run()" << std::endl;
	ioService_.run();
}

void UDPServer::receive_()
{
	socket_.async_receive_from( boost::asio::buffer( data_, maxLength),
									senderEndpoint_,
									[ this](boost::system::error_code error, std::size_t bytesRecvd)
									{
										if (!error && bytesRecvd > 0)
										{
											send_( bytesRecvd);
										}
										else
										{
											receive_();
										}
									});
}
