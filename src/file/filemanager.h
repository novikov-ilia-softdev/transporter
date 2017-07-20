#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "file.h"
#include <vector>
#include <boost/asio.hpp>

class FileManager{
public:
	FilePtr getFile( char* filePath);
	void createFile( const File& file);
	void serialize( std::string& outboundData, std::string& outboundHeader, FilePtr file);
};

#endif // FILEMANAGER_H
