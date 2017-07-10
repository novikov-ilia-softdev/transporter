#include "filemanager.h"
#include <fstream>

File FileManager::getFile( char* filePath)
{
	return File( filePath);
}

void FileManager::createFile( const File& file)
{
	std::ofstream outFile (file.getName().c_str());
	outFile << file.getContent();
	outFile.close();
}
