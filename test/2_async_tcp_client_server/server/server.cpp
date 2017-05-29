#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

// g++ -o server.out server.cpp -lboost_system -lboost_thread

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;
void start_accept( socket_ptr socket, boost::asio::ip::tcp::acceptor& acceptor, boost::asio::io_service& service)
void handle_accept( socket_ptr socket, boost::asio::ip::tcp::acceptor& acceptor, boost::asio::io_service& service, const boost::system::error_code& err)

int main()
{
	const int localPort = 2001;

	boost::asio::io_service service;
	boost::asio::ip::tcp::endpoint endpoint( boost::asio::ip::tcp::v4(), localPort);
	boost::asio::ip::tcp::acceptor acceptor( service, endpoint);

	socket_ptr socket( new boost::asio::ip::tcp::socket( service));
	start_accept( socket, acceptor, service);
	service.run();
}

void start_accept( socket_ptr socket, boost::asio::ip::tcp::acceptor& acceptor, boost::asio::io_service& service)
{
	acceptor.async_accept( boost::bind( handle_accept, socket, _1, acceptor, _2, service, _3));
}

void handle_accept( socket_ptr socket, boost::asio::ip::tcp::acceptor& acceptor, boost::asio::io_service& service, const boost::system::error_code& err)
{
	if( !err)
	{
		std::cout << "accepted!" << std::endl;
		socket_ptr socket( new boost::asio::ip::tcp::socket( service));
		start_accept( socket, acceptor);
	}
}
