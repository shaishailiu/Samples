#ifndef __GRP_MATRIX_H__
#define __GRP_MATRIX_H__

#include <memory>
#include "../math/Vector.h"
#include "../math/Quaternion.h"
//#include "Core.h"
//namespace grp


class Matrix
{
public:
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float M[4][4];
		float _M[16];
	};

public:
	Matrix();
	Matrix(	float, float, float, float,
			float, float, float, float,
			float, float, float, float,
			float, float, float, float);
	explicit Matrix(const float*);
	Matrix(const Matrix&);

	Matrix& operator=(const Matrix&);
	Matrix& operator*=(const Matrix&);

	Matrix operator+(const Matrix&) const;
	Matrix& operator+=(const Matrix&);
	Matrix operator-(const Matrix&) const;

	Vector3& getVector3(size_t row);
	Vector4& getVector4(size_t row);

	const Vector3& getVector3(size_t row) const;
	const Vector4& getVector4(size_t row) const;

	void multiply_optimized(const Matrix& m, Matrix& out) const;
	void multiply(const Matrix& m);
	void prependMultiply(const Matrix& m);

	bool operator==(const Matrix&) const;
	bool operator!=(const Matrix&) const;

	Matrix getLerp(const Matrix&, float) const;
	Matrix& lerp(const Matrix&, float);

	Matrix operator*(const Matrix&) const;

	Matrix operator*(float) const;
	Matrix operator/(float) const;

	//friend Matrix operator*(float, const Matrix&);

	Matrix& setTranslation(const Vector3& v);
	void appendTranslation(const Vector3& v);
	void appendTranslation(const float &x,const float &y,const float &z);
	void prependTranslation(const Vector3& v);
	void prependTranslation(const float &x,const float &y,const float &z);

	Matrix& setRotation(const Quaternion& q);
	void appendRotation(const Quaternion& q);
	void prependRotation(const Quaternion& q);

	void appendRotationAxis(const float &degrees,const Vector3 &axis);
	void prependRotationAxis(const float &degrees,const Vector3 &axis);

	Matrix& setScale(const Vector3& v);
	void appendScale(const Vector3& v);
	void appendScale(const float &x,const float &y,const float &z);
	void prependScale(const Vector3& v);
	void prependScale(const float &x,const float &y,const float &z);

	Matrix& setTranslationRotation(const Vector3&v, const Quaternion& q);
	void appendTranslationRotation(const Vector3&v, const Quaternion& q);
	void prependTranslationRotation(const Vector3&v, const Quaternion& q);

	Matrix& setTransform(const Vector3& translation,const Quaternion& rotation, const Vector3& scale);
	void appendTransform(const Vector3& translation,const Quaternion& rotation, const Vector3& scale);
	void prependTransform(const Vector3& translation,const Quaternion& rotation, const Vector3& scale);

	Vector4 transformVector4(const Vector4& v) const;
	Vector3 transformVector3(const Vector3& v) const;
	Vector3 rotateVector3(const Vector3& n) const;
	//AaBox transformBox(const AaBox& box) const;

	//can only do this when there's no scale
	Vector3 invTransformVector3(const Vector3& v) const;
	Vector3 invRotateVector3(const Vector3& n) const;

	const Vector3& getTranslation() const;
	Quaternion getRotation() const;
	void removeTranslation();

	bool isParity() const;

	Vector3 getScale() const;
	void removeScale();

	void removeRotation();

	bool getInverse(Matrix& out) const;

	void buildLookAtLH(const Vector3& eyePos, const Vector3& lookAt, const Vector3& up);
	void buildLookAtRH(const Vector3& eyePos, const Vector3& lookAt, const Vector3& up);

	void buildProjectPerspectiveFovLH(float fov, float aspect, float nearValue, float farValue);
	void buildProjectPerspectiveFovRH(float fov, float aspect, float nearValue, float farValue);

	void buildProjectOrthoLH(float width, float height, float nearValue, float farValue);
	void buildProjectOrthoRH(float width, float height, float nearValue, float farValue);

	void identity();

//public:
	//GRANDPA_API static const Matrix	ZERO;
	//GRANDPA_API static const Matrix	IDENTITY;
};

inline Matrix::Matrix()
{
	_11 = 1.0f; _12 = 0.0f; _13 = 0.0f; _14 = 0.0f;
	_21 = 0.0f; _22 = 1.0f; _23 = 0.0f; _24 = 0.0f;
	_31 = 0.0f; _32 = 0.0f; _33 = 1.0f; _34 = 0.0f;
	_41 = 0.0f; _42 = 0.0f; _43 = 0.0f; _44 = 1.0f;
}

