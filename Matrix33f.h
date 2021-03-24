#pragma once
#include <stdio.h>
#include <math.h>
#include "Vector3f.h"
namespace ComputerGraphicsCourse{
	struct Matrix33f
	{
		union {
			float Array[9];	// óÒóDêÊ
			struct { 
				float Val11, Val21, Val31;
				float Val12, Val22, Val32;
				float Val13, Val23, Val33;
			};
		};

		Matrix33f():
		Val11(0.0), Val12(0.0), Val13(0.0),
		Val21(0.0), Val22(0.0), Val23(0.0),
		Val31(0.0), Val32(0.0), Val33(0.0){}

		Matrix33f(
			const float _val11, const float _val12, const float _val13,
			const float _val21, const float _val22, const float _val23,
			const float _val31, const float _val32, const float _val33
			):
		Val11(_val11), Val12(_val12), Val13(_val13),
		Val21(_val21), Val22(_val22), Val23(_val23),
		Val31(_val31), Val32(_val32), Val33(_val33){}

		Matrix33f(const Matrix33f& m):
		Val11(m.Val11), Val12(m.Val12), Val13(m.Val13),
		Val21(m.Val21), Val22(m.Val22), Val23(m.Val23), 
		Val31(m.Val31), Val32(m.Val32), Val33(m.Val33) {}

		inline static Matrix33f Identity()
		{
			return Matrix33f(
				1.0, 0.0, 0.0,
				0.0, 1.0, 0.0,
				0.0, 0.0, 1.0);
		}

		static Matrix33f Transpose(const Matrix33f& mat)
		{
			Matrix33f ret;

			for(int i = 0; i < 3; i++)
			{
				for(int j = 0; j < 3; j++)
				{
					ret(i, j) = mat(j, i);
				}
			}

			return ret;
		}

		static inline float Determinant(const Matrix33f& m)
		{
			float Det = 0.0f;

			Det += m.Val11*m.Val22*m.Val33;
			Det += m.Val21*m.Val32*m.Val13;
			Det += m.Val31*m.Val12*m.Val23;

			Det -= m.Val11*m.Val32*m.Val23;
			Det -= m.Val31*m.Val22*m.Val13;
			Det -= m.Val21*m.Val12*m.Val33;

			return Det;
		}
		static inline Matrix33f Inverse(const Matrix33f& m)
		{
			float b11 = m.Val22*m.Val33 - m.Val23*m.Val32;
			float b12 = m.Val13*m.Val32 - m.Val12*m.Val33;
			float b13 = m.Val12*m.Val23 - m.Val13*m.Val22;

			float b21 = m.Val23*m.Val31 - m.Val21*m.Val33;
			float b22 = m.Val11*m.Val33 - m.Val13*m.Val31;
			float b23 = m.Val13*m.Val21 - m.Val11*m.Val23;

			float b31 = m.Val21*m.Val32 - m.Val22*m.Val31;
			float b32 = m.Val12*m.Val31 - m.Val11*m.Val32;
			float b33 = m.Val11*m.Val22 - m.Val12*m.Val21;

			float det_inv = 1.0f / Matrix33f::Determinant(m);

			Matrix33f ret;

			ret.Val11 = det_inv * b11;
			ret.Val12 = det_inv * b12;
			ret.Val13 = det_inv * b13;

			ret.Val21 = det_inv * b21;
			ret.Val22 = det_inv * b22;
			ret.Val23 = det_inv * b23;

			ret.Val31 = det_inv * b31;
			ret.Val32 = det_inv * b32;
			ret.Val33 = det_inv * b33;

			return ret;
		}


		// íPçÄââéZéq
		inline Matrix33f operator - () const
		{
			return Matrix33f(
				-Val11, -Val12, -Val13,
				-Val21, -Val22, -Val23,
				-Val31, -Val32, -Val33);
		}

		inline float & operator()(int i, int j)
		{
			return Array[3*j+i];
		}
		inline const float operator()(int i, int j) const
		{
			return Array[3*j+i];
		}

		// 2çÄââéZéq
		friend const Matrix33f operator+(const Matrix33f& left, const Matrix33f& right)
		{
			return Matrix33f(
				left.Val11+right.Val11, left.Val12+right.Val12, left.Val13+right.Val13,
				left.Val21+right.Val21, left.Val22+right.Val22, left.Val23+right.Val23,
				left.Val31+right.Val31, left.Val32+right.Val32, left.Val33+right.Val33);
		}
		friend const Matrix33f operator-(const Matrix33f& left, const Matrix33f& right)
		{
			return Matrix33f(
				left.Val11-right.Val11, left.Val12-right.Val12, left.Val13-right.Val13,
				left.Val21-right.Val21, left.Val22-right.Val22, left.Val23-right.Val23,
				left.Val31-right.Val31, left.Val32-right.Val32, left.Val33-right.Val33);
		}
		friend const Matrix33f operator*(const Matrix33f& left, const Matrix33f& right)
		{
			Matrix33f m;

			for(int i = 0; i < 3; i++)
			{
				for(int j = 0; j < 3; j++)
				{
					float t = 0.0;
					for(int k = 0; k < 3; k++)
					{
						t += left.Array[3*k+i]*right.Array[3*j+k];
					}
					m.Array[j*3+i] = t;
				}
			}
			return m;
		}
		inline friend const Vector3f operator*(const Matrix33f& left, const Vector3f& right)
		{

			return Vector3f(
				left.Val11*right.X+left.Val12*right.Y+left.Val13*right.Z,
				left.Val21*right.X+left.Val22*right.Y+left.Val23*right.Z,
				left.Val31*right.X+left.Val32*right.Y+left.Val33*right.Z);
		}
		//Debug
		inline void Dump()
		{
			for(int i = 0; i < 3; i++)
			{
				printf("(%g, %g, %g)\n", this->Array[3*0+i], Array[3*1+i], Array[3*2+i]);
			}
		}

	};


};