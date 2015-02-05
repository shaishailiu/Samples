#ifndef _BASELAYER_H_
#define _BASELAYER_H_

class BaseLayer
{
public:
	virtual void update()=0;

	BaseLayer();

	~BaseLayer();
};

#endif