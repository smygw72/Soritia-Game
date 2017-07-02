/*
*  camera.h
*  iPadGlTest001
*
*  Created by Hiroyuki Kubo on 10/09/15.
*  Copyright 2010 Waseda University. All rights reserved.
*
*/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>

#include "Vector3f.h"
#include "Matrix44f.h"
#include "Quaternion.h"

namespace ComputerGraphicsCourse{


	class Camera{

	private:
		Matrix44f _world;
		Matrix44f _view;
		Matrix44f _proj;

		Matrix44f _mv;
		Matrix44f _mvp;
		Matrix44f _timv;

		Vector3f _cameraPosition;
		Vector3f _initCamPos;
		Vector3f _cameraTarget;
		Vector3f _initTarget;
		Vector3f _upVector;

		int _width, _height;

		Vector3f _fromAxis; // ���ʂ̃x�N�g��

		Quaternion _newQuat; // �V�����N�H�[�^�j�I��
		Quaternion _oldQuat; // �O�̃N�H�[�^�j�I��

		int _mouseX, _mouseY;	

		bool _AltKeyPressed;
		bool _ShiftKeyPressed;
		bool _CtrlKeyPressed;

	public:

		void UpdateMatrix()
		{
			_mv = _view * _world;
			_mvp = _proj * _mv;
			_timv = Matrix44f::Transpose(Matrix44f::Inverse(_mv));
		}

		void Initialize(int width, int height, Vector3f cameraPosition, Vector3f target, Vector3f upVector)
		{	
			_world = Matrix44f::Identity();
			_view = Matrix44f::Identity();
			_proj = Matrix44f::Identity();

			_width = width;
			_height = height;
			_cameraPosition = cameraPosition;
			_initCamPos = cameraPosition;
			_initTarget = target;
			_cameraTarget = target;
			_upVector = upVector;

			_view = Matrix44f::LookAtRH(_cameraPosition, _cameraTarget, upVector);

			float vFov = 40.0f/180.0f*(float)M_PI;
			float aspect = (float)width/(float)height;		
			_proj = Matrix44f::PerspectiveFovRH(vFov, aspect, 1.0f, 50.0f);

			_fromAxis = Vector3f(0.0f, 1.0f, 0.0f); // ���ʂ̃x�N�g��
			_fromAxis = upVector;
			_newQuat = Quaternion(); // �V�����N�H�[�^�j�I��
			_oldQuat = Quaternion(); // �O�̃N�H�[�^�j�I��		
		}
		void Reset(void)
		{
			Initialize(_width, _height, _initCamPos, _initTarget, _upVector);
			UpdateMatrix();
		}

		Matrix44f World(void){ return _world;}
		Matrix44f View(void){ return _view; }
		Matrix44f Projection(void) { return _proj;}
		Matrix44f MV(void) { return _mv;}
		Matrix44f MVP(void) { return _mvp;}
		Matrix44f TIMV(void) {return _timv;}
		Vector3f CameraPosition(void) {return _cameraPosition; }

		// �R���X�g���N�^
		Camera(){
			Initialize(768, 1024, Vector3f(0, 0, -50), Vector3f(0, 0, 0), Vector3f(0, 1, 0));
		}
		Camera(int width, int height,
			float camPosX, float camPosY, float camPosZ,
			float targetX, float targetY, float targetZ,
			float upX, float upY, float upZ)
			:_AltKeyPressed(false), _ShiftKeyPressed(false), _CtrlKeyPressed(false)
		{
			Initialize(width, height,
				Vector3f(camPosX, camPosY, camPosZ),
				Vector3f(targetX, targetY, targetZ),
				Vector3f(upX, upY, upZ)
				);
			UpdateMatrix();
		}

		// �X�N���[�����W����A���z�P�ʋ���̃x�N�g�����擾
		Vector3f ScreenToVector(float screenPointX, float screenPointY)
		{
			float radius = 1.0f;
			float x = -(screenPointX - _width / 2.0f) / (radius * _width / 2.0f);
			float y = (screenPointY - _height / 2.0f) / (radius * _height / 2.0f);
			if(_cameraPosition.Z < 0.0) y = -y;
			float z = 0.0f;
			float mag = (x * x) + (y * y);
			if (mag > 1.0f)
			{
				float scale = 1.0f / (float)sqrt(mag);
				x *= scale;
				y *= scale;
			}
			else
				z = -1.0f * (float)sqrt(1.0f - mag);
			return Vector3f::Normalize(Vector3f(x, y, z));
		}

		void OnMouseDown(int x, int y)
		{		
			// ��]�̏���
			_fromAxis = ScreenToVector((float)x, (float)y);
			//_oldQuat = Quaternion::RotationMatrix(_world);

		}
		void OnMouseUp(int x, int y)
		{
			_oldQuat = _newQuat;
		}
		void OnMouseMove(int x, int y, bool LeftButtonDown, bool MiddleButtonDown, bool RightButtonDown)
		{
			//�ړ��ʂ��v�Z
			int dx = x - _mouseX;
			int dy = y - _mouseY;


			//���݂̃J�[�\���ʒu���o���Ă���
			_mouseX = x;
			_mouseY = y;

			// Alt��������Ă����瓮��B
			if (_AltKeyPressed)
			{
				if (MiddleButtonDown || (LeftButtonDown && RightButtonDown))
				{
					//�J���� ���s�ړ�
					_cameraPosition = _cameraPosition + Vector3f(-dx * 0.01f, dy * 0.01f, 0.0f);
					_cameraTarget = _cameraTarget + Vector3f(-dx * 0.01f, dy * 0.01f, 0.0f);

					_view = Matrix44f::LookAtRH(_cameraPosition, _cameraTarget, Vector3f(0.0f, 1.0f, 0.0f));
				}
				else if (LeftButtonDown)
				{

					// ��]
					// ���[���h����]
					Vector3f toAxis = ScreenToVector((float)x, (float)y);

					Quaternion q;
					q = Quaternion::QuaternionFrom2Vectors(_fromAxis, toAxis);
					_newQuat = q * _oldQuat;

					_world = Quaternion::RotationQuaternion(_newQuat);
				}
				else if(RightButtonDown)
				{
					// �J�������璍���_�܂ł̃x�N�g��
					Vector3f cam2target = _cameraTarget - _cameraPosition;
					_cameraPosition = _cameraPosition + dx * 0.005f * cam2target;
					_view = Matrix44f::LookAtRH(_cameraPosition, _cameraTarget, Vector3f(0.0f, 1.0f, 0.0f));

				}


				UpdateMatrix();
			}
		}
		void OnKeyUp(bool AltKeyPressed, bool ShiftKeyPressed, bool CtrlKeyPressed)
		{
			// �X�e�[�^�X�̍X�V
			_AltKeyPressed = AltKeyPressed;
			_ShiftKeyPressed = ShiftKeyPressed;
			_CtrlKeyPressed = CtrlKeyPressed;
		}
		void OnKeyDown(bool AltKeyPressed, bool ShiftKeyPressed, bool CtrlKeyPressed)
		{
			// �X�e�[�^�X�̍X�V
			_AltKeyPressed = AltKeyPressed;
			_ShiftKeyPressed = ShiftKeyPressed;
			_CtrlKeyPressed = CtrlKeyPressed;
		}
	};

};