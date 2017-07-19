#include "filemanager.h"
#include <fstream>
#include <boost/filesystem.hpp>

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
