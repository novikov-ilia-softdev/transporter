#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include <list>
#include "room.h"

class Server
{
public:
	Server( boost::asio::io_service& ioService, const boost::asio::ip::tcp::endpoint& endpoint);

private:
	void accept_();

private:
	boost::asio::ip::tcp::acceptor acceptor_;
	boost::asio::ip::tcp::socket socket_;
	Room room_;
};

typedef boost::shared_ptr<Server> ServerPtr;
typedef std::list<ServerPtr> ServerList;

#endif // SERVER_H
