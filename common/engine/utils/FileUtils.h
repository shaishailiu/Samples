#ifndef _FILEUTILS_H_
#define _FILEUTILS_H_

#include <string>
#include "utils/Memory.h"

using namespace std;

class FileUtils
{
public:
	FileUtils(void);
	~FileUtils(void);

	string static readTxt(string fileUrl);

	static Memory * loadFile(const char *filename);
};

#endif

