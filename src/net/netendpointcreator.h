#ifndef NETENDPOINTCREATOR_H
#define NETENDPOINTCREATOR_H

#include "iserver.h"
#include "args/serverargs.h"
#include "iclient.h"
#include "args/clientargs.h"

class NetEndpointCreator{
public:
	NetEndpointCreator();
	IServerPtr createServer( ServerArgsPtr serverArgsPtr);
	IClientPtr createClient( ClientArgsPtr clientArgsPtr);
};

#endif // NETENDPOINTCREATOR_H