inline Matrix::Matrix(	float f11, float f12, float f13, float f14,
						float f21, float f22, float f23, float f24,
						float f31, float f32, float f33, float f34,
						float f41, float f42, float f43, float f44)
{
	_11 = f11; _12 = f12; _13 = f13; _14 = f14;
	_21 = f21; _22 = f22; _23 = f23; _24 = f24;
	_31 = f31; _32 = f32; _33 = f33; _34 = f34;
	_41 = f41; _42 = f42; _43 = f43; _44 = f44;
}

inline Matrix::Matrix(const float* p)
{
	memcpy(_M, p, sizeof(Matrix));
}

inline Matrix::Matrix(const Matrix& m)
{
	memcpy(_M, m._M, sizeof(Matrix));
}

inline Vector3& Matrix::getVector3(size_t row)
{
	return *((Vector3*)M[row]);
}

inline Vector4& Matrix::getVector4(size_t row)
{
	return *((Vector4*)M[row]);
}

inline const Vector3& Matrix::getVector3(size_t row) const
{
	return *((Vector3*)M[row]);
}

inline const Vector4& Matrix::getVector4(size_t row) const
{
	return *((Vector4*)M[row]);
}

inline Matrix& Matrix::operator=(const Matrix& m)
{
	_11 = m._11; _12 = m._12; _13 = m._13; _14 = m._14;
	_21 = m._21; _22 = m._22; _23 = m._23; _24 = m._24;
	_31 = m._31; _32 = m._32; _33 = m._33; _34 = m._34;
	_41 = m._41; _42 = m._42; _43 = m._43; _44 = m._44;

	return *this;
}

inline Matrix& Matrix::operator+=(const Matrix& m)
{
	return *this = *this + m;
}

inline Matrix& Matrix::operator*=(const Matrix& m)
{
	return *this = *this * m;
}

inline bool Matrix::operator==(const Matrix& m) const
{
	return (memcmp(this, &m, sizeof(Matrix)) == 0);
}

inline bool Matrix::operator!=(const Matrix& m) const
{
	return (memcmp(this, &m, sizeof(Matrix)) != 0);
}

inline Matrix Matrix::getLerp(const Matrix& m, float l) const
{
	return *this + (m - *this) * l;
}

inline Matrix& Matrix::lerp(const Matrix& m, float l)
{
	return *this = *this + (m - *this) * l;
}

inline Matrix Matrix::operator*(const Matrix& m) const
{
	Matrix r;

	r._11 = _11 * m._11 + _12 * m._21 + _13 * m._31 + _14 * m._41;
	r._12 = _11 * m._12 + _12 * m._22 + _13 * m._32 + _14 * m._42;
	r._13 = _11 * m._13 + _12 * m._23 + _13 * m._33 + _14 * m._43;
	r._14 = _11 * m._14 + _12 * m._24 + _13 * m._34 + _14 * m._44;

	r._21 = _21 * m._11 + _22 * m._21 + _23 * m._31 + _24 * m._41;
	r._22 = _21 * m._12 + _22 * m._22 + _23 * m._32 + _24 * m._42;
	r._23 = _21 * m._13 + _22 * m._23 + _23 * m._33 + _24 * m._43;
	r._24 = _21 * m._14 + _22 * m._24 + _23 * m._34 + _24 * m._44;

	r._31 = _31 * m._11 + _32 * m._21 + _33 * m._31 + _34 * m._41;
	r._32 = _31 * m._12 + _32 * m._22 + _33 * m._32 + _34 * m._42;
	r._33 = _31 * m._13 + _32 * m._23 + _33 * m._33 + _34 * m._43;
	r._34 = _31 * m._14 + _32 * m._24 + _33 * m._34 + _34 * m._44;

	r._41 = _41 * m._11 + _42 * m._21 + _43 * m._31 + _44 * m._41;
	r._42 = _41 * m._12 + _42 * m._22 + _43 * m._32 + _44 * m._42;
	r._43 = _41 * m._13 + _42 * m._23 + _43 * m._33 + _44 * m._43;
	r._44 = _41 * m._14 + _42 * m._24 + _43 * m._34 + _44 * m._44;

	return r;
}

