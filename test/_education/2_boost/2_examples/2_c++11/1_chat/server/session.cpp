#include "session.h"

Session::Session( boost::asio::ip::tcp::socket socket, Room& room)
	: socket_( std::move( socket)), room_(room)
{
}

boost::asio::ip::tcp::socket& Session::socket()
{
	return socket_;
}

void Session::start()
{
	room_.join( shared_from_this());
	readHeader_();
}

void Session::deliver( const Message& msg)
{
	bool writeInProgress = !writeMsgs_.empty();
	writeMsgs_.push_back(msg);
	if ( !writeInProgress)
	{
		write_();
	}
}

void Session::readHeader_()
{
	auto self( shared_from_this());
	boost::asio::async_read( socket_,
							 boost::asio::buffer(readMsg_.getData(),
							 Message::headerLength),
							 [this, self](boost::system::error_code ec, std::size_t length)
							 {
								 if ( !ec && readMsg_.decodeHeader())
								 {
									 readBody_();
								 }
								 else
								 {
									 room_.leave( shared_from_this());
								 }
							 });
}

void Session::readBody_()
{
	auto self( shared_from_this());
	boost::asio::async_read( socket_,
							 boost::asio::buffer(readMsg_.getBody(),
							 readMsg_.getBodyLength()),
							 [this, self](boost::system::error_code ec, std::size_t length)
							 {
								 if (!ec)
								 {
									 room_.deliver( readMsg_, shared_from_this());
									 readHeader_();
								 }
								 else
								 {
									 room_.leave(shared_from_this());
								 }
							 });
}

void Session::write_()
{
	auto self( shared_from_this());
	boost::asio::async_write( socket_,
							  boost::asio::buffer( writeMsgs_.front().getData(),
							  writeMsgs_.front().getLength()),
							  [this, self]( boost::system::error_code ec, std::size_t length)
								{
									if (!ec)
									{
										writeMsgs_.pop_front();
										if (!writeMsgs_.empty())
										{
											write_();
										}
									}
									else
									{
										room_.leave( shared_from_this());
									}
								});
}
