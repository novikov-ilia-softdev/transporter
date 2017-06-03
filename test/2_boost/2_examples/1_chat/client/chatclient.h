#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include <deque>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "../message/chatmessage.hpp"

class ChatClient
{
typedef std::deque<chatMessage> chatMessageQueue;

public:
	ChatClient( boost::asio::io_service& ioService,
			    boost::asio::ip::tcp::resolver::iterator endpointIterator);

	void write( const chatMessage& msg);
	void close();

private:
	void handleConnect_( const boost::system::error_code& error);
	void handleReadHeader_( const boost::system::error_code& error);
	void handleReadBody_( const boost::system::error_code& error);
	void doWrite_( chatMessage msg);
	void handleWrite_( const boost::system::error_code& error);
	void doClose_();

private:
	boost::asio::io_service& ioService_;
	boost::asio::ip::tcp::socket socket_;
	chatMessage readMsg_;
	chatMessageQueue writeMsgs_;
};

#endif // CHATCLIENT_H
