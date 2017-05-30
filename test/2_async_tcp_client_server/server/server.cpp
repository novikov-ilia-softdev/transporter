#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

// g++ -o server.out server.cpp -lboost_system -lboost_thread

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;
typedef boost::shared_ptr<boost::asio::io_service> service_ptr;
typedef boost::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor_ptr;

void start_accept( socket_ptr socket, acceptor_ptr acceptor, service_ptr service);
void handle_accept( socket_ptr socket, acceptor_ptr acceptor, service_ptr service, const boost::system::error_code& err);
void handle_read( const boost::system::error_code& error, std::size_t bytes_transferred, socket_ptr socket);

char data[ 512];

int main()
{
	const int localPort = 2001;

	service_ptr service( new boost::asio::io_service());
	boost::asio::ip::tcp::endpoint endpoint( boost::asio::ip::tcp::v4(), localPort);
	acceptor_ptr acceptor( new boost::asio::ip::tcp::acceptor( *service, endpoint));
	socket_ptr socket( new boost::asio::ip::tcp::socket( *service));

	start_accept( socket, acceptor, service);
	service->run();
}

void start_accept( socket_ptr socket, acceptor_ptr acceptor, service_ptr service)
{
	acceptor->async_accept( *socket, boost::bind( handle_accept, socket, acceptor, service, boost::asio::placeholders::error));
}

void handle_accept( socket_ptr socket, acceptor_ptr acceptor, service_ptr service, const boost::system::error_code& err)
{
	if( err)
	{
		std::cout << "error acception!" << std::endl;
		return;
	}

	std::cout << "accepted!" << std::endl;
	socket_ptr newSocket( new boost::asio::ip::tcp::socket( *service));
	start_accept( newSocket, acceptor, service);

	socket->async_read_some( boost::asio::buffer( data),
							 boost::bind( handle_read, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, socket));
}

void handle_read( const boost::system::error_code& error, std::size_t bytes_transferred, socket_ptr socket)
{
	if( error)
	{
		std::cout << "error handle_read!" << std::endl;
	}

	std::cout << "handle_read" << std::endl;
	std::cout << "bytes_transferred: " << bytes_transferred << std::endl;
	std::cout << "data: " << data << std::endl;

	socket->close();
}