inline Matrix Matrix::operator*(float f) const
{
	Matrix r;

	r._11 = _11 * f;
	r._12 = _12 * f;
	r._13 = _13 * f;
	r._14 = 0.0f;
	
	r._21 = _21 * f;
	r._22 = _22 * f;
	r._23 = _23 * f;
	r._24 = 0.0f;

	r._31 = _31 * f;
	r._32 = _32 * f;
	r._33 = _33 * f;
	r._34 = 0.0f;

	r._41 = _41 * f;
	r._42 = _42 * f;
	r._43 = _43 * f;
	r._44 = 1.0f;
	return r;
}

inline Matrix Matrix::operator/(float f) const
{
	return *this * (1/f);
}

inline Matrix Matrix::operator+(const Matrix& m) const
{
	Matrix t;
	t._11 = _11 + m._11;
	t._12 = _12 + m._12;
	t._13 = _13 + m._13;
	t._14 = 0.0f;

	t._21 = _21 + m._21;
	t._22 = _22 + m._22;
	t._23 = _23 + m._23;
	t._24 = 0.0f;

	t._31 = _31 + m._31;
	t._32 = _32 + m._32;
	t._33 = _33 + m._33;
	t._34 = 0.0f;

	t._41 = _41 + m._41;
	t._42 = _42 + m._42;
	t._43 = _43 + m._43;
	t._44 = 1.0f;
	return t;
}

inline Matrix Matrix::operator-(const Matrix& m) const
{
	Matrix t;
	t._11 = _11 - m._11;
	t._12 = _12 - m._12;
	t._13 = _13 - m._13;
	t._14 = 0.0f;

	t._21 = _21 - m._21;
	t._22 = _22 - m._22;
	t._23 = _23 - m._23;
	t._24 = 0.0f;

	t._31 = _31 - m._31;
	t._32 = _32 - m._32;
	t._33 = _33 - m._33;
	t._34 = 0.0f;

	t._41 = _41 - m._41;
	t._42 = _42 - m._42;
	t._43 = _43 - m._43;
	t._44 = 1.0f;
	return t;
}

inline void Matrix::multiply_optimized(const Matrix& m, Matrix& out) const
{
	out._11 = _11 * m._11 + _12 * m._21 + _13 * m._31;
	out._12 = _11 * m._12 + _12 * m._22 + _13 * m._32;
	out._13 = _11 * m._13 + _12 * m._23 + _13 * m._33;
	out._14 = 0.0f;

	out._21 = _21 * m._11 + _22 * m._21 + _23 * m._31;
	out._22 = _21 * m._12 + _22 * m._22 + _23 * m._32;
	out._23 = _21 * m._13 + _22 * m._23 + _23 * m._33;
	out._24 = 0.0f;

	out._31 = _31 * m._11 + _32 * m._21 + _33 * m._31;
	out._32 = _31 * m._12 + _32 * m._22 + _33 * m._32;
	out._33 = _31 * m._13 + _32 * m._23 + _33 * m._33;
	out._34 = 0.0f;

	out._41 = _41 * m._11 + _42 * m._21 + _43 * m._31 + m._41;
	out._42 = _41 * m._12 + _42 * m._22 + _43 * m._32 + m._42;
	out._43 = _41 * m._13 + _42 * m._23 + _43 * m._33 + m._43;
	out._44 = 1.0f;
}
inline void Matrix::multiply(const Matrix& m)
{

	float _11s = _11 * m._11 + _12 * m._21 + _13 * m._31 + _14 * m._41;
	float _12s = _11 * m._12 + _12 * m._22 + _13 * m._32 + _14 * m._42;
	float _13s = _11 * m._13 + _12 * m._23 + _13 * m._33 + _14 * m._43;
	float _14s = _11 * m._14 + _12 * m._24 + _13 * m._34 + _14 * m._44;

	float _21s = _21 * m._11 + _22 * m._21 + _23 * m._31 + _24 * m._41;
	float _22s = _21 * m._12 + _22 * m._22 + _23 * m._32 + _24 * m._42;
	float _23s = _21 * m._13 + _22 * m._23 + _23 * m._33 + _24 * m._43;
	float _24s = _21 * m._14 + _22 * m._24 + _23 * m._34 + _24 * m._44;

	float _31s = _31 * m._11 + _32 * m._21 + _33 * m._31 + _34 * m._41;
	float _32s = _31 * m._12 + _32 * m._22 + _33 * m._32 + _34 * m._42;
	float _33s = _31 * m._13 + _32 * m._23 + _33 * m._33 + _34 * m._43;
	float _34s = _31 * m._14 + _32 * m._24 + _33 * m._34 + _34 * m._44;

	float _41s = _41 * m._11 + _42 * m._21 + _43 * m._31 + _44 * m._41;
	float _42s = _41 * m._12 + _42 * m._22 + _43 * m._32 + _44 * m._42;
	float _43s = _41 * m._13 + _42 * m._23 + _43 * m._33 + _44 * m._43;
	float _44s = _41 * m._14 + _42 * m._24 + _43 * m._34 + _44 * m._44;

	_11 = _11s; _12 = _12s; _13 = _13s; _14 = _14s;
	_21 = _21s; _22 = _22s; _23 = _23s; _24 = _24s;
	_31 = _31s; _32 = _32s; _33 = _33s; _34 = _34s;
	_41 = _41s; _42 = _42s; _43 = _43s; _44 = _44s;	
}


