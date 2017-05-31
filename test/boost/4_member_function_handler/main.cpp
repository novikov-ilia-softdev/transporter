// g++ main.cpp -lboost_system

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class Printer
{
public:
	Printer(boost::asio::io_service& io):
			timer_( io, boost::posix_time::seconds(1)),
			count_(0)
	{
		timer_.async_wait(boost::bind( &Printer::print, this));
	}

	~Printer()
	{
		std::cout << "Final count is " << count_ << std::endl;
	}

	void print()
	{
		std::cout << "print" << std::endl;
		if (count_ < 5)
		{
			std::cout << count_ << std::endl;
			++count_;

			timer_.expires_at(timer_.expires_at() + boost::posix_time::seconds(1));
			timer_.async_wait(boost::bind( &Printer::print, this));
		}
	}

private:
	boost::asio::deadline_timer timer_;
	int count_;
};

int main()
{
	boost::asio::io_service io;
	Printer p( io);
	io.run();
}
