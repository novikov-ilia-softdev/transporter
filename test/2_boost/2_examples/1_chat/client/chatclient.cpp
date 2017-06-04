#include <iostream>
#include "chatclient.h"

ChatClient::ChatClient( boost::asio::io_service& ioService,
						boost::asio::ip::tcp::resolver::iterator endpointIterator)
				: ioService_( ioService),
				  socket_( ioService)
{
	boost::asio::async_connect( socket_,
								endpointIterator,
								boost::bind( &ChatClient::handleConnect_, this, boost::asio::placeholders::error));
}

void ChatClient::write( const chatMessage& msg)
{
	ioService_.post( boost::bind( &ChatClient::doWrite_, this, msg));
}

void ChatClient::close()
{
	ioService_.post( boost::bind( &ChatClient::doClose_, this));
}

void ChatClient::handleConnect_( const boost::system::error_code& error)
{
	if (!error)
	{
		boost::asio::async_read( socket_,
								 boost::asio::buffer( readMsg_.getData(), chatMessage::headerLength),
								 boost::bind( &ChatClient::handleReadHeader_, this, boost::asio::placeholders::error));
	}
}

void ChatClient::handleReadHeader_( const boost::system::error_code& error)
{
	if ( !error && readMsg_.decodeHeader())
	{
		boost::asio::async_read( socket_,
								 boost::asio::buffer( readMsg_.getBody(), readMsg_.getBodyLength()),
								 boost::bind( &ChatClient::handleReadBody_, this, boost::asio::placeholders::error));
	}
	else
	{
		doClose_();
	}
}

void ChatClient::handleReadBody_( const boost::system::error_code& error)
{
	if ( !error)
	{
		std::cout.write( readMsg_.getBody(), readMsg_.getBodyLength());
		std::cout << "\n";
		boost::asio::async_read( socket_,
								 boost::asio::buffer(readMsg_.getData(), chatMessage::headerLength),
								 boost::bind( &ChatClient::handleReadHeader_, this, boost::asio::placeholders::error));
	}
	else
	{
		doClose_();
	}
}

void ChatClient::doWrite_( chatMessage msg)
{
	bool writeInProgress = !writeMsgs_.empty();
	writeMsgs_.push_back(msg);
	if ( !writeInProgress)
	{
		boost::asio::async_write( socket_,
								  boost::asio::buffer( writeMsgs_.front().getData(),
								  writeMsgs_.front().getLength()),
								  boost::bind( &ChatClient::handleWrite_, this, boost::asio::placeholders::error));
	}
}

void ChatClient::handleWrite_( const boost::system::error_code& error)
{
	if (!error)
	{
		writeMsgs_.pop_front();
		if ( !writeMsgs_.empty())
		{
			boost::asio::async_write( socket_,
									  boost::asio::buffer(writeMsgs_.front().getData(),
									  writeMsgs_.front().getLength()),
									  boost::bind( &ChatClient::handleWrite_, this, boost::asio::placeholders::error));
		}
	}
	else
	{
		doClose_();
	}
}

void ChatClient::doClose_()
{
	socket_.close();
}
