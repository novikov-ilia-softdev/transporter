#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "server.h"

Server::Server( boost::asio::io_service& ioService, short port):
	socket_( ioService, boost::asio::ip::udp::endpoint( boost::asio::ip::udp::v4(), port))
{
	socket_.async_receive_from( boost::asio::buffer( data_, maxLength),
								senderEndpoint_,
								boost::bind( &Server::handleReceiveFrom,
											 this,
											 boost::asio::placeholders::error,
											 boost::asio::placeholders::bytes_transferred));
}

void Server::handleReceiveFrom( const boost::system::error_code& error, size_t bytesRecvd)
{
	if (!error && bytesRecvd > 0)
	{
		socket_.async_send_to( boost::asio::buffer( data_, bytesRecvd),
													senderEndpoint_,
													boost::bind( &Server::handleSendTo,
																 this,
																 boost::asio::placeholders::error,
																 boost::asio::placeholders::bytes_transferred));
	}
	else
	{
		socket_.async_receive_from( boost::asio::buffer( data_, maxLength),
									senderEndpoint_,
									boost::bind( &Server::handleReceiveFrom,
												 this,
												 boost::asio::placeholders::error,
												 boost::asio::placeholders::bytes_transferred));
	}
}

void Server::handleSendTo(const boost::system::error_code& error, size_t bytesSent)
{
	socket_.async_receive_from( boost::asio::buffer( data_, maxLength),
								senderEndpoint_,
								boost::bind( &Server::handleReceiveFrom,
											 this,
											 boost::asio::placeholders::error,
											 boost::asio::placeholders::bytes_transferred));
}

