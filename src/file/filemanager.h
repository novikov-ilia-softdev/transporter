#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "file.h"

class FileManager{
public:
	File getFile( char* filePath);
	void createFile( const File& file);
};

#endif // FILEMANAGER_H
