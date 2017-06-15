#ifndef UTILS
#define UTILS

#include <ctime>
#include <string>

std::string make_daytime_string()
{
	std::time_t now = std::time(0);
	return std::ctime(&now);
}

#endif // UTILS
