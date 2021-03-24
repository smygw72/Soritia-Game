#pragma once

#include "Vector3f.h"
#include "Matrix44f.h"
#include <math.h>

namespace ComputerGraphicsCourse{

	class Quaternion
	{
	public:
		float X, Y, Z, W;

		Quaternion(){X = Y = Z = 0.0; W = 1.0;};
		Quaternion(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w;}

		// オペレータ
		// http://www.arakin.dyndns.org/gl_torusquat.php
		Quaternion operator*(const Quaternion& m)
		{

			float w = this->W * m.W - this->X * m.X - this->Y * m.Y - this->Z * m.Z;
			float x = this->W * m.X + this->X * m.W + this->Y * m.Z - this->Z * m.Y;
			float y = this->W * m.Y - this->X * m.Z + this->Y * m.W + this->Z * m.X;
			float z = this->W * m.Z + this->X * m.Y - this->Y * m.X + this->Z * m.W;

			return Quaternion(x, y, z, w);
		}

		// 2つのベクトルからクォータニオンを生成
		static Quaternion QuaternionFrom2Vectors(Vector3f from, Vector3f to)
		{
			// ▲内積Vector3.Dot メソッド
			float dot = Vector3f::Dot(from, to);

			// ▲外積Vector3.Cross メソッド
			Vector3f cross = Vector3f::Cross(from, to);

			// ▲2(1+cosθ) Math.Sqrt メソッド、float への型変換に注意
			float s = (float)sqrt((1.0 + dot) * 2.0);

			return Quaternion(cross.X / s, cross.Y / s, cross.Z / s, s / 2.0f);
		}
		static Matrix44f RotationQuaternion(const Quaternion q)
		{
			Matrix44f m;

			float qx, qy, qz, qw;
			qx = q.X;
			qy = q.Y;
			qz = q.Z;
			qw = q.W;

			m.Val11 = 1.0f - 2.0f * qy * qy - 2.0f * qz * qz;
			m.Val12 = 2.0f * qx * qy + 2.0f * qw * qz;
			m.Val13 = 2.0f * qx * qz - 2.0f * qw * qy;
			m.Val14 = 0.0f;

			m.Val21 = 2.0f * qx * qy - 2.0f * qw * qz;
			m.Val22 = 1.0f - 2.0f * qx * qx - 2.0f * qz * qz;
			m.Val23 = 2.0f * qy * qz + 2.0f * qw * qx;
			m.Val24 = 0.0f;

			m.Val31 = 2.0f * qx * qz + 2.0f * qw * qy;
			m.Val32 = 2.0f * qy * qz - 2.0f * qw * qx;
			m.Val33 = 1.0f - 2.0f * qx * qx - 2.0f * qy * qy;
			m.Val34 = 0.0f;

			m.Val41 = m.Val42 = m.Val43 = 0.0f;
			m.Val44 = 1.0f;

			return Matrix44f::Transpose(m);

		}
		// http://marupeke296.com/DXG_No58_RotQuaternionTrans.html
		static Quaternion RotationMatrix(const Matrix44f& m)
		{
			

			// 最大成分を検索
			float elem[ 4 ]; // 0:x, 1:y, 2:z, 3:w
			elem[ 0 ] =  m.Val11 - m.Val22 - m.Val33 + 1.0f;
			elem[ 1 ] = -m.Val11 + m.Val22 - m.Val33 + 1.0f;
			elem[ 2 ] = -m.Val11 - m.Val22 + m.Val33 + 1.0f;
			elem[ 3 ] =  m.Val11 + m.Val22 + m.Val33 + 1.0f;


			unsigned biggestIndex = 0;
			for ( int i = 1; i < 4; i++ ) {
				if ( elem[i] > elem[biggestIndex] )
					biggestIndex = i;
			}

			if ( elem[biggestIndex] < 0.0f )
				return Quaternion(); // 引数の行列に間違いあり！

			// 最大要素の値を算出
			float qx, qy, qz, qw;
			float *q[4] = {&qx, &qy, &qz, &qw};
			float v = sqrtf( elem[biggestIndex] ) * 0.5f;
			*q[biggestIndex] = v;
			float mult = 0.25f / v;

			switch ( biggestIndex ) {
				case 0: // x
					*q[1] = (m.Val12 + m.Val21) * mult;
					*q[2] = (m.Val31 + m.Val13) * mult;
					*q[3] = (m.Val23 - m.Val32) * mult;
					break;
				case 1: // y
					*q[0] = (m.Val12 + m.Val21) * mult;
					*q[2] = (m.Val23 + m.Val32) * mult;
					*q[3] = (m.Val31 - m.Val13) * mult;
					break;
				case 2: // z
					*q[0] = (m.Val31 + m.Val13) * mult;
					*q[1] = (m.Val23 + m.Val32) * mult;
					*q[3] = (m.Val12 - m.Val21) * mult;
					break;
				case 3: // w
					*q[0] = (m.Val23 - m.Val32) * mult;
					*q[1] = (m.Val31 - m.Val13) * mult;
					*q[2] = (m.Val12 - m.Val21) * mult;
		break;
			}

			return Quaternion(qx, qy, qz, qw);
		}


	};
};