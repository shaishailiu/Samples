#ifndef __gles_types__
#define __gles_types__

//////////////////////////////////////////////////////////////////////////
//lukey  2013 09 05
//////////////////////////////////////////////////////////////////////////

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <math.h>
//gl Vertex GLPoint

static float transform(GLfloat fValue)
{
	fValue = 2 * fValue / 600.0f - 1;
	return fValue;
}

typedef struct GLPoint{ 
	GLfloat x;
	GLfloat y;
	GLfloat z;

	GLPoint()
	{

	}

	GLPoint(GLfloat fx,GLfloat fy)
		:x(transform(fx)),y(transform(fy)),z(1.0f)
	{

	}
} Vertex3D;

typedef struct GLColor{ 
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
} GLcolor;

static inline Vertex3D Vertex3DMake(GLfloat x, GLfloat y, GLfloat z)
{
	Vertex3D ret;
	ret.x = z;
	ret.y = y;
	ret.z = z;
	return ret;
}

static inline GLfloat Vertex3DCalculateDistanceBetweenVertices (Vertex3D first, Vertex3D second)
{
	GLfloat deltaX = second.x - first.x;
	GLfloat deltaY = second.y - first.y;
	GLfloat deltaZ = second.z - first.z;
	return sqrtf(deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ );
};

typedef struct GLTriangle{
	Vertex3D v1;
	Vertex3D v2;
	Vertex3D v3;
} Triangle3D;

static inline Triangle3D Triangle3DMake(Vertex3D v1, Vertex3D v2, Vertex3D v3)
{
	Triangle3D ret;
	ret.v1 = v1;
	ret.v2 = v2;
	ret.v3 = v3;
	return ret;
}



static inline void DrawLine(GLPoint p1,GLPoint p2,GLfloat w,GLColor color)
{
	GLPoint p[2];
	p[0] = p1;
	p[1] = p2;
	//glLineWidth(w);

	glVertexAttribPointer( 0, 3, GL_FLOAT, 0, 0, p);
	glEnableVertexAttribArray( 0 );
	//glVertexAttribPointer( 1, 4, GL_FLOAT, 0, 0, &color);
	//glEnableVertexAttribArray( 1 );
	
	glDrawArrays(GL_LINES,0,2);
}

static inline void DrawLine(GLPoint p1,GLPoint p2)
{
	GLPoint p[2];
	p[0] = p1;
	p[1] = p2;
	//glLineWidth(w);

	glVertexAttribPointer( 0, 3, GL_FLOAT, 0, 0, p);
	glEnableVertexAttribArray( 0 );
	//glVertexAttribPointer( 1, 4, GL_FLOAT, 0, 0, &color);
	//glEnableVertexAttribArray( 1 );

	glDrawArrays(GL_LINES,0,2);
}


#endif //__gles_types__


