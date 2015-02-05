#include <string.h>
#include "Memory.h"



Memory::Memory(void)
{
	position = 0;
	size = 0;
}


Memory::~Memory(void)
{
	if (buffer != nullptr)
	{
		delete buffer;
	}
	
}

unsigned int Memory::read( void *dst, unsigned int _size )
{
	if( ( position + _size ) > size ){ 
		_size = size - position;
	}

	memcpy( dst, &buffer[position], _size );

	position += _size;

	return _size;
}

std::string Memory::readString()
{
	short strLength;
	read(&strLength, sizeof(short));

	char *s = new char[strLength + 1];
	read(s, strLength);
	s[strLength] = 0;

	string str(s);
	delete s;
	return str;
}

float Memory::readFloat()
{
	float num;
	
	read(&num, sizeof(float));

	return num;
}

int Memory::readInt()
{
	int num;
	read(&num, sizeof(int));
	return num;
}
