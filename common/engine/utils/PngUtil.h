#ifndef _PNG1_H_
#define _PNG1_H_

#include <GLES2/gl2.h>
#include "png/png.h"

class Memory;

class PngUtil
{
public:
	PngUtil(void);
	~PngUtil(void);
	GLsizei width;
	GLsizei height;
	GLenum format;
	GLint internalFormat;
	GLuint id;
	GLubyte *texels;


	//! The OpenGLES texture id.
	unsigned int	tid;

	//! The texture bits.
	unsigned char	byte;

	//! The total size of the texture in bytes.
	unsigned int	size;

	//! The target of the texture. (Default GL_TEXTURE_2D)
	unsigned int	target;

	//! The type of texel to use for this texture. (Default GL_UNSIGNED_BYTE)
	unsigned int	texel_type;

	//! The raw texel array.
	//unsigned char	*texel_array;

	//! The number of mipmaps (PVRTC only).
	unsigned int	n_mipmap;

	//! The compression type.
	unsigned int	compression;

	static PngUtil * readPNGFromFile (const char *filename);
	//static PngUtil * readPNGBuffer(const char *filename);
	static void png_memory_read( png_structp structp, png_bytep bytep, png_size_t size );
};
#endif
