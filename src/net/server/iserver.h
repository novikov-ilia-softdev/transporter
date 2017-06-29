#ifndef ISERVER_H
#define ISERVER_H

#include <memory>
#include "args/serverargs.h"

class IServer{
public:
	IServer( ServerArgsPtr serverArgsPtr);
	virtual void run() = 0;
	virtual ~IServer() = 0;
};

typedef std::shared_ptr<IServer> IServerPtr;

#endif // ISERVER_H
