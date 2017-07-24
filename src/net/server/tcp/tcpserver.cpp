#include "tcpserver.h"
#include "session.h"
#include <iostream>

TCPServer::TCPServer( ServerArgsPtr serverArgsPtr):
	IServer( serverArgsPtr),
	serverArgsPtr_( serverArgsPtr),
	acceptor_( ioService_,
			  boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(),
					  	  	  	  	  	  	  std::atoi( serverArgsPtr->getPort()))),
	socket_( ioService_)
{
	accept_();
}

void TCPServer::run()
{
	ioService_.run();
}

void TCPServer::accept_()
{
	std::cout << "accepting..." << std::endl;
	acceptor_.async_accept( socket_,
							[ this]( boost::system::error_code ec)
							{
								if( !ec)
								{
									std::cout << "connected " << socket_.remote_endpoint().address().to_string() << std::endl;
									std::make_shared<Session>( std::move( socket_))->start();
								}

								accept_();
							});
}
