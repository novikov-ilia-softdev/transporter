#include "session.h"
#include <boost/bind.hpp>

Session::Session( boost::asio::ip::tcp::socket socket):
	socket_( std::move( socket))
{
}

void Session::start()
{
	read_();
}

void Session::read_()
{
	auto self( shared_from_this());
	socket_.async_read_some( boost::asio::buffer( data_, maxLength),
							 [this, self]( boost::system::error_code ec, std::size_t length)
							 {
								if( !ec)
								{
									write_( length);
								}

							 });
}

void Session::write_( std::size_t length)
{
	auto self( shared_from_this());
	boost::asio::async_write( socket_,
							  boost::asio::buffer( data_, length),
							  [this, self]( boost::system::error_code ec, std::size_t length)
							  {
								 if( !ec)
								 {
									 read_();
								 }
							  });
}
