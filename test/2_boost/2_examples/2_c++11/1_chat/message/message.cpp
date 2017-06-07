#include "message.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

Message::Message(): bodyLength_( 0)
{
}

const char* Message::getData() const
{
	return data_;
}

char* Message::getData()
{
	return data_;
}

size_t Message::getLength() const
{
	return headerLength + bodyLength_;
}

const char* Message::getBody() const
{
	return data_ + headerLength;
}

char* Message::getBody()
{
	return data_ + headerLength;
}

size_t Message::getBodyLength() const
{
	return bodyLength_;
}

void Message::setBodyLength(size_t newLength)
{
	bodyLength_ = newLength;
	if (bodyLength_ > maxBodyLength)
		bodyLength_ = maxBodyLength;
}

bool Message::decodeHeader()
{
	char header[ headerLength + 1] = "";
	std::strncat( header, data_, headerLength);
	bodyLength_ = std::atoi( header);
	if( bodyLength_ > maxBodyLength)
	{
		bodyLength_ = 0;
		return false;
	}
	return true;
}

void Message::encodeHeader()
{
	char header[ headerLength + 1] = "";
	std::sprintf( header, "%4d", static_cast<int>( bodyLength_));
	std::memcpy( data_, header, headerLength);
}
