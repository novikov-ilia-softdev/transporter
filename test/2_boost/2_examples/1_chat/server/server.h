#ifndef SERVER_H
#define SERVER_H

#include <list>
#include "session.h"

class Server
{
public:
	Server( boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint);
	void startAccept();
	void handleAccept( SessionPtr session, const boost::system::error_code& error);

private:
	boost::asio::io_service& ioService_;
	boost::asio::ip::tcp::acceptor acceptor_;
	Room room_;
};

typedef boost::shared_ptr<Server> ServerPtr;
typedef std::list<ServerPtr> ServerList;

#endif // SERVER_H
