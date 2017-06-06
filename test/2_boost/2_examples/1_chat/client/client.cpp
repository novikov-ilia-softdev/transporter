#include <iostream>
#include "client.h"

Client::Client( boost::asio::io_service& ioService,
						boost::asio::ip::tcp::resolver::iterator endpointIterator)
				: ioService_( ioService),
				  socket_( ioService)
{
	boost::asio::async_connect( socket_,
								endpointIterator,
								boost::bind( &Client::handleConnect_, this, boost::asio::placeholders::error));
}

void Client::write( const Message& msg)
{
	ioService_.post( boost::bind( &Client::doWrite_, this, msg));
}

void Client::close()
{
	ioService_.post( boost::bind( &Client::doClose_, this));
}

void Client::handleConnect_( const boost::system::error_code& error)
{
	if (!error)
	{
		boost::asio::async_read( socket_,
								 boost::asio::buffer( readMsg_.getData(), Message::headerLength),
								 boost::bind( &Client::handleReadHeader_, this, boost::asio::placeholders::error));
	}
}

void Client::handleReadHeader_( const boost::system::error_code& error)
{
	if ( !error && readMsg_.decodeHeader())
	{
		boost::asio::async_read( socket_,
								 boost::asio::buffer( readMsg_.getBody(), readMsg_.getBodyLength()),
								 boost::bind( &Client::handleReadBody_, this, boost::asio::placeholders::error));
	}
	else
	{
		doClose_();
	}
}

void Client::handleReadBody_( const boost::system::error_code& error)
{
	if ( !error)
	{
		std::cout.write( readMsg_.getBody(), readMsg_.getBodyLength());
		std::cout << "\n";
		boost::asio::async_read( socket_,
								 boost::asio::buffer(readMsg_.getData(), Message::headerLength),
								 boost::bind( &Client::handleReadHeader_, this, boost::asio::placeholders::error));
	}
	else
	{
		doClose_();
	}
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
