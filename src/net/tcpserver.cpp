#include "tcpserver.h"
#include "session.h"

TCPServer::TCPServer( ServerArgsPtr serverArgsPtr):
	IServer( serverArgsPtr),
	serverArgsPtr_( serverArgsPtr),
	acceptor_( ioService_,
			  boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(),
					  	  	  	  	  	  	  std::atoi( serverArgsPtr->getPort()))),
	socket_( ioService_)
{
	std::cout << "TCPServer" << std::endl;
	accept_();
}

void TCPServer::run()
{
	std::cout << "TCPServer::run before" << std::endl;
	ioService_.run();
	std::cout << "TCPServer::run after" << std::endl;
}

void TCPServer::accept_()
{
	acceptor_.async_accept( socket_,
							[ this]( boost::system::error_code ec)
							{
								if( !ec)
								{
									std::make_shared<Session>( std::move( socket_))->start();
									std::cout << "connected!" << std::endl;
								}

								accept_();
							});
}