inline void Matrix::prependMultiply(const Matrix& m)
{

	float _11s = m._11 * _11 + m._12 * _21 + m._13 * _31 + m._14 * _41;
	float _12s = m._11 * _12 + m._12 * _22 + m._13 * _32 + m._14 * _42;
	float _13s = m._11 * _13 + m._12 * _23 + m._13 * _33 + m._14 * _43;
	float _14s = m._11 * _14 + m._12 * _24 + m._13 * _34 + m._14 * _44;

	float _21s = m._21 * _11 + m._22 * _21 + m._23 * _31 + m._24 * _41;
	float _22s = m._21 * _12 + m._22 * _22 + m._23 * _32 + m._24 * _42;
	float _23s = m._21 * _13 + m._22 * _23 + m._23 * _33 + m._24 * _43;
	float _24s = m._21 * _14 + m._22 * _24 + m._23 * _34 + m._24 * _44;

	float _31s = m._31 * _11 + m._32 * _21 + m._33 * _31 + m._34 * _41;
	float _32s = m._31 * _12 + m._32 * _22 + m._33 * _32 + m._34 * _42;
	float _33s = m._31 * _13 + m._32 * _23 + m._33 * _33 + m._34 * _43;
	float _34s = m._31 * _14 + m._32 * _24 + m._33 * _34 + m._34 * _44;

	float _41s = m._41 * _11 + m._42 * _21 + m._43 * _31 + m._44 * _41;
	float _42s = m._41 * _12 + m._42 * _22 + m._43 * _32 + m._44 * _42;
	float _43s = m._41 * _13 + m._42 * _23 + m._43 * _33 + m._44 * _43;
	float _44s = m._41 * _14 + m._42 * _24 + m._43 * _34 + m._44 * _44;

	_11 = _11s; _12 = _12s; _13 = _13s; _14 = _14s;
	_21 = _21s; _22 = _22s; _23 = _23s; _24 = _24s;
	_31 = _31s; _32 = _32s; _33 = _33s; _34 = _34s;
	_41 = _41s; _42 = _42s; _43 = _43s; _44 = _44s;	
}

inline Matrix& Matrix::setTranslation(const Vector3& v)
{
	_41 = v.X;
	_42 = v.Y;
	_43 = v.Z;
	return *this;
}



inline void Matrix::appendTranslation(const Vector3& v)
{
	Matrix m;
	m._41 = v.X;
	m._42 = v.Y;
	m._43 = v.Z;
	multiply(m);
}

inline void Matrix::appendTranslation(const float &x,const float &y,const float &z)
{
	Matrix m;
	m._41 = x;
	m._42 = y;
	m._43 = z;
	multiply(m);
}

inline void Matrix::prependTranslation(const Vector3& v)
{
	Matrix m;
	m._41 = v.X;
	m._42 = v.Y;
	m._43 = v.Z;
	prependMultiply(m);
}

inline void Matrix::prependTranslation(const float &x,const float &y,const float &z)
{
	Matrix m;
	m._41 = x;
	m._42 = y;
	m._43 = z;
	prependMultiply(m);
}

inline Matrix& Matrix::setRotation(const Quaternion& q)
{
	float xx2 = q.X * q.X * 2;
	float yy2 = q.Y * q.Y * 2;
	float zz2 = q.Z * q.Z * 2;
	float xy2 = q.X * q.Y * 2;
	float zw2 = q.Z * q.W * 2;
	float xz2 = q.X * q.Z * 2; 
	float yw2 = q.Y * q.W * 2;
	float yz2 = q.Y * q.Z * 2;
	float xw2 = q.X * q.W * 2;

	_11 = 1-yy2-zz2;	_12 =   xy2+zw2;	_13 =   xz2-yw2;
	_21 =   xy2-zw2;	_22 = 1-xx2-zz2;	_23 =   yz2+xw2;
	_31 =   xz2+yw2;	_32 =   yz2-xw2;	_33 = 1-xx2-yy2;
	return *this;
}

