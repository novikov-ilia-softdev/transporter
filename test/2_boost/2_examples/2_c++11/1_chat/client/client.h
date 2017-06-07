#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <deque>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "../message/message.h"

class Client
{
typedef std::deque<Message> chatMessageQueue;

public:
	Client( boost::asio::io_service& ioService,
			boost::asio::ip::tcp::resolver::iterator endpointIterator);

	void write( const Message& msg);
	void close();

private:
	void connect_( boost::asio::ip::tcp::resolver::iterator endpointIterator);
	void readHeader_();
	void readBody_();
	void write_();

private:
	boost::asio::io_service& ioService_;
	boost::asio::ip::tcp::socket socket_;
	Message readMsg_;
	MessageQueue writeMsgs_;
};

#endif // CHATCLIENT_H
