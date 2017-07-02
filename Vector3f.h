#pragma once
#include<stdio.h>
#include<math.h>

namespace ComputerGraphicsCourse{
	struct Vector3f
	{
		union {
			struct { float X,Y,Z; };
			struct { float R,G,B; };
			float Array[3];
		};

		Vector3f():X(0.0), Y(0.0), Z(0.0){	}
		Vector3f(const float _x, const float _y, const float _z):X(_x), Y(_y), Z(_z){}
		Vector3f(const Vector3f& v):X(v.X), Y(v.Y), Z(v.Z){}

		inline static float Dot(const Vector3f& left, const Vector3f& right)
		{
			return left.X*right.X + left.Y*right.Y + left.Z*right.Z;
		}
		inline static Vector3f Cross(const Vector3f& left, const Vector3f& right)
		{
			return Vector3f(
				left.Y*right.Z - left.Z*right.Y,
				left.Z*right.X - left.X*right.Z,
				left.X*right.Y - left.Y*right.X);
		}
		inline static float LengthSq(const Vector3f& v)
		{
			return v.X*v.X + v.Y*v.Y + v.Z*v.Z;
		}
		inline static float Length(const Vector3f& v)
		{
			return sqrt(Vector3f::LengthSq(v));
		}
		inline static Vector3f Normalize(const Vector3f& v)
		{
			float len = Vector3f::Length(v);
			return 1.0f / len * v;
		}
		// 極座標から変換
		inline static Vector3f FromSpherical(const float r, const float theta, const float phi)
		{
			return r * Vector3f(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
		}

		// 単項演算子
		inline Vector3f operator - () const
		{
			return Vector3f(-X, -Y, -Z);
		}
		inline float & operator[](int i)
		{
			return Array[i];
		}
		inline const float operator[](int i) const
		{
			return Array[i];
		}
		inline Vector3f& operator +=(const Vector3f& v)
		{
			X += v.X;
			Y += v.Y;
			Z += v.Z;
			return *this;
		}
		inline Vector3f& operator -=(const Vector3f& v)
		{
			X -= v.X;
			Y -= v.Y;
			Z -= v.Z;
			return *this;
		}
		// 2項演算子
		inline friend const Vector3f operator+(const Vector3f& left, const Vector3f& right)
		{
			return Vector3f(left.X + right.X, left.Y + right.Y, left.Z + right.Z);
		}
		inline friend const Vector3f operator-(const Vector3f& left, const Vector3f& right)
		{
			return Vector3f(left.X - right.X, left.Y - right.Y, left.Z - right.Z);
		}
		inline friend const Vector3f operator*(const float left, const Vector3f& right)
		{
			return Vector3f(left * right.X, left * right.Y, left * right.Z);
		}				

		//Debug
		inline void Dump()
		{
			printf("(%g, %g, %g)\n", X, Y, Z);
		}

	};
};