inline void Matrix::appendRotation(const Quaternion& q)
{
	Matrix m;
	m.setRotation(q);
	multiply(m);
}



inline void Matrix::prependRotation(const Quaternion& q)
{
	Matrix m;
	m.setRotation(q);
	prependMultiply(m);
}

inline void Matrix::appendRotationAxis(const float &degrees,const Vector3 &axis)
{
	float pi = 3.1415926;
	Quaternion q(axis,degrees*pi/180);
	appendRotation(q);
}

inline void Matrix::prependRotationAxis(const float &degrees,const Vector3 &axis)
{
	float pi = 3.1415926;
	Quaternion q(axis,degrees*pi/180);
	prependRotation(q);
}

inline Matrix& Matrix::setScale(const Vector3& s){

	_11 = s.X;	_12 = 0.0f;	_13 = 0.0f;	_14 = 0.0f;
	_21 = 0.0f;	_22 = s.Y;	_23 = 0.0f;	_24 = 0.0f;
	_31 = 0.0f;	_32 = 0.0f;	_33 = s.Z;	_34 = 0.0f;
	_41 = 0.0f;	_42 = 0.0f;	_43 = 0.0f;	_44 = 1.0f;
	return *this;
}

inline void Matrix::appendScale(const Vector3& v){
	Matrix m;
	m.setScale(v);
	multiply(m);
}
inline void Matrix::appendScale(const float &x,const float &y,const float &z)
{
	Matrix m;
	m._11 = x;
	m._22 = y;
	m._33 = z;
	multiply(m);
}

inline void Matrix::prependScale(const Vector3& v){
	Matrix m;
	m.setScale(v);
	prependMultiply(m);
}

inline void Matrix::prependScale(const float &x,const float &y,const float &z)
{
	Matrix m;
	m._11 = x;
	m._22 = y;
	m._33 = z;
	prependMultiply(m);
}
inline Matrix& Matrix::setTranslationRotation(const Vector3& v, const Quaternion& q)
{
	float xx2 = q.X * q.X * 2;
	float yy2 = q.Y * q.Y * 2;
	float zz2 = q.Z * q.Z * 2;
	float xy2 = q.X * q.Y * 2;
	float zw2 = q.Z * q.W * 2;
	float xz2 = q.X * q.Z * 2;
	float yw2 = q.Y * q.W * 2;
	float yz2 = q.Y * q.Z * 2;
	float xw2 = q.X * q.W * 2;

	_11 = 1-yy2-zz2;	_12 =   xy2+zw2;	_13 =   xz2-yw2;	_14 = 0.0f;
	_21 =   xy2-zw2;	_22 = 1-xx2-zz2;	_23 =   yz2+xw2;	_24 = 0.0f;
	_31 =   xz2+yw2;	_32 =   yz2-xw2;	_33 = 1-xx2-yy2;	_34 = 0.0f;
	_41 = v.X;			_42 = v.Y;			_43 = v.Z;			_44 = 1.0f;
	return *this;
}

inline void Matrix::appendTranslationRotation(const Vector3&v, const Quaternion& q)
{
	Matrix m;
	m.setTranslationRotation(v,q);
	multiply(m);
}

inline void Matrix::prependTranslationRotation(const Vector3&v, const Quaternion& q)
{
	Matrix m;
	m.setTranslationRotation(v,q);
	prependMultiply(m);
}
inline Matrix& Matrix::setTransform(const Vector3& v,
									const Quaternion& q,
									const Vector3& s)
{
	float xx2 = q.X * q.X * 2;
	float yy2 = q.Y * q.Y * 2;
	float zz2 = q.Z * q.Z * 2;
	float xy2 = q.X * q.Y * 2;
	float zw2 = q.Z * q.W * 2;
	float xz2 = q.X * q.Z * 2; 
	float yw2 = q.Y * q.W * 2;
	float yz2 = q.Y * q.Z * 2;
	float xw2 = q.X * q.W * 2;

	_11 = (1-yy2-zz2) * s.X;	_12 = ( xy2+zw2) * s.Y;		_13 = ( xz2-yw2) * s.Z;		_14 = 0.0f;
	_21 = ( xy2-zw2) * s.X;		_22 = (1-xx2-zz2) * s.Y;	_23 = ( yz2+xw2) * s.Z;		_24 = 0.0f;
	_31 = ( xz2+yw2) * s.X;		_32 = ( yz2-xw2) * s.Y;		_33 = (1-xx2-yy2) * s.Z;	_34 = 0.0f;
	_41 = v.X;					_42 = v.Y;					_43 = v.Z;					_44 = 1.0f;
	return *this;
}


