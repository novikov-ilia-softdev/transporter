#include "server.h"
#include "session.h"

Server::Server( boost::asio::io_service& ioService, const boost::asio::ip::tcp::endpoint& endpoint)
	: acceptor_( ioService, endpoint), socket_( ioService)
{
	accept_();
}

void Server::accept_()
{
	acceptor_.async_accept( socket_,
							[this](boost::system::error_code ec)
							{
								  if( !ec)
								  {
									  std::make_shared<Session>( std::move( socket_), room_)->start();
								  }

								  accept_();
							});
}
