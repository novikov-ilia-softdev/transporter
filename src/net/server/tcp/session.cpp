#include "session.h"
#include "file/file.h"
#include <iostream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

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
	boost::asio::async_read(
			socket_,
			boost::asio::buffer( inboundHeader_),
			[this, self]( boost::system::error_code ec, std::size_t length)
			{
				if( !ec)
				{
					std::istringstream is( std::string( inboundHeader_, headerLength_));
					std::size_t inboundDataSize = 0;
					if ( !( is >> std::hex >> inboundDataSize))
					{
						std::cout << "error" << std::endl;
						return;
					}

					inboundData_.resize( inboundDataSize);
					boost::asio::async_read(
						socket_,
						boost::asio::buffer( inboundData_),
						[this, self]( boost::system::error_code ec, std::size_t length)
						{
							if( !ec)
							{
								std::string archiveData( &inboundData_[0], inboundData_.size());
								std::istringstream archiveStream( archiveData);
								boost::archive::text_iarchive archive( archiveStream);
								File file;
								archive >> file;
								std::cout << file << std::endl;
							}
						});
				}
			});
}