inline void Matrix::appendTransform(const Vector3& v,const Quaternion& q,const Vector3& s)
{
	Matrix m;
	m.setTransform(v,q,s);
	multiply(m);
}


inline void Matrix::prependTransform(const Vector3& v,const Quaternion& q,const Vector3& s)
{
	Matrix m;
	m.setTransform(v,q,s);
	prependMultiply(m);
}

inline Vector4 Matrix::transformVector4(const Vector4& v) const
{
	Vector4 result;
	result.X = v.X * _11 + v.Y * _21 + v.Z * _31 + v.W * _41;
	result.Y = v.X * _12 + v.Y * _22 + v.Z * _32 + v.W * _42;
	result.Z = v.X * _13 + v.Y * _23 + v.Z * _33 + v.W * _43;
	result.W = v.W;
	return result;
}

inline Vector3 Matrix::transformVector3(const Vector3& v) const
{
	Vector3 result;
	result.X = v.X * _11 + v.Y * _21 + v.Z * _31 + _41;
	result.Y = v.X * _12 + v.Y * _22 + v.Z * _32 + _42;
	result.Z = v.X * _13 + v.Y * _23 + v.Z * _33 + _43;
	return result;
}

inline Vector3 Matrix::rotateVector3(const Vector3& n) const
{
	Vector3 result;
	result.X = n.X * _11 + n.Y * _21 + n.Z * _31;
	result.Y = n.X * _12 + n.Y * _22 + n.Z * _32;
	result.Z = n.X * _13 + n.Y * _23 + n.Z * _33;
	return result;
}
/*
inline AaBox Matrix::transformBox(const AaBox& box) const
{
	AaBox result;

	const float* Amin = (const float*)&box.MinEdge;
	const float* Amax = (const float*)&box.MaxEdge;
	float* Bmin = (float*)&result.MinEdge;
	float* Bmax = (float*)&result.MaxEdge;

	Bmin[0] = Bmax[0] = _41;
	Bmin[1] = Bmax[1] = _42;
	Bmin[2] = Bmax[2] = _43;

	unsigned long i, j;
	const Matrix& m = *this;

	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			float a = m.M[j][i] * Amin[j];
			float b = m.M[j][i] * Amax[j];

			if (a < b)
			{
				Bmin[i] += a;
				Bmax[i] += b;
			}
			else
			{
				Bmin[i] += b;
				Bmax[i] += a;
			}
		}
	}
	return result;
}
*/
inline Vector3 Matrix::invTransformVector3(const Vector3& v) const
{
	Vector3 temp, result;
	temp.X = v.X - _41;
	temp.Y = v.Y - _42;
	temp.Z = v.Z - _43;

	result.X = temp.X * _11 + temp.Y * _12 + temp.Z * _13;
	result.Y = temp.X * _21 + temp.Y * _22 + temp.Z * _23;
	result.Z = temp.X * _31 + temp.Y * _32 + temp.Z * _33;
	return result;
}

inline Vector3 Matrix::invRotateVector3(const Vector3& n) const
{
	Vector3 result;

	result.X = n.X * _11 + n.Y * _12 + n.Z * _13;
	result.Y = n.X * _21 + n.Y * _22 + n.Z * _23;
	result.Z = n.X * _31 + n.Y * _32 + n.Z * _33;
	
	return result;
}

inline const Vector3& Matrix::getTranslation() const
{
	return getVector3(3);
}

inline Quaternion Matrix::getRotation() const
{
	return *this;
}

inline void Matrix::removeTranslation()
{
	_41 = 0.0f;
	_42 = 0.0f;
	_43 = 0.0f;
}

inline bool Matrix::isParity() const
{
	return getVector3(2).dot(getVector3(0).cross(getVector3(1))) < 0.0f;
}

//always mirror with z axis
inline Vector3 Matrix::getScale() const
{
	if(isParity())
	{
		return Vector3(getVector3(0).length(),
						getVector3(1).length(),
						-getVector3(2).length());
	}
	return Vector3(getVector3(0).length(),
					getVector3(1).length(),
					getVector3(2).length());
}

