#include "room.h"

void Room::join( IParticipantPtr participant)
{
	participants_.insert( participant);
	for( auto msg: recentMsgs_)
		participant->deliver( msg);
}

void Room::leave( IParticipantPtr participant)
{
	participants_.erase( participant);
}

void Room::deliver( const Message& msg, IParticipantPtr notThisParticipant)
{
	recentMsgs_.push_back(msg);
	while( recentMsgs_.size() > maxRecentMsgs_)
		recentMsgs_.pop_front();

	for( auto participant: participants_)
	{
		if( participant != notThisParticipant)
			participant->deliver( msg);
	}
}
