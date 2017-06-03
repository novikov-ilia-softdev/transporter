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
		boost::asio::async_read(socket_,
		boost::asio::buffer( readMsg_.data(),
							 chatMessage::header_length),
							 boost::bind( &ChatClient::handleReadHeader_, this, boost::asio::placeholders::error));
	}
}

void ChatClient::handleReadHeader_( const boost::system::error_code& error)
{
	if ( !error && readMsg_.decode_header())
	{
		boost::asio::async_read( socket_,
								 boost::asio::buffer(readMsg_.body(), readMsg_.body_length()),
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
		std::cout.write(readMsg_.body(), readMsg_.body_length());
		std::cout << "\n";
		boost::asio::async_read( socket_,
								 boost::asio::buffer(readMsg_.data(), chatMessage::header_length),
								 boost::bind( &ChatClient::handleReadHeader_, this, boost::asio::placeholders::error));
	}
	else
	{
		doClose_();
	}
}

void ChatClient::doWrite_( chatMessage msg)
{
	bool write_in_progress = !writeMsgs_.empty();
	writeMsgs_.push_back(msg);
	if ( !write_in_progress)
	{
		boost::asio::async_write( socket_,
								  boost::asio::buffer(writeMsgs_.front().data(),
								  writeMsgs_.front().length()),
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
									  boost::asio::buffer(writeMsgs_.front().data(),
									  writeMsgs_.front().length()),
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
