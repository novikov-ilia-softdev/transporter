#include "room.h"

void Room::join( IParticipantPtr participant)
{
	participants_.insert( participant);
	std::for_each( recentMsgs_.begin(),
				   recentMsgs_.end(),
				   boost::bind( &IParticipant::deliver,
								participant,
								_1));
}

void Room::leave( IParticipantPtr participant)
{
	participants_.erase( participant);
}

void Room::deliver( const Message& msg)
{
	recentMsgs_.push_back(msg);
	while( recentMsgs_.size() > maxRecentMsgs_)
		recentMsgs_.pop_front();

	std::for_each( participants_.begin(),
				   participants_.end(),
				   boost::bind( &IParticipant::deliver,
								_1,
								boost::ref( msg)));
}
