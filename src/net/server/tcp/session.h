#ifndef SESSION_H
#define SESSION_H

#include <boost/asio.hpp>
#include "file/filemanager.h"
#include "message/message.h"

class Session: public std::enable_shared_from_this<Session>
{
public:
	Session( boost::asio::ip::tcp::socket socket);
	void start();

private:
	void readHeader_();
	void readBody_();

private:
	boost::asio::ip::tcp::socket socket_;
	char inboundHeader_[Message::headerLength];
	std::vector<char> inboundData_;
	FileManager fileManager_;
};

#endif // SESSION_H
