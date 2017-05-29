#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

// g++ -o server server.cpp -lboost_system -lboost_thread

typedef boost::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr;
void client_session( socket_ptr sock);

int main()
{
	const int localPort = 2001;

	boost::asio::io_service service;
	boost::asio::ip::tcp::endpoint endpoint( boost::asio::ip::tcp::v4(), localPort);
	boost::asio::ip::tcp::acceptor acceptor( service, endpoint);

	while( true)
	{
	    socket_ptr socket( new boost::asio::ip::tcp::socket( service));
	    std::cout << "accepting..." << std::endl;

	    try
		{
	    	acceptor.accept( *socket);
	    	boost::thread( boost::bind( client_session, socket));
		}
		catch( boost::system::system_error& err)
		{
			std::cout << "exception:" << std::endl;
			std::cout << err.what() << std::endl;
		}
	}
}

void client_session( socket_ptr socket)
{
	std::cout << "new client!"<< std::endl;
	char data[512];

	try
	{
		size_t length = socket->read_some( boost::asio::buffer( data));
		std::cout << "got " << length << " bytes from client: " << data  << std::endl;
		socket->close();
	}
	catch( boost::system::system_error& err)
	{
		std::cout << "exception:" << std::endl;
		std::cout << err.what() << std::endl;
	}
}