//will get shit when scale equals 0
inline void Matrix::removeScale()
{
	Vector3 scale = getScale();
	_11 /= scale.X;	_12 /= scale.X;	_13 /= scale.X;
	_21 /= scale.Y;	_22 /= scale.Y;	_23 /= scale.Y;
	_31 /= scale.Z;	_32 /= scale.Z;	_33 /= scale.Z;
}

//will remove scale as well
inline void Matrix::removeRotation()
{
	_11 = 1.0f;	_12 = 0.0f; _13 = 0.0f;
	_21 = 0.0f;	_22 = 1.0f; _23 = 0.0f;
	_31 = 0.0f;	_32 = 0.0f;	_33 = 1.0f;
}

inline bool Matrix::getInverse(Matrix& out) const
{
	float d = (M[0][0] * M[1][1] - M[0][1] * M[1][0]) * (M[2][2]) -
			  (M[0][0] * M[1][2] - M[0][2] * M[1][0]) * (M[2][1]) +
			  (M[0][1] * M[1][2] - M[0][2] * M[1][1]) * (M[2][0]);

	if (fabs(d) < 0.00001f)
	{
		return false;
	}
	d = 1.0f / d;

	out.M[0][0] = d * (M[1][1] * (M[2][2]                              ) + M[1][2] * (                  - M[2][1]          )                                                      );
	out.M[0][1] = d * (M[2][1] * (M[0][2]                              ) + M[2][2] * (                  - M[0][1]          )                                                      );
	out.M[0][2] = d * (                                                                                                                      (M[0][1] * M[1][2] - M[0][2] * M[1][1]));
	out.M[1][0] = d * (M[1][2] * (M[2][0]                              )                                                       + M[1][0] * (                  - M[2][2]          ));
	out.M[1][1] = d * (M[2][2] * (M[0][0]                              )                                                       + M[2][0] * (                  - M[0][2]          ));
	out.M[1][2] = d * (                                                    +           (M[0][2] * M[1][0] - M[0][0] * M[1][2])                                                      );
	out.M[2][0] = d * (                                                    + M[1][0] * (M[2][1]                              ) + M[1][1] * (                  - M[2][0]          ));
	out.M[2][1] = d * (                                                    + M[2][0] * (M[0][1]                              ) + M[2][1] * (                  - M[0][0]          ));
	out.M[2][2] = d * (          (M[0][0] * M[1][1] - M[0][1] * M[1][0])                                                                                                            );
	out.M[3][0] = d * (M[1][0] * (M[2][2] * M[3][1] - M[2][1] * M[3][2]) + M[1][1] * (M[2][0] * M[3][2] - M[2][2] * M[3][0]) + M[1][2] * (M[2][1] * M[3][0] - M[2][0] * M[3][1]));
	out.M[3][1] = d * (M[2][0] * (M[0][2] * M[3][1] - M[0][1] * M[3][2]) + M[2][1] * (M[0][0] * M[3][2] - M[0][2] * M[3][0]) + M[2][2] * (M[0][1] * M[3][0] - M[0][0] * M[3][1]));
	out.M[3][2] = d * (M[3][0] * (M[0][2] * M[1][1] - M[0][1] * M[1][2]) + M[3][1] * (M[0][0] * M[1][2] - M[0][2] * M[1][0]) + M[3][2] * (M[0][1] * M[1][0] - M[0][0] * M[1][1]));
	out.M[3][3] = d * (M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) + M[0][1] * (M[1][2] * M[2][0] - M[1][0] * M[2][2]) + M[0][2] * (M[1][0] * M[2][1] - M[1][1] * M[2][0]));
	return true;
}

inline void Matrix:: buildLookAtLH(const Vector3& eyePos, const Vector3& lookAt, const Vector3& up)
{
	Vector3 zaxis = lookAt - eyePos;
	zaxis.normalize();

	Vector3 xaxis = up.cross(zaxis);
	xaxis.normalize();

	Vector3 yaxis = zaxis.cross(xaxis);

	_11 = xaxis.X;
	_12 = yaxis.X;
	_13 = zaxis.X;
	_14 = 0.0f;

	_21 = xaxis.Y;
	_22 = yaxis.Y;
	_23 = zaxis.Y;
	_24 = 0.0f;

	_31 = xaxis.Z;
	_32 = yaxis.Z;
	_33 = zaxis.Z;
	_34 = 0.0f;

	_41 = -xaxis.dot(eyePos);
	_42 = -yaxis.dot(eyePos);
	_43 = -zaxis.dot(eyePos);
	_44 = 1.0f;
}

