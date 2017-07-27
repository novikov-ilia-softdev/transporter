#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <boost/asio.hpp>
#include "net/client/iclient.h"
#include "file/filemanager.h"

class UDPClient: public IClient{
public:
	UDPClient( ClientArgsPtr clientArgsPtr);
	void run();

private:
	ClientArgsPtr clientArgsPtr_;
	boost::asio::io_service ioService_;
	boost::asio::ip::tcp::socket socket_;
	boost::asio::ip::tcp::resolver resolver_;
	FileManager fileManager_;
};

typedef std::shared_ptr<UDPClient> UDPClientPtr;

#endif // UDPCLIENT_H
