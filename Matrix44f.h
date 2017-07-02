#pragma once
#include <stdio.h>
#include <math.h>
#include "Vector3f.h"
#include "Vector4f.h"
namespace ComputerGraphicsCourse{
	struct Matrix44f
	{
		union {
			float Array[16];	// óÒóDêÊ
			struct { 
				float Val11, Val21, Val31, Val41;
				float Val12, Val22, Val32, Val42;
				float Val13, Val23, Val33, Val43;
				float Val14, Val24, Val34, Val44;
			};
		};

		Matrix44f():
		Val11(0.0), Val12(0.0), Val13(0.0), Val14(0.0),
			Val21(0.0), Val22(0.0), Val23(0.0), Val24(0.0),
			Val31(0.0), Val32(0.0), Val33(0.0), Val34(0.0),
			Val41(0.0), Val42(0.0), Val43(0.0), Val44(0.0){}

		Matrix44f(
			const float _val11, const float _val12, const float _val13, const float _val14,
			const float _val21, const float _val22, const float _val23, const float _val24,
			const float _val31, const float _val32, const float _val33, const float _val34,
			const float _val41, const float _val42, const float _val43, const float _val44
			):
		Val11(_val11), Val12(_val12), Val13(_val13), Val14(_val14),
			Val21(_val21), Val22(_val22), Val23(_val23), Val24(_val24),
			Val31(_val31), Val32(_val32), Val33(_val33), Val34(_val34),
			Val41(_val41), Val42(_val42), Val43(_val43), Val44(_val44){}

		Matrix44f(const Matrix44f& m):
		Val11(m.Val11), Val12(m.Val12), Val13(m.Val13), Val14(m.Val14),
			Val21(m.Val21), Val22(m.Val22), Val23(m.Val23), Val24(m.Val24),
			Val31(m.Val31), Val32(m.Val32), Val33(m.Val33), Val34(m.Val34),
			Val41(m.Val41), Val42(m.Val42), Val43(m.Val43), Val44(m.Val44){}

		inline static Matrix44f Identity()
		{
			return Matrix44f(
				1.0, 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0,
				0.0, 0.0, 0.0, 1.0);
		}

		static Matrix44f Transpose(const Matrix44f& mat)
		{
			Matrix44f ret;

			for(int i = 0; i < 4; i++)
			{
				for(int j = 0; j < 4; j++)
				{
					ret(i, j) = mat(j, i);
				}
			}

			return ret;
		}