inline void Matrix:: buildLookAtRH(const Vector3& eyePos, const Vector3& lookAt, const Vector3& up)
{
	Vector3 zaxis = eyePos - lookAt;
	zaxis.normalize();

	Vector3 xaxis = up.cross(zaxis);
	xaxis.normalize();

	Vector3 yaxis = zaxis.cross(xaxis);

	_11 = xaxis.X;
	_12 = yaxis.X;
	_13 = zaxis.X;
	_14 = 0.0f;

	_21 = xaxis.Y;
	_22 = yaxis.Y;
	_23 = zaxis.Y;
	_24 = 0.0f;

	_31 = xaxis.Z;
	_32 = yaxis.Z;
	_33 = zaxis.Z;
	_34 = 0.0f;

	_41 = -xaxis.dot(eyePos);
	_42 = -yaxis.dot(eyePos);
	_43 = -zaxis.dot(eyePos);
	_44 = 1.0f;
}

inline void Matrix:: buildProjectPerspectiveFovLH(float fov, float aspect, float nearValue, float farValue)
{
	double h = 1.0 / tan(fov / 2.0);
	float w = (float)(h / aspect);

	_11 = w;
	_12 = 0.0f;
	_13 = 0.0f;
	_14 = 0.0f;

	_21 = 0.0f;
	_22 = (float)h;
	_23 = 0.0f;
	_24 = 0.0f;

	_31 = 0.0f;
	_32 = 0.0f;
	_33 = farValue / (farValue - nearValue);
	_34 = 1.0f;

	_41 = 0.0f;
	_42 = 0.0f;
	_43 = -nearValue * farValue / (farValue - nearValue);
	_44 = 0.0f;
}

inline void Matrix:: buildProjectPerspectiveFovRH(float fov, float aspect, float nearValue, float farValue)
{
	double h = 1.0 / tan(fov / 2.0);
	float w = (float)(h / aspect);

	_11 = w;
	_12 = 0.0f;
	_13 = 0.0f;
	_14 = 0.0f;

	_21 = 0.0f;
	_22 = (float)h;
	_23 = 0.0f;
	_24 = 0.0f;

	_31 = 0.0f;
	_32 = 0.0f;
	_33 = farValue / (nearValue - farValue);	//DirectX version
	//_33 = farValue + nearValue / (nearValue - farValue); // OpenGL version
	_34 = -1.0f;

	_41 = 0;
	_42 = 0;
	_43 = nearValue * farValue / (nearValue - farValue);	//DirectX version
	//_43 = 2.0f * nearValue * farValue / (nearValue - farValue); // OpenGL version
	_44 = 0;
}

inline void Matrix:: buildProjectOrthoLH(float width, float height, float nearValue, float farValue)
{
	_11 = 2.0f / width;
	_12 = 0.0f;
	_13 = 0.0f;
	_14 = 0.0f;

	_21 = 0.0f;
	_22 = 2.0f / height;
	_23 = 0.0f;
	_24 = 0.0f;

	_31 = 0.0f;
	_32 = 0.0f;
	_33 = 1.0f / (farValue - nearValue);
	_34 = 0.0f;

	_41 = 0.0f;
	_42 = 0.0f;
	_43 = nearValue / (nearValue - farValue);
	_44 = 1.0f;
}

inline void Matrix:: buildProjectOrthoRH(float width, float height, float nearValue, float farValue)
{
	_11 = 2.0f / width;
	_12 = 0.0f;
	_13 = 0.0f;
	_14 = 0.0f;

	_21 = 0.0f;
	_22 = 2.0f / height;
	_23 = 0.0f;
	_24 = 0.0f;

	_31 = 0.0f;
	_32 = 0.0f;
	_33 = 1.0f / (nearValue - farValue);
	_34 = 0.0f;

	_41 = 0.0f;
	_42 = 0.0f;
	_43 = nearValue / (nearValue - farValue);
	_44 = -1.0f;
}

inline void Matrix:: identity()
{
	_11 = 1.0f; _12 = 0.0f; _13 = 0.0f; _14 = 0.0f;
	_21 = 0.0f; _22 = 1.0f; _23 = 0.0f; _24 = 0.0f;
	_31 = 0.0f; _32 = 0.0f; _33 = 1.0f; _34 = 0.0f;
	_41 = 0.0f; _42 = 0.0f; _43 = 0.0f; _44 = 1.0f;	
}



#endif
