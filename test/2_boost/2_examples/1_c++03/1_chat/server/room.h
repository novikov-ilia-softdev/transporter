#ifndef ROOM_H
#define ROOM_H

#include <set>
#include <boost/bind.hpp>
#include "../message/message.h"
#include "iparticipant.h"

class Room
{
public:
	void join( IParticipantPtr participant);
	void leave( IParticipantPtr participant);
	void deliver( const Message& msg, IParticipantPtr notThisParticipant);

private:
	std::set<IParticipantPtr> participants_;
	enum { maxRecentMsgs_ = 100 };
	MessageQueue recentMsgs_;
};

#endif // ROOM_H