		static inline float Determinant(const Matrix44f& m)
		{
			float Det = 0.0f;

			Det += m.Val11*m.Val22*m.Val33*m.Val44 + m.Val11*m.Val23*m.Val34*m.Val44 + m.Val11*m.Val24*m.Val32*m.Val43;
			Det += m.Val12*m.Val21*m.Val34*m.Val43 + m.Val12*m.Val23*m.Val31*m.Val42 + m.Val12*m.Val24*m.Val33*m.Val41;
			Det += m.Val13*m.Val21*m.Val32*m.Val44 + m.Val13*m.Val22*m.Val34*m.Val41 + m.Val13*m.Val24*m.Val31*m.Val42;
			Det += m.Val14*m.Val21*m.Val33*m.Val42 + m.Val14*m.Val22*m.Val31*m.Val43 + m.Val14*m.Val23*m.Val32*m.Val41;
			Det -= m.Val11*m.Val22*m.Val34*m.Val43 + m.Val11*m.Val23*m.Val32*m.Val44 + m.Val11*m.Val24*m.Val33*m.Val42;
			Det -= m.Val12*m.Val21*m.Val33*m.Val44 + m.Val12*m.Val23*m.Val34*m.Val41 + m.Val12*m.Val24*m.Val31*m.Val43;
			Det -= m.Val13*m.Val21*m.Val34*m.Val42 + m.Val13*m.Val22*m.Val31*m.Val44 + m.Val13*m.Val24*m.Val32*m.Val41;
			Det -= m.Val14*m.Val21*m.Val32*m.Val43 + m.Val14*m.Val22*m.Val33*m.Val41 + m.Val14*m.Val23*m.Val31*m.Val42;

			return Det;
		}
		static inline Matrix44f Inverse(const Matrix44f& m)
		{
			float b11 = m.Val22*m.Val33*m.Val44 + m.Val23*m.Val34*m.Val42 + m.Val24*m.Val32*m.Val43 - m.Val22*m.Val34*m.Val43 - m.Val23*m.Val32*m.Val44 - m.Val24*m.Val33*m.Val42;
			float b12 = m.Val12*m.Val34*m.Val43 + m.Val13*m.Val32*m.Val44 + m.Val14*m.Val33*m.Val42 - m.Val12*m.Val33*m.Val44 - m.Val13*m.Val34*m.Val42 - m.Val14*m.Val32*m.Val43;
			float b13 = m.Val12*m.Val23*m.Val44 + m.Val13*m.Val24*m.Val42 + m.Val14*m.Val22*m.Val43 - m.Val12*m.Val24*m.Val43 - m.Val13*m.Val22*m.Val44 - m.Val14*m.Val23*m.Val42;
			float b14 = m.Val12*m.Val24*m.Val33 + m.Val13*m.Val22*m.Val34 + m.Val14*m.Val23*m.Val32 - m.Val12*m.Val23*m.Val34 - m.Val13*m.Val24*m.Val32 - m.Val14*m.Val22*m.Val33;

			float b21 = m.Val21*m.Val34*m.Val43 + m.Val23*m.Val31*m.Val44 + m.Val24*m.Val33*m.Val41 - m.Val21*m.Val33*m.Val44 - m.Val23*m.Val34*m.Val41 - m.Val24*m.Val31*m.Val43;
			float b22 = m.Val11*m.Val33*m.Val44 + m.Val13*m.Val34*m.Val41 + m.Val14*m.Val31*m.Val43 - m.Val11*m.Val34*m.Val43 - m.Val13*m.Val31*m.Val44 - m.Val14*m.Val33*m.Val41;
			float b23 = m.Val11*m.Val24*m.Val43 + m.Val13*m.Val21*m.Val44 + m.Val14*m.Val23*m.Val41 - m.Val11*m.Val23*m.Val44 - m.Val13*m.Val24*m.Val41 - m.Val14*m.Val21*m.Val43;
			float b24 = m.Val11*m.Val23*m.Val34 + m.Val13*m.Val24*m.Val31 + m.Val14*m.Val21*m.Val33 - m.Val11*m.Val24*m.Val33 - m.Val13*m.Val21*m.Val34 - m.Val14*m.Val23*m.Val31;

			float b31 = m.Val21*m.Val32*m.Val44 + m.Val22*m.Val34*m.Val41 + m.Val24*m.Val31*m.Val42 - m.Val21*m.Val34*m.Val42 - m.Val22*m.Val31*m.Val44 - m.Val24*m.Val32*m.Val41;
			float b32 = m.Val11*m.Val34*m.Val42 + m.Val12*m.Val31*m.Val44 + m.Val14*m.Val32*m.Val41 - m.Val11*m.Val32*m.Val44 - m.Val12*m.Val34*m.Val41 - m.Val14*m.Val31*m.Val42;
			float b33 = m.Val11*m.Val22*m.Val44 + m.Val12*m.Val24*m.Val41 + m.Val14*m.Val21*m.Val42 - m.Val11*m.Val24*m.Val42 - m.Val12*m.Val21*m.Val44 - m.Val14*m.Val22*m.Val41;
			float b34 = m.Val11*m.Val24*m.Val32 + m.Val12*m.Val21*m.Val34 + m.Val14*m.Val22*m.Val31 - m.Val11*m.Val22*m.Val34 - m.Val12*m.Val24*m.Val31 - m.Val14*m.Val21*m.Val32;

			float b41 = m.Val21*m.Val33*m.Val42 + m.Val22*m.Val31*m.Val43 + m.Val23*m.Val32*m.Val41 - m.Val21*m.Val32*m.Val43 - m.Val22*m.Val33*m.Val41 - m.Val23*m.Val31*m.Val42;
			float b42 = m.Val11*m.Val32*m.Val43 + m.Val12*m.Val33*m.Val41 + m.Val13*m.Val31*m.Val42 - m.Val11*m.Val33*m.Val42 - m.Val12*m.Val31*m.Val43 - m.Val13*m.Val32*m.Val41;
			float b43 = m.Val11*m.Val23*m.Val42 + m.Val12*m.Val21*m.Val43 + m.Val13*m.Val22*m.Val41 - m.Val11*m.Val22*m.Val43 - m.Val12*m.Val23*m.Val41 - m.Val13*m.Val21*m.Val42;
			float b44 = m.Val11*m.Val22*m.Val33 + m.Val12*m.Val23*m.Val31 + m.Val13*m.Val21*m.Val32 - m.Val11*m.Val23*m.Val32 - m.Val12*m.Val21*m.Val33 - m.Val13*m.Val22*m.Val31;

			float det_inv = 1.0f / Matrix44f::Determinant(m);

			Matrix44f ret;

			ret.Val11 = det_inv * b11;
			ret.Val12 = det_inv * b12;
			ret.Val13 = det_inv * b13;
			ret.Val14 = det_inv * b14;

			ret.Val21 = det_inv * b21;
			ret.Val22 = det_inv * b22;
			ret.Val23 = det_inv * b23;
			ret.Val24 = det_inv * b24;

			ret.Val31 = det_inv * b31;
			ret.Val32 = det_inv * b32;
			ret.Val33 = det_inv * b33;
			ret.Val34 = det_inv * b34;

			ret.Val41 = det_inv * b41;
			ret.Val42 = det_inv * b42;
			ret.Val43 = det_inv * b43;
			ret.Val44 = det_inv * b44;

			return ret;
		}

