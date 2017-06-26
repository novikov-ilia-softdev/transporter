#include "serverargs.h"
#include <iostream>

ServerArgs::ServerArgs( int argc, char* argv[]):
	argc_( argc), argv_( argv)
{
	port_ = argv_[ 2];
	transport_ = argv_[ 3];
}
