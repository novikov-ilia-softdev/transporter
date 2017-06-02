#include <iostream>
#include "chatclient.h"

ChatClient::ChatClient( boost::asio::io_service& io_service,
						boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
				: io_service_(io_service),
				  socket_(io_service)
{
	boost::asio::async_connect( socket_,
								endpoint_iterator,
								boost::bind( &ChatClient::handle_connect, this, boost::asio::placeholders::error));
}

void ChatClient::write( const chat_message& msg)
{
	io_service_.post(boost::bind( &ChatClient::do_write, this, msg));
}

void ChatClient::close()
{
	io_service_.post( boost::bind( &ChatClient::do_close, this));
}

void ChatClient::handle_connect( const boost::system::error_code& error)
{
	if (!error)
	{
		boost::asio::async_read(socket_,
		boost::asio::buffer( read_msg_.data(),
							 chat_message::header_length),
							 boost::bind( &ChatClient::handle_read_header, this, boost::asio::placeholders::error));
	}
}

void ChatClient::handle_read_header( const boost::system::error_code& error)
{
	if ( !error && read_msg_.decode_header())
	{
		boost::asio::async_read( socket_,
								 boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
								 boost::bind( &ChatClient::handle_read_body, this, boost::asio::placeholders::error));
	}
	else
	{
		do_close();
	}
}

void ChatClient::handle_read_body( const boost::system::error_code& error)
{
	if ( !error)
	{
		std::cout.write(read_msg_.body(), read_msg_.body_length());
		std::cout << "\n";
		boost::asio::async_read( socket_,
								 boost::asio::buffer(read_msg_.data(), chat_message::header_length),
								 boost::bind( &ChatClient::handle_read_header, this, boost::asio::placeholders::error));
	}
	else
	{
		do_close();
	}
}

void ChatClient::do_write( chat_message msg)
{
	bool write_in_progress = !write_msgs_.empty();
	write_msgs_.push_back(msg);
	if ( !write_in_progress)
	{
		boost::asio::async_write( socket_,
								  boost::asio::buffer(write_msgs_.front().data(),
								  write_msgs_.front().length()),
								  boost::bind( &ChatClient::handle_write, this, boost::asio::placeholders::error));
	}
}

void ChatClient::handle_write(const boost::system::error_code& error)
{
	if (!error)
	{
		write_msgs_.pop_front();
		if ( !write_msgs_.empty())
		{
			boost::asio::async_write( socket_,
									  boost::asio::buffer(write_msgs_.front().data(),
									  write_msgs_.front().length()),
									  boost::bind( &ChatClient::handle_write, this, boost::asio::placeholders::error));
		}
	}
	else
	{
		do_close();
	}
}

void ChatClient::do_close()
{
	socket_.close();
}
