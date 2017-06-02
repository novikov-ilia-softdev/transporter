// g++ main.cpp -lboost_system -lboost_thread

#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

const int TIMEOUT_MS = 1;
const int MAX_COUNT = 10000;

class Printer
{
public:
  Printer(boost::asio::io_service& io)
    : strand_( io),
      timer1_( io, boost::posix_time::milliseconds( timeoutMs)),
      timer2_( io, boost::posix_time::milliseconds( timeoutMs)),
      count_( 0)
  {
	timer1_.async_wait( strand_.wrap( boost::bind( &Printer::print1, this)));
	timer2_.async_wait( strand_.wrap( boost::bind( &Printer::print2, this)));
  }

  ~Printer()
  {
	  std::cout << "Final count is " << count_ << std::endl;
  }

  void print1()
  {
    if (count_ < maxCount_)
    {
		std::cout << "Timer 1: " << count_ << std::endl;
		++count_;

		timer1_.expires_at(timer1_.expires_at() + boost::posix_time::milliseconds( timeoutMs));
		timer1_.async_wait( strand_.wrap(boost::bind( &Printer::print1, this)));
    }
  }

  void print2()
  {
    if (count_ < maxCount_)
    {
		std::cout << "Timer 2: " << count_ << std::endl;
		++count_;

		timer2_.expires_at( timer2_.expires_at() + boost::posix_time::milliseconds( timeoutMs));
		timer2_.async_wait( strand_.wrap(boost::bind( &Printer::print2, this)));
    }
  }

private:
	boost::asio::io_service::strand strand_;
	boost::asio::deadline_timer timer1_;
	boost::asio::deadline_timer timer2_;
	int count_;
	static const int maxCount_;
	static const int timeoutMs;
};

const int Printer::maxCount_ = 10;
const int Printer::timeoutMs = 1000;

int main()
{
	boost::asio::io_service io;
	Printer p( io);
	boost::thread t( boost::bind( &boost::asio::io_service::run, &io));
	io.run();
	t.join();
}
