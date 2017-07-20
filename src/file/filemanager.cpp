#include "filemanager.h"
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "message/message.h"

FilePtr FileManager::getFile( char* filePath)
{
	if( !boost::filesystem::exists( filePath))
	{
		return 0;
	}

	return FilePtr( new File( filePath));
}

void FileManager::createFile( const File& file)
{
	std::ofstream outFile (file.getName().c_str());
	outFile << file.getContent();
	outFile.close();
}

void FileManager::serialize( std::string& outboundData, std::string& outboundHeader, FilePtr file)
{
	std::ostringstream archiveStream;
	boost::archive::text_oarchive archive( archiveStream);
	archive << *file;
	outboundData = archiveStream.str();

	std::ostringstream headerStream;

	headerStream << std::setw( Message::headerLength) << std::hex << outboundData.size();

	if( !headerStream || headerStream.str().size() != Message::headerLength)
	{
		std::cout << "error" << std::endl;
	}
	outboundHeader = headerStream.str();
}
