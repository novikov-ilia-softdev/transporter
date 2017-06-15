#ifndef SESSION_H
#define SESSION_H

#include <boost/asio.hpp>
#include "iparticipant.h"
#include "room.h"

class Session : public IParticipant, public std::enable_shared_from_this<Session>
{
public:
	Session( boost::asio::ip::tcp::socket socket, Room& room);
	boost::asio::ip::tcp::socket& socket();
	void start();
	void deliver( const Message& msg);

private:
	void readHeader_();
	void readBody_();
	void write_();

private:
	boost::asio::ip::tcp::socket socket_;
	Room& room_;
	Message readMsg_;
	MessageQueue writeMsgs_;
};

typedef std::shared_ptr<Session> SessionPtr;

#endif // SESSION_H
