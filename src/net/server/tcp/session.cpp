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
	const std::size_t header_length = 8;
	boost::asio::async_read(
			socket_,
			boost::asio::buffer(inbound_header_),
			[this, self]( boost::system::error_code ec, std::size_t length)
			{
				if( !ec)
				{
					std::istringstream is(std::string(inbound_header_, header_length));
					std::size_t inbound_data_size = 0;
					if (!(is >> std::hex >> inbound_data_size))
					{
						std::cout << "error" << std::endl;
						return;
					}

					inbound_data_.resize(inbound_data_size);
					boost::asio::async_read(
						socket_,
						boost::asio::buffer( inbound_data_),
						[this, self]( boost::system::error_code ec, std::size_t length)
						{
							if( !ec)
							{
								std::string archive_data(&inbound_data_[0], inbound_data_.size());
								std::istringstream archive_stream(archive_data);
								boost::archive::text_iarchive archive(archive_stream);
								File file;
								archive >> file;
								std::cout << file << std::endl;
							}
						});
				}
			});
}
