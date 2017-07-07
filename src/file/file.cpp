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
