#ifndef SESSION_H
#define SESSION_H

#include <boost/asio.hpp>

class Session: public std::enable_shared_from_this<Session>
{
public:
	Session( boost::asio::ip::tcp::socket socket);
	void start();

private:
	void read_();
	void write_( std::size_t length);

private:
	boost::asio::ip::tcp::socket socket_;
	enum { headerLength_ = 8 };
	char inboundHeader_[headerLength_];
	std::vector<char> inboundData_;
};

#endif // SESSION_H
