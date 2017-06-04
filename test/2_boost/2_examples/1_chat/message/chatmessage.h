#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

class chatMessage
{
public:
  enum { headerLength = 4 };
  enum { maxBodyLength = 512 };

  chatMessage();

  const char* getData() const;
  char* getData();
  size_t getLength() const;
  const char* getBody() const;
  char* getBody();
  size_t getBodyLength() const;
  void setBodyLength( size_t new_length);
  bool decodeHeader();
  void encodeHeader();

private:
  char data_[ headerLength + maxBodyLength];
  size_t bodyLength_;
};

#endif // CHATMESSAGE_H
