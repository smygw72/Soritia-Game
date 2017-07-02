#pragma once
#include <stdio.h>
#include <math.h>
namespace ComputerGraphicsCourse{
	struct Vector4f
	{
		union {
			struct { float X,Y,Z,W; };
			struct { float R,G,B,A; };
			float Array[4];
		};

		Vector4f():X(0.0), Y(0.0), Z(0.0), W(0.0){	}
		Vector4f(const float _x, const float _y, const float _z, const float _w):X(_x), Y(_y), Z(_z), W(_w){}
		Vector4f(const Vector4f& v):X(v.X), Y(v.Y), Z(v.Z), W(v.X){}

		inline static float Dot(const Vector4f& left, const Vector4f& right)
		{
			return left.X*right.X + left.Y*right.Y + left.Z*right.Z + left.W*right.W;
		}
		inline static float LengthSq(const Vector4f& v)
		{
			return v.X*v.X + v.Y*v.Y + v.Z*v.Z + v.W*v.W;
		}
		inline static float Length(const Vector4f& v)
		{
			return sqrt(Vector4f::LengthSq(v));
		}
		inline static Vector4f Normalize(const Vector4f& v)
		{
			float len = Vector4f::Length(v);
			return 1.0f / len * v;
		}

		// íPçÄââéZéq
		inline Vector4f operator - () const
		{
			return Vector4f(-X, -Y, -Z, -W);
		}
		inline float & operator[](int i)
		{
			return Array[i];
		}
		inline const float operator[](int i) const
		{
			return Array[i];
		}
				
		inline Vector4f& operator +=(const Vector4f& v)
		{
			X += v.X;
			Y += v.Y;
			Z += v.Z;
			W += v.W;
			return *this;
		}
		inline Vector4f& operator -=(const Vector4f& v)
		{
			X -= v.X;
			Y -= v.Y;
			Z -= v.Z;
			W -= v.W;
			return *this;
		}

		// 2çÄââéZéq
		inline friend const Vector4f operator+(const Vector4f& left, const Vector4f& right)
		{
			return Vector4f(left.X + right.X, left.Y + right.Y, left.Z + right.Z, left.W + right.W);
		}
		inline friend const Vector4f operator-(const Vector4f& left, const Vector4f& right)
		{
			return Vector4f(left.X - right.X, left.Y - right.Y, left.Z - right.Z, left.W - right.W);
		}
		inline friend const Vector4f operator*(const float left, const Vector4f& right)
		{
			return Vector4f(left * right.X, left * right.Y, left * right.Z, left * right.W);
		}
		//Debug
		inline void Dump()
		{
			printf("(%g, %g, %g, %g)\n", X, Y, Z, W);
		}

	};
};