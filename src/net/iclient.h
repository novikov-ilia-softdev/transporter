#ifndef ICLIENT_H
#define ICLIENT_H

#include <memory>
#include "args/clientargs.h"

class IClient{
public:
	IClient( ClientArgsPtr clientArgsPtr);
	virtual void run() = 0;
	virtual ~IClient() = 0;
};

typedef std::shared_ptr<IClient> IClientPtr;

#endif // ICLIENT_H
