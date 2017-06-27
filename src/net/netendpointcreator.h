#ifndef NETENDPOINTCREATOR_H
#define NETENDPOINTCREATOR_H

#include "iserver.h"
#include "args/serverargs.h"

class NetEndpointCreator{
public:
	NetEndpointCreator();
	IServerPtr createServer( ServerArgsPtr serverArgsPtr);
};

#endif // NETENDPOINTCREATOR_H