		static Matrix44f LookAtRH(const Vector3f& cameraPosition, const Vector3f& cameraTarget, const Vector3f& cameraUpVector)
		{	
			Matrix44f mat;
			Vector3f dir;
			dir.X = cameraPosition.X - cameraTarget.X;
			dir.Y = cameraPosition.Y - cameraTarget.Y;
			dir.Z = cameraPosition.Z - cameraTarget.Z;

			Vector3f zaxis = Vector3f::Normalize(dir);
			Vector3f xaxis = Vector3f::Normalize(Vector3f::Cross(cameraUpVector, zaxis));
			Vector3f yaxis = Vector3f::Cross(zaxis, xaxis);

			mat.Array[0] = xaxis.X;	mat.Array[1] = yaxis.X;	mat.Array[2]  = zaxis.X;	mat.Array[3]	= 0;
			mat.Array[4] = xaxis.Y;	mat.Array[5] = yaxis.Y;	mat.Array[6]  = zaxis.Y;	mat.Array[7]	= 0;
			mat.Array[8] = xaxis.Z;	mat.Array[9] = yaxis.Z;	mat.Array[10] = zaxis.Z;	mat.Array[11] = 0;
			mat.Array[12] = -Vector3f::Dot(xaxis, cameraPosition);
			mat.Array[13] = -Vector3f::Dot(yaxis, cameraPosition);	
			mat.Array[14] = -Vector3f::Dot(zaxis, cameraPosition);
			mat.Array[15] = 1.0f;

			return mat;
		}
		static Matrix44f OrthoRH(const float left, const float right, const float bottom, const float top, const float nearClip, const float farClip)
		{
			Matrix44f mat;
			mat.Array[0] = 2.0f/(right-left);	mat.Array[4] = 0.0;					mat.Array[8] = 0.0;					mat.Array[12] = -(right+left)/(right-left);
			mat.Array[1] = 0.0;					mat.Array[5] = 2.0f/(top-bottom);	mat.Array[9] = 0.0;					mat.Array[13] = -(top+bottom)/(top-bottom);
			mat.Array[2] = 0.0;					mat.Array[6] = 0.0;					mat.Array[10] = -2.0f/(farClip-nearClip);	mat.Array[14] = -(farClip+nearClip)/(farClip-nearClip);
			mat.Array[3] = 0.0;					mat.Array[7] = 0.0;					mat.Array[11] = 0.0;				mat.Array[15] = 1.0;
			return mat;
		}
		static Matrix44f PerspectiveFovRH(const float fieldOfViewY, const float aspectRatio, const float znearPlane, const float zfarPlane)
		{
			Matrix44f mat;

			float halfFov = 0.5f*fieldOfViewY;
			float h = cos(halfFov)/sin(halfFov);
			float w = h / aspectRatio;

			mat.Array[0]	= w;		mat.Array[1]	= 0.0;			mat.Array[2] = 0.0;	mat.Array[3] = 0.0;
			mat.Array[4]	= 0.0;		mat.Array[5]	= h;			mat.Array[6] = 0.0;	mat.Array[7] = 0.0;
			mat.Array[8]	= 0.0;		mat.Array[9]	= 0.0;			mat.Array[10] = zfarPlane/(znearPlane-zfarPlane);	mat.Array[11] = -1.0;
			mat.Array[12] = 0.0;		mat.Array[13] = 0.0;			mat.Array[14] = znearPlane*zfarPlane/(znearPlane-zfarPlane);	mat.Array[15] = 0.0;

			return mat;
		}

