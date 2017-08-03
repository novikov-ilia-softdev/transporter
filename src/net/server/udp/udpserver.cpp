#include "udpserver.h"
#include <iostream>
#include "file/file.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

UDPServer::UDPServer( ServerArgsPtr serverArgsPtr):
	IServer( serverArgsPtr),
	serverArgsPtr_( serverArgsPtr),
	socket_( ioService_, boost::asio::ip::udp::endpoint( boost::asio::ip::udp::v4(), std::atoi( serverArgsPtr->getPort())))
{
	receive_();
}

void UDPServer::run()
{
	std::cout << "UDPServer::run()" << std::endl;
	ioService_.run();
}

void UDPServer::receive_()
{
	inboundData_.resize( 1024);

	socket_.async_receive_from( boost::asio::buffer( inboundData_),
								senderEndpoint_,
								[ this](boost::system::error_code error, std::size_t bytesRecvd)
								{
									if (!error && bytesRecvd > 0)
									{
										std::cout << "bytesRecvd: " << bytesRecvd << std::endl;
										//std::cout << "inboundData_: " << inboundData_ << std::endl;
										try
										{
											std::string archiveData( &inboundData_[0 + 8], inboundData_.size());
											std::istringstream archiveStream( archiveData);
											boost::archive::text_iarchive archive( archiveStream);
											File file;
											archive >> file;
											std::cout << "received file " << file.getName() << std::endl;
											fileManager_.createFile( file);
											socket_.close();
										}
										catch( std::exception& e)
										{
											std::cerr << "Exception: " << e.what() << "\n";
										}
									}
								});
}

/*
void UDPServer::receive_()
{
	socket_.async_receive_from( boost::asio::buffer( inboundHeader_, Message::headerLength),
								senderEndpoint_,
								[ this](boost::system::error_code error, std::size_t bytesRecvd)
								{
									if (!error && bytesRecvd > 0)
									{
										std::cout << "bytesRecvd: " << bytesRecvd << std::endl;
										std::cout << "inboundHeader_: " << inboundHeader_ << std::endl;

										std::istringstream is( std::string( inboundHeader_, Message::headerLength));
										std::size_t inboundDataSize = 0;
										if( !( is >> std::hex >> inboundDataSize))
										{
											std::cout << "error" << std::endl;
											return;
										}

										std::cout << "inboundDataSize: " << inboundDataSize << std::endl;
										inboundData_.resize( inboundDataSize);

										socket_.async_receive_from( boost::asio::buffer( inboundData_),
																	senderEndpoint_,
																	[ this](boost::system::error_code error, std::size_t bytesRecvd)
																	{
																		if (!error && bytesRecvd > 0)
																		{
																			std::cout << "bytesRecvd: " << bytesRecvd << std::endl;
																			//std::cout << "inboundData_: " << inboundData_ << std::endl;
																			try
																			{
																				std::string archiveData( &inboundData_[0], inboundData_.size());
																				std::istringstream archiveStream( archiveData);
																				boost::archive::text_iarchive archive( archiveStream);
																				File file;
																				archive >> file;
																				std::cout << "received file " << file.getName() << std::endl;
																				fileManager_.createFile( file);
																				socket_.close();
																			}
																			catch( std::exception& e)
																			{
																				std::cerr << "Exception: " << e.what() << "\n";
																			}
																		}
																	});

									}
								});
}
*/
