#include "file.h"
#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>

File::File()
{

}

File::File( char* path)
{
	boost::filesystem::path p( path);
	name_ = p.filename().string();

	std::ifstream ifs( path);
	std::string content( (std::istreambuf_iterator<char>(ifs) ),
					   (std::istreambuf_iterator<char>()    ) );

	content_ = content;
}

const std::string& File::getName() const
{
	return name_;
}

const std::string& File::getContent() const
{
	return content_;
}

std::ostream& operator<<( std::ostream& stream, const File& file)
{
	return stream << "name_: " << file.name_ << std::endl
				  << "content_: " << std::endl << file.content_;
}
