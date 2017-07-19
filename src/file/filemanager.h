#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "file.h"

class FileManager{
public:
	FilePtr getFile( char* filePath);
	void createFile( const File& file);
};

#endif // FILEMANAGER_H
