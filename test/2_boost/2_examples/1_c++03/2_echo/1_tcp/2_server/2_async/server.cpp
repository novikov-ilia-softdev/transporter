#include "server.h"
#include <boost/bind.hpp>

Server::Server( boost::asio::io_service& ioService, short port):
	ioService_(ioService),
	acceptor_( ioService,
			   boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), port))
{
	startAccept_();
}

void Server::startAccept_()
{
	Session* newSession = new Session( ioService_);
	acceptor_.async_accept( newSession->getSocket(),
							boost::bind( &Server::handleAccept_,
										 this,
										 newSession,
										 boost::asio::placeholders::error));
}

void Server::handleAccept_( Session* newSession, const boost::system::error_code& error)
{
	if (!error)
	{
		newSession->start();
	}
	else
	{
		delete newSession;
	}

	startAccept_();
}
