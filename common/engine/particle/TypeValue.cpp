#include "TypeValue.h"


TypeValue::TypeValue(void)
{
}


TypeValue::~TypeValue(void)
{
}

void TypeValue::setDataByJson( const Json::Value jsonTv )
{
	type = jsonTv["type"].asInt();
	//value = atoi(jsonTv["value"].asString().c_str());
	value = jsonTv["value"].asString();
}
