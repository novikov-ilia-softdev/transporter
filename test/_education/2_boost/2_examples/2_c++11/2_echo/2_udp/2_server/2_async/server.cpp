#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "server.h"

Server::Server( boost::asio::io_service& ioService, short port):
	socket_( ioService, boost::asio::ip::udp::endpoint( boost::asio::ip::udp::v4(), port))
{
	receive_();
}

void Server::receive_()
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

void Server::send_( std::size_t length)
{
	socket_.async_send_to( boost::asio::buffer( data_, length),
						   senderEndpoint_,
						   [ this](boost::system::error_code error, std::size_t bytesSent)
						   {
								receive_();
						   });
}
