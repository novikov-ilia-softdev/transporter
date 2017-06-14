#include "server.h"
#include "session.h"
#include <boost/bind.hpp>

Server::Server( boost::asio::io_service& ioService, short port):
	acceptor_( ioService, boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), port)),
	socket_( ioService)
{
	accept_();
}

void Server::accept_()
{
	acceptor_.async_accept( socket_,
							[ this]( boost::system::error_code ec)
							{
								if( !ec)
								{
									std::make_shared<Session>( std::move( socket_))->start();
								}

								accept_();
							});
}
