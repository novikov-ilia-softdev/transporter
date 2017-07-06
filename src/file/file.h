#ifndef FILE_H
#define FILE_H

#include <string>

class File{
public:
	File( char* path);

private:
	std::string name_;
	std::size_t size_;
	std::string content_;
};

#endif // FILE_H
