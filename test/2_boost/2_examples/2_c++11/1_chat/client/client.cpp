#include <iostream>
#include "client.h"

Client::Client( boost::asio::io_service& ioService,
				boost::asio::ip::tcp::resolver::iterator endpointIterator)
				: ioService_( ioService),
				  socket_( ioService)
{
	connect_( endpointIterator);
}

void Client::write( const Message& msg)
{
	ioService_.post( boost::bind( &Client::doWrite_, this, msg));
}

void Client::close()
{
	ioService_.post( boost::bind( &Client::doClose_, this));
}

void Client::connect_( boost::asio::ip::tcp::resolver::iterator endpointIterator)
{
	boost::asio::async_connect( socket_,
								endpointIterator,
								[ this]( boost::system::error_code ec, boost::asio::ip::tcp::resolver::iterator endpointIterator)
								{
									if ( !ec)
									{
										readHeader_();
									}
								});
}

void Client::readHeader_()
{
	boost::asio::async_read( socket_,
							 boost::asio::buffer( readMsg_.getData(), Message::headerLength),
							 [ this]( boost::system::error_code ec, std::size_t length)
							 {
							   if( !ec && readMsg_.decodeHeader())
							   {
								   readBody_();
							   }
							   else
							   {
								 socket_.close();
							   }
							 });
}

void Client::readBody_()
{
	boost::asio::async_read( socket_,
							 boost::asio::buffer( readMsg_.getBody(), readMsg_.getBodyLength()),
							 [this](boost::system::error_code ec, std::size_t length)
							 {
								if (!ec)
								{
									std::cout.write( readMsg_.getBody(), readMsg_.getBodyLength());
									std::cout << "\n";
									readHeader_();
								}
								else
								{
									socket_.close();
								}
							 });
}

void Client::doWrite_( Message msg)
{
	bool writeInProgress = !writeMsgs_.empty();
	writeMsgs_.push_back(msg);
	if ( !writeInProgress)
	{
		boost::asio::async_write( socket_,
								  boost::asio::buffer( writeMsgs_.front().getData(),
								  writeMsgs_.front().getLength()),
								  boost::bind( &Client::handleWrite_, this, boost::asio::placeholders::error));
	}
}

void Client::handleWrite_( const boost::system::error_code& error)
{
	if (!error)
	{
		writeMsgs_.pop_front();
		if ( !writeMsgs_.empty())
		{
			boost::asio::async_write( socket_,
									  boost::asio::buffer(writeMsgs_.front().getData(),
									  writeMsgs_.front().getLength()),
									  boost::bind( &Client::handleWrite_, this, boost::asio::placeholders::error));
		}
	}
	else
	{
		doClose_();
	}
}

void Client::doClose_()
{
	socket_.close();
}
