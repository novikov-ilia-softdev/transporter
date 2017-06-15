#ifndef IPARTICIPANT_H
#define IPARTICIPANT_H

#include <boost/shared_ptr.hpp>
#include "../message/message.h"

class IParticipant
{
public:
	virtual ~IParticipant() {}
	virtual void deliver(const Message& msg) = 0;
};

typedef boost::shared_ptr<IParticipant> IParticipantPtr;

#endif // IPARTICIPANT_H
