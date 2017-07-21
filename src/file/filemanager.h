#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "file.h"
#include <vector>
#include <boost/asio.hpp>
#include <boost/archive/text_oarchive.hpp>

typedef std::vector<boost::asio::const_buffer> Buffers;

class FileManager{
public:
	FilePtr getFile( char* filePath);
	void createFile( const File& file);
	Buffers serialize( FilePtr file);
	std::string outboundData_;
};

#endif // FILEMANAGER_H
