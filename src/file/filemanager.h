#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "file.h"
#include <vector>
#include <boost/asio.hpp>

typedef std::vector<boost::asio::const_buffer> Buffers;

class FileManager{
public:
	FilePtr getFile( char* filePath);
	void createFile( const File& file);
	Buffers serialize( FilePtr file);
};

#endif // FILEMANAGER_H
