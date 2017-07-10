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
	enum { maxLength = 1024 };
	char data_[ maxLength];
	char inbound_header_[8];
	std::vector<char> inbound_data_;

};

#endif // SESSION_H
