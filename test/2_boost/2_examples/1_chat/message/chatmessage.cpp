#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "chatmessage.h"

chatMessage::chatMessage(): bodyLength_( 0)
{
}

const char* chatMessage::getData() const
{
	return data_;
}

char* chatMessage::getData()
{
	return data_;
}

size_t chatMessage::getLength() const
{
	return headerLength + bodyLength_;
}

const char* chatMessage::getBody() const
{
	return data_ + headerLength;
}

char* chatMessage::getBody()
{
	return data_ + headerLength;
}

size_t chatMessage::getBodyLength() const
{
	return bodyLength_;
}

void chatMessage::setBodyLength(size_t newLength)
{
	bodyLength_ = newLength;
	if (bodyLength_ > maxBodyLength)
		bodyLength_ = maxBodyLength;
}

bool chatMessage::decodeHeader()
{
	char header[ headerLength + 1] = "";
	strncat( header, data_, headerLength);
	bodyLength_ = atoi( header);
	if( bodyLength_ > maxBodyLength)
	{
		bodyLength_ = 0;
		return false;
	}
	return true;
}

void chatMessage::encodeHeader()
{
	char header[ headerLength + 1] = "";
	sprintf( header, "%4d", static_cast<int>( bodyLength_));
	memcpy( data_, header, headerLength);
}