		static Matrix44f Translate(const float tx, const float ty, const float tz)
		{
			Matrix44f mat = Matrix44f::Identity();
			mat.Val14 = tx;
			mat.Val24 = ty;
			mat.Val34 = tz;

			return mat;
		}
		static Matrix44f RotateX(const float angle)
		{
			Matrix44f mat = Matrix44f::Identity();

			mat.Array[5] = cos(angle);	mat.Array[6]  = sin(angle);
			mat.Array[9] = -sin(angle);	mat.Array[10] = cos(angle);

			return mat;
		}
		static Matrix44f RotateY(const float angle)
		{
			Matrix44f mat = Matrix44f::Identity();

			mat.Array[10] = cos(angle);	mat.Array[8]  = sin(angle);
			mat.Array[2] = -sin(angle);	mat.Array[0] = cos(angle);

			return mat;
		}
		static Matrix44f RotateZ(const float angle)
		{
			Matrix44f mat = Matrix44f::Identity();

			mat.Array[0] = cos(angle);	mat.Array[1]  = sin(angle);
			mat.Array[4] = -sin(angle);	mat.Array[5] = cos(angle);

			return mat;
		}
		static Matrix44f Scale(const float x, const float y, const float z)
		{
			Matrix44f mat = Matrix44f();

			mat.Array[0] = x;
			mat.Array[5] = y;
			mat.Array[10] = z;
			mat.Array[15] = 1.0f;

			return mat;
		}
		static Matrix44f Scale(const Vector3f& vec)
		{
			return Matrix44f::Scale(vec.X, vec.Y, vec.Z);
		}
		static Matrix44f RotateAxis(const Vector3f& axisRotation, const float angle)
		{
			Matrix44f rot;
			float Vx,Vy,Vz;
			float c,s;

			Vx = axisRotation.X;
			Vy = axisRotation.Y;
			Vz = axisRotation.Z;

			c = cos(angle);
			s = sin(angle);

			rot.Val11 = Vx * Vx * (1.0f - c) + c;		rot.Val12 = Vx * Vy * (1.0f - c) - Vz * s;	rot.Val13 = Vz * Vx * (1.0f - c) + Vy * s;	rot.Val14 = 0.0f;
			rot.Val21 = Vx * Vy * (1.0f - c) + Vz * s;	rot.Val22 = Vy * Vy * (1.0f - c) + c;		rot.Val23 = Vy * Vz * (1.0f - c) - Vx * s;	rot.Val24 = 0.0f;
			rot.Val31 = Vz * Vx * (1.0f - c) - Vy * s;	rot.Val32 = Vy * Vz * (1.0f - c) + Vx * s;	rot.Val33 = Vz * Vz * (1.0f - c) + c;		rot.Val34 = 0.0f;
			rot.Val41 = 0.0f;							rot.Val42 = 0.0f;							rot.Val43 = 0.0f;							rot.Val44 = 1.0f;
			return rot;
		}

