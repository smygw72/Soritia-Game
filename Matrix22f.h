#pragma once
#include <stdio.h>
#include <math.h>
#include "Vector2f.h"
namespace ComputerGraphicsCourse{
	struct Matrix22f
	{
		union {
			float Array[4];	// óÒóDêÊ
			struct { 
				float Val11, Val21;
				float Val12, Val22;
			};
		};

		Matrix22f():
		Val11(0.0), Val12(0.0),
		Val21(0.0), Val22(0.0){}

		Matrix22f(
			const float _val11, const float _val12,
			const float _val21, const float _val22
			):
		Val11(_val11), Val12(_val12),
		Val21(_val21), Val22(_val22){}

		Matrix22f(const Matrix22f& m):
		Val11(m.Val11), Val12(m.Val12),
		Val21(m.Val21), Val22(m.Val22){}

		inline static Matrix22f Identity()
		{
			return Matrix22f(
				1.0, 0.0,
				0.0, 1.0);
		}

		static Matrix22f Transpose(const Matrix22f& mat)
		{
			Matrix22f ret;

			for(int i = 0; i < 2; i++)
			{
				for(int j = 0; j < 2; j++)
				{
					ret(i, j) = mat(j, i);
				}
			}

			return ret;
		}

		static inline float Determinant(const Matrix22f& m)
		{
			float Det = m.Val11*m.Val22 - m.Val12*m.Val21;

			return Det;
		}
		static inline Matrix22f Inverse(const Matrix22f& m)
		{
			float b11 =  m.Val22;	float b12 = -m.Val12;
			float b21 = -m.Val21;	float b22 = m.Val11;

			float det_inv = 1.0f / Matrix22f::Determinant(m);

			Matrix22f ret;

			ret.Val11 = det_inv * b11;
			ret.Val12 = det_inv * b12;
			
			ret.Val21 = det_inv * b21;
			ret.Val22 = det_inv * b22;

			return ret;
		}



		// íPçÄââéZéq
		inline Matrix22f operator - () const
		{
			return Matrix22f(
				-Val11, -Val12,
				-Val21, -Val22);
		}

		inline float & operator()(int i, int j)
		{
			return Array[2*j+i];
		}
		inline const float operator()(int i, int j) const
		{
			return Array[2*j+i];
		}

		// 2çÄââéZéq
		friend const Matrix22f operator+(const Matrix22f& left, const Matrix22f& right)
		{
			return Matrix22f(
				left.Val11+right.Val11, left.Val12+right.Val12,
				left.Val21+right.Val21, left.Val22+right.Val22);
		}
		friend const Matrix22f operator-(const Matrix22f& left, const Matrix22f& right)
		{
			return Matrix22f(
				left.Val11-right.Val11, left.Val12-right.Val12,
				left.Val21-right.Val21, left.Val22-right.Val22);
		}
		friend const Matrix22f operator*(const Matrix22f& left, const Matrix22f& right)
		{
			Matrix22f m;

			for(int i = 0; i < 2; i++)
			{
				for(int j = 0; j < 2; j++)
				{
					float t = 0.0;
					for(int k = 0; k < 2; k++)
					{
						t += left.Array[2*k+i]*right.Array[2*j+k];
					}
					m.Array[j*2+i] = t;
				}
			}
			return m;
		}
				
		inline friend const Vector2f operator*(const Matrix22f& left, const Vector2f& right)
		{

			return Vector2f(
				left.Val11*right.X+left.Val12*right.Y,
				left.Val21*right.X+left.Val22*right.Y);
		}

		//Debug
		inline void Dump()
		{
			for(int i = 0; i < 2; i++)
			{
				printf("(%g, %g)\n", this->Array[2*0+i], Array[2*1+i]);
			}
		}

	};


};