#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <string>
#define MAX_PATH 200

using namespace std;
class Memory
{
public:
	Memory(void);
	~Memory(void);

	char			filename[ MAX_PATH ];

	//! The file size in bytes.
	unsigned int	size;

	//! The position of the cursor within the memory buffer.
	unsigned int	position;

	//! The memory buffer.
	unsigned char	*buffer;

	//static Memory *mopen( char *filename, unsigned char relative_path );

	unsigned int read(void *dst, unsigned int _size );

	string readString();

	float readFloat();

	int readInt();

	//void minsert(char *str, unsigned int position );

};
#endif