		// íPçÄââéZéq
		inline Matrix44f operator - () const
		{
			return Matrix44f(
				-Val11, -Val12, -Val13, -Val14,
				-Val21, -Val22, -Val23, -Val24,
				-Val31, -Val32, -Val33, -Val34,
				-Val41, -Val42, -Val43, -Val44);
		}

		inline float & operator()(int i, int j)
		{
			return Array[4*j+i];
		}
		inline const float operator()(int i, int j) const
		{
			return Array[4*j+i];
		}

		// 2çÄââéZéq
		friend const Matrix44f operator+(const Matrix44f& left, const Matrix44f& right)
		{
			return Matrix44f(
				left.Val11+right.Val11, left.Val12+right.Val12, left.Val13+right.Val13, left.Val14+right.Val14,
				left.Val21+right.Val21, left.Val22+right.Val22, left.Val23+right.Val23, left.Val24+right.Val24,
				left.Val31+right.Val31, left.Val32+right.Val32, left.Val33+right.Val33, left.Val34+right.Val34,
				left.Val41+right.Val41, left.Val42+right.Val42, left.Val43+right.Val43, left.Val44+right.Val44);
		}
		friend const Matrix44f operator-(const Matrix44f& left, const Matrix44f& right)
		{
			return Matrix44f(
				left.Val11-right.Val11, left.Val12-right.Val12, left.Val13-right.Val13, left.Val14-right.Val14,
				left.Val21-right.Val21, left.Val22-right.Val22, left.Val23-right.Val23, left.Val24-right.Val24,
				left.Val31-right.Val31, left.Val32-right.Val32, left.Val33-right.Val33, left.Val34-right.Val34,
				left.Val41-right.Val41, left.Val42-right.Val42, left.Val43-right.Val43, left.Val44-right.Val44);
		}
		friend const Matrix44f operator*(const Matrix44f& left, const Matrix44f& right)
		{
			Matrix44f m;

			for(int i = 0; i < 4; i++)
			{
				for(int j = 0; j < 4; j++)
				{
					float t = 0.0;
					for(int k = 0; k < 4; k++)
					{
						t += left.Array[4*k+i]*right.Array[4*j+k];
					}
					m.Array[j*4+i] = t;
				}
			}
			return m;
		}
		inline friend const Vector4f operator*(const Matrix44f& left, const Vector4f& right)
		{
			Vector4f v;

			return Vector4f(
				left.Val11*right.X+left.Val12*right.Y+left.Val13*right.Z+left.Val14*right.W,
				left.Val21*right.X+left.Val22*right.Y+left.Val23*right.Z+left.Val24*right.W,
				left.Val31*right.X+left.Val32*right.Y+left.Val33*right.Z+left.Val34*right.W,
				left.Val41*right.X+left.Val42*right.Y+left.Val43*right.Z+left.Val44*right.W);
		}

		//Debug
		inline void Dump()
		{
			for(int i = 0; i < 4; i++)
			{
				printf("(%g, %g, %g, %g)\n", this->Array[4*0+i], Array[4*1+i], Array[4*2+i], Array[4*3+i]);
			}
		}

	};


};