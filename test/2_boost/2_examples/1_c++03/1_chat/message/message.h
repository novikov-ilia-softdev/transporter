#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include <deque>

class Message
{
public:
  enum { headerLength = 4 };
  enum { maxBodyLength = 512 };

  Message();

  const char* getData() const;
  char* getData();
  std::size_t getLength() const;
  const char* getBody() const;
  char* getBody();
  std::size_t getBodyLength() const;
  void setBodyLength( std::size_t new_length);
  bool decodeHeader();
  void encodeHeader();

private:
  char data_[ headerLength + maxBodyLength];
  std::size_t bodyLength_;
};

typedef std::deque<Message> MessageQueue;

#endif // CHATMESSAGE_H
