#ifndef IPARTICIPANT_H
#define IPARTICIPANT_H

#include "../message/message.h"
#include <memory>

class IParticipant
{
public:
	virtual ~IParticipant() {}
	virtual void deliver(const Message& msg) = 0;
};

typedef std::shared_ptr<IParticipant> IParticipantPtr;

#endif // IPARTICIPANT_H
