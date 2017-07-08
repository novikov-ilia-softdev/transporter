#include "file.h"
#include <fstream>
#include <iostream>

File::File()
{

}


File::File( char* path)
{
	std::ifstream ifs( path);
	std::string content( (std::istreambuf_iterator<char>(ifs) ),
					   (std::istreambuf_iterator<char>()    ) );

	content_ = content;
}

std::ostream& operator<<( std::ostream& stream, const File& file)
{
	return stream << "name_: " << file.name_ << std::endl
				  << "size_: " << file.size_ << std::endl
				  << "content_: " << file.content_;
}
