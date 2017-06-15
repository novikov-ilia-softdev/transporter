#include "session.h"
#include <boost/bind.hpp>

Session::Session( boost::asio::io_service& ioService):
	socket_( ioService)
{
}

boost::asio::ip::tcp::socket& Session::getSocket()
{
	return socket_;
}

void Session::start()
{
	socket_.async_read_some( boost::asio::buffer( data_, maxLength),
							 boost::bind( &Session::handleRead_,
									 	  this,
										  boost::asio::placeholders::error,
										  boost::asio::placeholders::bytes_transferred));
}

void Session::handleRead_( const boost::system::error_code& error, size_t bytes_transferred)
{
	if( !error)
	{
		boost::asio::async_write( socket_,
								  boost::asio::buffer( data_, bytes_transferred),
								  boost::bind( &Session::handleWrite_,
										  	   this,
											   boost::asio::placeholders::error));
	}
	else
	{
		delete this;
	}
}

void Session::handleWrite_(const boost::system::error_code& error)
{
	if (!error)
	{
		socket_.async_read_some( boost::asio::buffer( data_, maxLength),
								 boost::bind( &Session::handleRead_,
										 	  this,
											  boost::asio::placeholders::error,
											  boost::asio::placeholders::bytes_transferred));
	}
	else
	{
		delete this;
	}
}
