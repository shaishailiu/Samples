#include "StringUtils.h"
#include <sstream>

using namespace std;
StringUtils::StringUtils(void)
{
}


StringUtils::~StringUtils(void)
{
}

std::string StringUtils::int2str(const int i )
{
	string s;
	stringstream ss(s);
	ss<< i;
	return ss.str();
}
