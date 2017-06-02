#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <deque>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "../message/chatmessage.hpp"


class ChatClient
{
typedef std::deque<chat_message> chat_message_queue;

public:
	ChatClient( boost::asio::io_service& io_service,
			    boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

	void write(const chat_message& msg);
	void close();

private:
	void handle_connect( const boost::system::error_code& error);
	void handle_read_header( const boost::system::error_code& error);
	void handle_read_body( const boost::system::error_code& error);
	void do_write( chat_message msg);
	void handle_write( const boost::system::error_code& error);
	void do_close();

private:
	boost::asio::io_service& io_service_;
	boost::asio::ip::tcp::socket socket_;
	chat_message read_msg_;
	chat_message_queue write_msgs_;
};

#endif // CHATCLIENT_H
