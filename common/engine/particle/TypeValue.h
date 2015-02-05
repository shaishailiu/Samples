#ifndef _TYPEVALUE_H_
#define _TYPEVALUE_H_

#include <string>
#include "json/json.h"

class TypeValue
{
public:
	TypeValue(void);
	~TypeValue(void);

	int type;
	//int value;
	std::string value;

	void setDataByJson(const Json::Value jsonTv);

};

#endif