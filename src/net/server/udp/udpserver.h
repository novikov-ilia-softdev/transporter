#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <memory>
#include <boost/asio.hpp>
#include "net/server/iserver.h"
#include "message/message.h"
#include "file/filemanager.h"

class UDPServer: public IServer{
public:
	UDPServer( ServerArgsPtr serverArgsPtr);
	void run();

private:
	static const unsigned int INBOUND_DATA_BUFFER_SIZE;

private:
	void receive_();


private:
	ServerArgsPtr serverArgsPtr_;
	boost::asio::io_service ioService_;
	boost::asio::ip::udp::socket socket_;
	boost::asio::ip::udp::endpoint senderEndpoint_;
	std::vector<char> inboundData_;
	FileManager fileManager_;
};

typedef std::shared_ptr<UDPServer> UDPServerPtr;

#endif // UDPSERVER_H
