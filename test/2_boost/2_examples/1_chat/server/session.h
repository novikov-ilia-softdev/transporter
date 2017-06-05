#ifndef SESSION_H
#define SESSION_H

#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "iparticipant.h"
#include "room.h"

class Session : public IParticipant, public boost::enable_shared_from_this<Session>
{
public:
	Session( boost::asio::io_service& ioService, Room& room);
	boost::asio::ip::tcp::socket& socket();
	void start();
	void deliver( const Message& msg);
	void handleReadHeader( const boost::system::error_code& error);
	void handleReadBody( const boost::system::error_code& error);
	void handleWrite(const boost::system::error_code& error);

private:
	boost::asio::ip::tcp::socket socket_;
	Room& room_;
	Message readMsg_;
	MessageQueue writeMsgs_;
};

typedef boost::shared_ptr<Session> SessionPtr;

#endif // SESSION_H
