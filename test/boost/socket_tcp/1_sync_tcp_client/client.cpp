// g++ -o client.out client.cpp -lboost_system -lpthread

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: client <host>" << std::endl;
			return 1;
		}

		boost::asio::io_service io_service;

		boost::asio::ip::tcp::resolver resolver( io_service);
		boost::asio::ip::tcp::resolver::query query( argv[1], "daytime");
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve( query);

		boost::asio::ip::tcp::socket socket( io_service);
		boost::asio::connect( socket, endpoint_iterator);

		for (;;)
		{
			boost::array<char, 128> buf;
			boost::system::error_code error;

			size_t len = socket.read_some( boost::asio::buffer( buf), error);

			if (error == boost::asio::error::eof)
				break;
			else if (error)
				throw boost::system::system_error(error);

			std::cout.write( buf.data(), len);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
