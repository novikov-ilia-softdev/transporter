#ifndef FILE_H
#define FILE_H

#include <string>
#include <memory>
#include <ostream>

class File{
public:
	File();
	File( char* path);
	const std::string& getName() const;
	const std::string& getContent() const;

	template <typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & name_;
		ar & content_;
	}

	friend std::ostream& operator<<( std::ostream& stream, const File& file);

private:
	std::string name_;
	std::string content_;
};

typedef std::shared_ptr<File> FilePtr;

#endif // FILE_H
