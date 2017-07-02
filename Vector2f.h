#pragma once
#include<stdio.h>
#include<math.h>

namespace ComputerGraphicsCourse{
	struct Vector2f
	{
		union {
			struct { float X,Y; };
			float Array[2];
		};

		Vector2f():X(0.0), Y(0.0){	}
		Vector2f(const float _x, const float _y):X(_x), Y(_y){}
		Vector2f(const Vector2f& v):X(v.X), Y(v.Y){}

		inline static float Dot(const Vector2f& left, const Vector2f& right)
		{
			return left.X*right.X + left.Y*right.Y;
		}

		inline static float LengthSq(const Vector2f& v)
		{
			return v.X*v.X + v.Y*v.Y;
		}
		inline static float Length(const Vector2f& v)
		{
			return sqrt(Vector2f::LengthSq(v));
		}
		inline static Vector2f Normalize(const Vector2f& v)
		{
			float len = Vector2f::Length(v);
			return 1.0f / len * v;
		}

		// íPçÄââéZéq
		inline Vector2f operator - () const
		{
			return Vector2f(-X, -Y);
		}
		inline float & operator[](int i)
		{
			return Array[i];
		}
		inline const float operator[](int i) const
		{
			return Array[i];
		}
				
		inline Vector2f& operator +=(const Vector2f& v)
		{
			X += v.X;
			Y += v.Y;
			return *this;
		}
		inline Vector2f& operator -=(const Vector2f& v)
		{
			X -= v.X;
			Y -= v.Y;
			return *this;
		}
		// 2çÄââéZéq
		inline friend const Vector2f operator+(const Vector2f& left, const Vector2f& right)
		{
			return Vector2f(left.X + right.X, left.Y + right.Y);
		}
		inline friend const Vector2f operator-(const Vector2f& left, const Vector2f& right)
		{
			return Vector2f(left.X - right.X, left.Y - right.Y);
		}
		inline friend const Vector2f operator*(const float left, const Vector2f& right)
		{
			return Vector2f(left * right.X, left * right.Y);
		}
		//Debug
		inline void Dump()
		{
			printf("(%g, %g)\n", X, Y);
		}

	};
};