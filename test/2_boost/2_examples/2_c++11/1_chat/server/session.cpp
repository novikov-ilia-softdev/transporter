#include "session.h"

Session::Session( boost::asio::io_service& ioService, Room& room)
	: socket_(ioService), room_(room)
{
}

boost::asio::ip::tcp::socket& Session::socket()
{
	return socket_;
}

void Session::start()
{
	room_.join(shared_from_this());
	boost::asio::async_read( socket_,
							 boost::asio::buffer( readMsg_.getData(), Message::headerLength),
							 boost::bind( &Session::handleReadHeader_,
										  shared_from_this(),
										  boost::asio::placeholders::error));
}

void Session::deliver( const Message& msg)
{
	bool writeInProgress = !writeMsgs_.empty();
	writeMsgs_.push_back(msg);
	if ( !writeInProgress)
	{
		boost::asio::async_write( socket_,
								  boost::asio::buffer(writeMsgs_.front().getData(),
								  writeMsgs_.front().getLength()),
								  boost::bind( &Session::handleWrite_,
											   shared_from_this(),
											   boost::asio::placeholders::error));
	}
}

void Session::handleReadHeader_( const boost::system::error_code& error)
{
	if (!error && readMsg_.decodeHeader())
	{
		boost::asio::async_read( socket_,
								 boost::asio::buffer(readMsg_.getBody(),
								 readMsg_.getBodyLength()),
								 boost::bind( &Session::handleReadBody_,
											  shared_from_this(),
											  boost::asio::placeholders::error));
	}
	else
	{
		room_.leave( shared_from_this());
	}
}

void Session::handleReadBody_( const boost::system::error_code& error)
{
	if (!error)
	{
		room_.deliver( readMsg_, shared_from_this());
		boost::asio::async_read( socket_,
								 boost::asio::buffer(readMsg_.getData(),
								 Message::headerLength),
								 boost::bind( &Session::handleReadHeader_,
											  shared_from_this(),
											  boost::asio::placeholders::error));
	}
	else
	{
		room_.leave( shared_from_this());
	}
}

void Session::handleWrite_( const boost::system::error_code& error)
{
	if (!error)
	{
		writeMsgs_.pop_front();
		if ( !writeMsgs_.empty())
		{
			boost::asio::async_write( socket_,
									  boost::asio::buffer( writeMsgs_.front().getData(),
									  writeMsgs_.front().getLength()),
									  boost::bind( &Session::handleWrite_, shared_from_this(),
												   boost::asio::placeholders::error));
		}
	}
	else
	{
		room_.leave( shared_from_this());
	}
}
