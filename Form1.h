#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glPanel.h"
#include "camera.h"
#include "stdafx.h"

using namespace std;

/*-----------------�ϐ��錾---------------------*/

/* �C���X�^���X�̐錾 */
Klondike klondike;

/* �ϐ��錾 */

// Field
vector<int> field_number[7];
vector<string> field_symbol[7];
vector<bool> field_direction[7];

// Stack
vector<int> stack_number;
vector<string> stack_symbol(3);

// Suit
vector<int> suit_number(4);


/*---------------------------------------------*/


namespace OpenGlFormApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace ComputerGraphicsCourse;

	/// <summary>
	/// Form1 �̊T�v
	///
	/// �x��: ���̃N���X�̖��O��ύX����ꍇ�A���̃N���X���ˑ����邷�ׂĂ� .resx �t�@�C���Ɋ֘A�t����ꂽ
	///          �}�l�[�W ���\�[�X �R���p�C�� �c�[���ɑ΂��� 'Resource File Name' �v���p�e�B��
	///          �ύX����K�v������܂��B���̕ύX���s��Ȃ��ƁA
	///          �f�U�C�i�ƁA���̃t�H�[���Ɋ֘A�t����ꂽ���[�J���C�Y�ς݃��\�[�X�Ƃ��A
	///          ���������݂ɗ��p�ł��Ȃ��Ȃ�܂��B
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	private:	
		HWND _hWnd;
		HDC _hDC;
		HGLRC _hglrc;
		Camera* _camera;
	private: System::Windows::Forms::Button^  startButton;
	private: System::Windows::Forms::Button^  moveButton1;
	private: System::Windows::Forms::Button^  moveButton2;
	private: System::Windows::Forms::Button^  moveButton3;
	private: System::Windows::Forms::Button^  moveButton4;
	private: System::Windows::Forms::Button^  moveButton5;
	private: System::Windows::Forms::Button^  moveButton6;
	private: System::Windows::Forms::Button^  moveButton7;
	private: System::Windows::Forms::Button^  openButton;
	private: System::Windows::Forms::Button^  moveButton;
	private: System::Windows::Forms::Button^  ShiftButton;
	private: OpenGLNet::glPanel^  glPanel1;

	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: �����ɃR���X�g���N�^ �R�[�h��ǉ����܂�
			//
			System::IntPtr hWnd = glPanel1->Handle;

			Init((HWND)hWnd.ToInt32());
			SetCurrent();

			// �J�����̈ʒu��(0, 0, 10)
			float camposX = 0.0; 
			float camposY = 0.0; 
			float camposZ = 10.0;

			// �J�����̏Ə��͌��_
			float targetX = 0.0, targetY = 0.0, targetZ = 0.0;

			// ������������ɂȂ�悤�ɁB
			float upX = 0.0, upY = 1.0, upZ = 0.0;

			// �J������p��
			_camera = new Camera(glPanel1->Width, glPanel1->Height, 
				camposX, camposY, camposZ, targetX, targetY, targetZ, upX, upY, upZ);
		}

	protected:
		/// <summary>
		/// �g�p���̃��\�[�X�����ׂăN���[���A�b�v���܂��B
		/// </summary>
		~Form1()
		{
			wglMakeCurrent (NULL, NULL) ;	/* �����_�����O �R���e�L�X�g���J�����gout*/
			wglDeleteContext (_hglrc);		/* �����_�����O �R���e�L�X�g�̍폜 */
			ReleaseDC(_hWnd, _hDC );		/* GetDC �Ŋm�ۂ��������J��*/

			if (components)
			{
				delete components;
			}
		}

	protected: 

	private:
		/// <summary>
		/// �K�v�ȃf�U�C�i�ϐ��ł��B
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �f�U�C�i �T�|�[�g�ɕK�v�ȃ��\�b�h�ł��B���̃��\�b�h�̓��e��
		/// �R�[�h �G�f�B�^�ŕύX���Ȃ��ł��������B
		/// </summary>
		void InitializeComponent(void)
		{
			this->startButton = (gcnew System::Windows::Forms::Button());
			this->moveButton1 = (gcnew System::Windows::Forms::Button());
			this->moveButton2 = (gcnew System::Windows::Forms::Button());
			this->moveButton3 = (gcnew System::Windows::Forms::Button());
			this->moveButton4 = (gcnew System::Windows::Forms::Button());
			this->moveButton5 = (gcnew System::Windows::Forms::Button());
			this->moveButton6 = (gcnew System::Windows::Forms::Button());
			this->moveButton7 = (gcnew System::Windows::Forms::Button());
			this->openButton = (gcnew System::Windows::Forms::Button());
			this->moveButton = (gcnew System::Windows::Forms::Button());
			this->ShiftButton = (gcnew System::Windows::Forms::Button());
			this->glPanel1 = (gcnew OpenGLNet::glPanel());
			this->SuspendLayout();
			// 
			// startButton
			// 
			this->startButton->BackColor = System::Drawing::Color::SpringGreen;
			this->startButton->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 24, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(128)));
			this->startButton->Location = System::Drawing::Point(44, 35);
			this->startButton->Name = L"startButton";
			this->startButton->Size = System::Drawing::Size(203, 79);
			this->startButton->TabIndex = 1;
			this->startButton->Text = L"Game start !";
			this->startButton->UseVisualStyleBackColor = false;
			this->startButton->Click += gcnew System::EventHandler(this, &Form1::_startButton_Click);
			// 
			// moveButton1
			// 
			this->moveButton1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->moveButton1->Location = System::Drawing::Point(88, 167);
			this->moveButton1->Name = L"moveButton1";
			this->moveButton1->Size = System::Drawing::Size(94, 44);
			this->moveButton1->TabIndex = 2;
			this->moveButton1->Text = L"move";
			this->moveButton1->UseVisualStyleBackColor = true;
			this->moveButton1->Click += gcnew System::EventHandler(this, &Form1::_moveButton1_Click);
			// 
			// moveButton2
			// 
			this->moveButton2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->moveButton2->Location = System::Drawing::Point(249, 167);
			this->moveButton2->Name = L"moveButton2";
			this->moveButton2->Size = System::Drawing::Size(94, 44);
			this->moveButton2->TabIndex = 3;
			this->moveButton2->Text = L"move";
			this->moveButton2->UseVisualStyleBackColor = true;
			this->moveButton2->Click += gcnew System::EventHandler(this, &Form1::_moveButton2_Click);
			// 
			// moveButton3
			// 
			this->moveButton3->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->moveButton3->Location = System::Drawing::Point(411, 167);
			this->moveButton3->Name = L"moveButton3";
			this->moveButton3->Size = System::Drawing::Size(94, 44);
			this->moveButton3->TabIndex = 4;
			this->moveButton3->Text = L"move";
			this->moveButton3->UseVisualStyleBackColor = true;
			this->moveButton3->Click += gcnew System::EventHandler(this, &Form1::_moveButton3_Click);
			// 
			// moveButton4
			// 
			this->moveButton4->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->moveButton4->Location = System::Drawing::Point(575, 167);
			this->moveButton4->Name = L"moveButton4";
			this->moveButton4->Size = System::Drawing::Size(94, 44);
			this->moveButton4->TabIndex = 5;
			this->moveButton4->Text = L"move";
			this->moveButton4->UseVisualStyleBackColor = true;
			this->moveButton4->Click += gcnew System::EventHandler(this, &Form1::_moveButton4_Click);
			// 
			// moveButton5
			// 
			this->moveButton5->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->moveButton5->Location = System::Drawing::Point(740, 167);
			this->moveButton5->Name = L"moveButton5";
			this->moveButton5->Size = System::Drawing::Size(94, 44);
			this->moveButton5->TabIndex = 6;
			this->moveButton5->Text = L"move";
			this->moveButton5->UseVisualStyleBackColor = true;
			this->moveButton5->Click += gcnew System::EventHandler(this, &Form1::_moveButton5_Click);
			// 
			// moveButton6
			// 
			this->moveButton6->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->moveButton6->Location = System::Drawing::Point(915, 167);
			this->moveButton6->Name = L"moveButton6";
			this->moveButton6->Size = System::Drawing::Size(94, 44);
			this->moveButton6->TabIndex = 7;
			this->moveButton6->Text = L"move";
			this->moveButton6->UseVisualStyleBackColor = true;
			this->moveButton6->Click += gcnew System::EventHandler(this, &Form1::_moveButton6_Click);
			// 
			// moveButton7
			// 
			this->moveButton7->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->moveButton7->Location = System::Drawing::Point(1076, 167);
			this->moveButton7->Name = L"moveButton7";
			this->moveButton7->Size = System::Drawing::Size(94, 44);
			this->moveButton7->TabIndex = 8;
			this->moveButton7->Text = L"move";
			this->moveButton7->UseVisualStyleBackColor = true;
			this->moveButton7->Click += gcnew System::EventHandler(this, &Form1::_moveButton7_Click);
			// 
			// openButton
			// 
			this->openButton->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->openButton->Location = System::Drawing::Point(1002, 35);
			this->openButton->Name = L"openButton";
			this->openButton->Size = System::Drawing::Size(98, 54);
			this->openButton->TabIndex = 9;
			this->openButton->Text = L"open";
			this->openButton->UseVisualStyleBackColor = true;
			this->openButton->Click += gcnew System::EventHandler(this, &Form1::_openButton_Click);
			// 
			// moveButton
			// 
			this->moveButton->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->moveButton->Location = System::Drawing::Point(1028, 95);
			this->moveButton->Name = L"moveButton";
			this->moveButton->Size = System::Drawing::Size(159, 54);
			this->moveButton->TabIndex = 10;
			this->moveButton->Text = L"move";
			this->moveButton->UseVisualStyleBackColor = true;
			this->moveButton->Click += gcnew System::EventHandler(this, &Form1::_moveButton_Click);
			// 
			// ShiftButton
			// 
			this->ShiftButton->BackColor = System::Drawing::SystemColors::Control;
			this->ShiftButton->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(128)));
			this->ShiftButton->Location = System::Drawing::Point(1106, 35);
			this->ShiftButton->Name = L"ShiftButton";
			this->ShiftButton->Size = System::Drawing::Size(98, 54);
			this->ShiftButton->TabIndex = 11;
			this->ShiftButton->Text = L"Shift !";
			this->ShiftButton->UseVisualStyleBackColor = false;
			this->ShiftButton->Click += gcnew System::EventHandler(this, &Form1::_shiftButton_Click);
			// 
			// glPanel1
			// 
			this->glPanel1->BackColor = System::Drawing::Color::DarkGreen;
			this->glPanel1->ForeColor = System::Drawing::SystemColors::ControlText;
			this->glPanel1->Location = System::Drawing::Point(32, 12);
			this->glPanel1->Name = L"glPanel1";
			this->glPanel1->Size = System::Drawing::Size(1217, 607);
			this->glPanel1->TabIndex = 0;
			this->glPanel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::OnPaint);
			this->glPanel1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::OnKeyDown);
			this->glPanel1->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::OnKeyUp);
			this->glPanel1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::OnMouseDown);
			this->glPanel1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::OnMouseMove);
			this->glPanel1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::OnMouseUp);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1289, 631);
			this->Controls->Add(this->ShiftButton);
			this->Controls->Add(this->moveButton);
			this->Controls->Add(this->openButton);
			this->Controls->Add(this->moveButton7);
			this->Controls->Add(this->moveButton6);
			this->Controls->Add(this->moveButton5);
			this->Controls->Add(this->moveButton4);
			this->Controls->Add(this->moveButton3);
			this->Controls->Add(this->moveButton2);
			this->Controls->Add(this->moveButton1);
			this->Controls->Add(this->startButton);
			this->Controls->Add(this->glPanel1);
			this->Name = L"Form1";
			this->Text = L"Klondike";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: void Render(int w, int h)
			 {
				 // �`��J�n
				 BeginRender();

				 // �`��͈͂̐ݒ�
				 glViewport(0, 0, w, h);

				 // �N���A�J���[�̐ݒ�
				 glClearColor(0.0, 0.5, 0.0, 1.0);

				 // �ŏ��̓h��Ԃ�
				 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) ;

				 // �f�v�X�e�X�g��L���ɂ���B
				 glEnable(GL_DEPTH_TEST);

				 // �J�����O�̐ݒ�
				 glEnable(GL_CULL_FACE);

				 // �ˉe�s��̐ݒ�
				 glMatrixMode(GL_PROJECTION);
				 glLoadMatrixf(_camera->Projection().Array);
				 glOrtho(-0.5, 0.5, 0.5, 0.5, 10.0, -10.0);

				 // �J�����̐ݒ�
				 glMatrixMode(GL_MODELVIEW);
				 glLoadMatrixf(_camera->MV().Array);
				
				 /*
				 // �����̐ݒ�
				 glEnable(GL_LIGHTING);
				 glEnable(GL_LIGHT0);
				 
				 // �����̈ʒu�ݒ�
				 GLfloat light0pos[] = { 0.0, 0.0, 5.0, 1.0 };
				 glLightfv(GL_LIGHT0, GL_POSITION, light0pos);

				 // �����̐F�ݒ�
				 GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
				 glLightfv(GL_LIGHT0, GL_DIFFUSE, white);

				 // �ގ��̐ݒ�
				 GLfloat green[] = {0.0, 0.5, 0.0, 1.0};
				 glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green);
				 */

				 // �l�p�`��`�悷��B
				 glEnable(GL_TEXTURE_2D);
				 glBegin(GL_QUADS);

				 glColor3f(1.0, 1.0, 1.0);
				 vector<float> texcoord;

				 // Field�ɂ���
				 for (int i = 0; i < 7; ++i) {
					 for (int j = 0; j < field_number[i].size(); ++j) {

						 // �}�b�s���O����e�N�X�`�����W���擾
						 texcoord = ChoiceTexture_field(i, j);

						 glNormal3f(0.0, 0.0, 1.0);

						 glTexCoord2f(texcoord[1], texcoord[0]);
						 glVertex3f(-6.5 + 2.0*i, -0.3 - 0.25*j, 0.05*j);

						 glTexCoord2f(texcoord[3], texcoord[2]);
						 glVertex3f(-5.7 + 2.0*i, -0.3 - 0.25*j, 0.05*j);

						 glTexCoord2f(texcoord[5], texcoord[4]);
						 glVertex3f(-5.7 + 2.0*i, 0.9 - 0.25*j, 0.05*j);

						 glTexCoord2f(texcoord[7], texcoord[6]);
						 glVertex3f(-6.5 + 2.0*i, 0.9 - 0.25*j, 0.05*j);

					 }
				 }


				 // Stack�ɂ���
				 for (int i = 0; i < stack_number.size(); ++i) {

					 // �܂��J�[�h���z�u����Ă��Ȃ��ꍇ�͕`�悵�Ȃ�
					 if (stack_number[i] == 0) {
						 continue;
					 }

					 // �}�b�s���O����e�N�X�`�����W���擾
					 texcoord = ChoiceTexture_stack(i);

					 glNormal3f(0.0, 0.0, 1.0);

					 glTexCoord2f(texcoord[1], texcoord[0]);
					 glVertex3f(3.0 - 0.3*i, 2.2, -0.05*i);

					 glTexCoord2f(texcoord[3], texcoord[2]);
					 glVertex3f(3.8 - 0.3*i, 2.2, -0.05*i);

					 glTexCoord2f(texcoord[5], texcoord[4]);
					 glVertex3f(3.8 - 0.3*i, 3.4, -0.05*i);

					 glTexCoord2f(texcoord[7], texcoord[6]);
					 glVertex3f(3.0 - 0.3*i, 3.4, -0.05*i);

				 }

				 // Suit�ɂ���
				 for (int i = 0; i < 4; ++i) {

					 // �܂��J�[�h���z�u����Ă��Ȃ��ꍇ�͕`�悵�Ȃ�
					 if (suit_number[i] == 0) {
						 continue;
					 }
					 
					 // �}�b�s���O����e�N�X�`�����W���擾
					 texcoord = ChoiceTexture_suit(i);

					 glNormal3f(0.0, 0.0, 1.0);

					 glTexCoord2f(texcoord[1], texcoord[0]);
					 glVertex3f(-3.5 + 1.0*i, 2.2, 0.0);

					 glTexCoord2f(texcoord[3], texcoord[2]);
					 glVertex3f(-2.7 + 1.0*i, 2.2, 0.0);

					 glTexCoord2f(texcoord[5], texcoord[4]);
					 glVertex3f(-2.7 + 1.0*i, 3.4, 0.0);

					 glTexCoord2f(texcoord[7], texcoord[6]);
					 glVertex3f(-3.5 + 1.0*i, 3.4, 0.0);

				 }


				 glEnd();

				 glDisable(GL_TEXTURE_2D);


				 // ���W����`��
//				 DrawAxis();

				 // ���܂������߂��܂Ƃ߂ď���
				 // �i�����glutSwapBuffer�͎g��Ȃ���OK�j
				 glFlush();

				 // �`��I��
				 EndRender();

				 // ��ʂ��X�V
				 Invalidate();

			 }
			 // ���W�n��`��
			 void DrawAxis(void)
			 {				 				 
				 // �ˉe�s��̐ݒ�
				 glMatrixMode(GL_PROJECTION);
				 glLoadMatrixf(_camera->Projection().Array);

				 // �J�����̐ݒ�
				 glMatrixMode(GL_MODELVIEW);
				 glLoadMatrixf(_camera->MV().Array);

				 // ���C�g�𖳌���
				 glDisable(GL_LIGHTING);


				 // ���W����`��
				 glBegin(GL_LINES);
				 glColor3f(1, 0, 0);
				 glVertex3f(0, 0, 0);
				 glVertex3f(1, 0, 0);

				 glColor3f(0, 1, 0);
				 glVertex3f(0, 0, 0);
				 glVertex3f(0, 1, 0);

				 glColor3f(0, 0, 1);
				 glVertex3f(0, 0, 0);
				 glVertex3f(0, 0, 1);
				 glEnd();
			 }

	private: void SaveScreen(String^ path)
			{
				int width = glPanel1->Width;
				int height = glPanel1->Height;

				// �o�b�t�@���m��
				GLubyte* data = (GLubyte *)malloc(width*height*3);

				// GlPanel���J�����g�ɐݒ�
				SetCurrent();

				// �o�b�N�o�b�t�@����摜���������Ɏ��o��
				glReadPixels(0, 0, width, height,
							GL_RGB, GL_UNSIGNED_BYTE, data);

				// �����Bitmap�Ɉڂ��ւ�
				Bitmap^ bmp = gcnew Bitmap(width, height);
				for(int h = 0; h < height; h++){
					for(int w = 0; w < width; w++){
						int r   = data[3*width*(height-h-1)+3*w+0];
						int g = data[3*width*(height-h-1)+3*w+1];
						int b  = data[3*width*(height-h-1)+3*w+2];

						bmp->SetPixel(w, h, Color::FromArgb(r, g, b));
					}
				}

				// �t�@�C���o��
				bmp->Save(path);

				// �������̉��
				free(data);
			}
			 std::string MarshalString ( String ^ s)
			 {
				 using namespace Runtime::InteropServices;
				 const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
				 std::string os  = chars;
				 Marshal::FreeHGlobal(IntPtr((void*)chars));

				 return os;
			 }


	private: void Init( HWND hWnd )
			 {
			 	 // ��ɉ�����Ă����B
			 	 wglMakeCurrent(0, 0);
			 	 
				 _hWnd = HWND(hWnd);
				 _hDC = HDC(GetDC(hWnd));

				 if( 0 != SetupPixelFormat( _hDC ) ) return;/*�s�N�Z���t�H�[�}�b�g�ݒ�*/

				 _hglrc = wglCreateContext(_hDC); /* �����_�����O �R���e�L�X�g�̍쐬 */

			 }

	private: inline void SetCurrent()
			 {
				 wglMakeCurrent( _hDC, _hglrc );
			 }
	private: inline void BeginRender()
			 {
				 wglMakeCurrent( _hDC, _hglrc );
			 }
	private:inline void EndRender()
			{
				SwapBuffers( _hDC );
				wglMakeCurrent( _hDC, 0);
			}

	private: int SetupPixelFormat( HDC hdc )/* �s�N�Z���t�H�[�}�b�g��ݒ肷��*/
			 {
				 {
					 int pixelformat;

					 static PIXELFORMATDESCRIPTOR pfd = {
						 sizeof (PIXELFORMATDESCRIPTOR),	// �\���̂̃T�C�Y
						 1,									// OpenGL �o�[�W����
						 PFD_DRAW_TO_WINDOW |				// �E�B���h�E�X�^�C��
						 PFD_SUPPORT_OPENGL |				// OpenGL ���g��
						 PFD_DOUBLEBUFFER,					// �_�u���o�b�t�@
						 PFD_TYPE_RGBA,						// �s�N�Z���̃J���[�f�[�^
						 32,								// �F�̃r�b�g��
						 0, 0, 0, 0, 0, 0, 0, 0,			// RGBA�J���[�o�b�t�@�̃r�b�g
						 0, 0, 0, 0, 0,						// �A�L�������[�V�����o�b�t�@�̃s�N�Z������̃r�b�g��
						 32,								// �f�v�X�o�b�t�@    �̃s�N�Z������̃r�b�g��
						 0,									// �X�e���V���o�b�t�@�̃s�N�Z������̃r�b�g��
						 0,									// �⏕�o�b�t�@      �̃s�N�Z������̃r�b�g��
						 PFD_MAIN_PLANE,					// ���C���[�^�C�v
						 0,									//
						 0,									//
						 0,									//
						 0									//
					 };

					 if ( 0 == (pixelformat = ChoosePixelFormat(hdc, &pfd)) )
					 {
						 return 1;
					 }

					 if ( FALSE == SetPixelFormat(hdc, pixelformat, &pfd) )
					 {
						 return 2;
					 }

					 return 0;
				 }
			 }
	private: System::Void OnPaint(void)
			 {
				 OnPaint(nullptr, nullptr);
			 }
	private: System::Void OnPaint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 Render(glPanel1->Width, glPanel1->Height);
			 }
	private: System::Void OnMouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 _camera->OnMouseDown(e->X, e->Y);
				 OnPaint();
			 }
	private: System::Void OnMouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				_camera->OnMouseUp(e->X, e->Y);
				OnPaint();
			 }
	private: System::Void OnMouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				_camera->OnMouseMove(e->X, e->Y, 
				 System::Windows::Forms::MouseButtons::Left == e->Button,
				 System::Windows::Forms::MouseButtons::Middle == e->Button,
				 System::Windows::Forms::MouseButtons::Right == e->Button);
				 OnPaint();
			 }
	private: System::Void OnKeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 _camera->OnKeyDown(e->Alt, e->Shift, e->Control);
				 OnPaint();
			 }
	private: System::Void OnKeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 _camera->OnKeyDown(e->Alt, e->Shift, e->Control);
				 OnPaint();
			 }


// Field�̃R�[���o�b�N�֐�
private: System::Void _startButton_Click(System::Object^  sender, System::EventArgs^  e) {
	InitTexture();
	klondike.initialize();
	getFieldStatus();
	getSuitStatus();
	getStackStatus();
	OnPaint();
}
private: System::Void _moveButton1_Click(System::Object^  sender, System::EventArgs^  e) {
	klondike.move_field(0);
	getFieldStatus();
	getSuitStatus();
	OnPaint();
}
private: System::Void _moveButton2_Click(System::Object^  sender, System::EventArgs^  e) {
	klondike.move_field(1);
	getFieldStatus();
	getSuitStatus();
	OnPaint();
}
private: System::Void _moveButton3_Click(System::Object^  sender, System::EventArgs^  e) {
	klondike.move_field(2);
	getFieldStatus();
	getSuitStatus();
	OnPaint();
}
private: System::Void _moveButton4_Click(System::Object^  sender, System::EventArgs^  e) {
	klondike.move_field(3);
	getFieldStatus();
	getSuitStatus();
	OnPaint();
}
private: System::Void _moveButton5_Click(System::Object^  sender, System::EventArgs^  e) {
	klondike.move_field(4);
	getFieldStatus();
	getSuitStatus();
	OnPaint();
}
private: System::Void _moveButton6_Click(System::Object^  sender, System::EventArgs^  e) {
	klondike.move_field(5);
	getFieldStatus();
	getSuitStatus();
	OnPaint();
}
private: System::Void _moveButton7_Click(System::Object^  sender, System::EventArgs^  e) {
	klondike.move_field(6);
	getFieldStatus();
	getSuitStatus();
	OnPaint();
}

// Stack�̃R�[���o�b�N�֐�
private: System::Void _moveButton_Click(System::Object^  sender, System::EventArgs^  e) {
	if (stack_number.size() != 0) {
		klondike.move_stack();
		getStackStatus();
		getFieldStatus();
		getSuitStatus();
		OnPaint();
	}
}
private: System::Void _openButton_Click(System::Object^  sender, System::EventArgs^  e) {
	if (stack_number.size() != 0) {
		klondike.open_stack();
		getStackStatus();
		OnPaint();
	}
}
private: System::Void _shiftButton_Click(System::Object^  sender, System::EventArgs^  e) {
	if (stack_number.size() != 0) {
		klondike.shift_stack();
		getStackStatus();
		OnPaint();
	}
}

		 /*-------------�e�N�X�`���}�b�s���O�̂��߂̊֐�----------------------*/

		 /* �e�N�X�`���̓ǂݍ��� */
		 void InitTexture() {

			 SetCurrent();

			 Bitmap^ bmp = gcnew Bitmap("trump.gif");

			 int width = bmp->Width;
			 int height = bmp->Height;

			 GLubyte* tex = new GLubyte[width * height * 3];

			 for (int h = 0; h < height; ++h) {
				 for (int w = 0; w < width; ++w) {
					 Color col = bmp->GetPixel(w, h);

					 tex[3 * width*h + 3 * w + 0] = col.R;
					 tex[3 * width*h + 3 * w + 1] = col.G;
					 tex[3 * width*h + 3 * w + 2] = col.B;

				 }
			 }
			 glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			 glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex);

			 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			 // �~�b�v�}�b�v
			 gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tex);

			 delete[] tex;

		 }

		 /* �}�b�s���O����̈��I�� */
		 vector<float> ChoiceTexture_field(int i, int j) {

			 vector<float> texcoord;
			 texcoord.clear();
			 int col, row;

			 // �g�����v�����������Ă���ꍇ
			 if (field_direction[i][j] == false) {
				 texcoord.push_back(1.0);
				 texcoord.push_back(7.0 / 8.0);

				 texcoord.push_back(1.0);
				 texcoord.push_back(1.0);

				 texcoord.push_back(6.0 / 7.0);
				 texcoord.push_back(1.0);

				 texcoord.push_back(6.0 / 7.0);
				 texcoord.push_back(7.0 / 8.0);

			 }

			 // �g�����v���\�������Ă���ꍇ
			 else if (field_direction[i][j] == true) {

				 row = field_number[i][j] - 1;

				 if (row <= 6) {
					 if (field_symbol[i][j] == "H") {
						 col = 0;
					 }
					 else if (field_symbol[i][j] == "S") {
						 col = 1;
					 }
					 else if (field_symbol[i][j] == "D") {
						 col = 2;
					 }
					 else if (field_symbol[i][j] == "C") {
						 col = 3;
					 }

				 }
				 else if (row > 6) {

					 if (field_symbol[i][j] == "H") {
						 col = 4;
					 }
					 else if (field_symbol[i][j] == "S") {
						 col = 5;
					 }
					 else if (field_symbol[i][j] == "D") {
						 col = 6;
					 }
					 else if (field_symbol[i][j] == "C") {
						 col = 7;
					 }

				 }

				 // �e�N�X�`�����W�̊��蓖��
				 texcoord.push_back(1.0 / 7.0*(row + 1));
				 texcoord.push_back(1.0 / 8.0*col);
				 texcoord.push_back(1.0 / 7.0*(row + 1));
				 texcoord.push_back(1.0 / 8.0*(col + 1));
				 texcoord.push_back(1.0 / 7.0*row);
				 texcoord.push_back(1.0 / 8.0*(col + 1));
				 texcoord.push_back(1.0 / 7.0*row);
				 texcoord.push_back(1.0 / 8.0*col);

			 }

			 return texcoord;
		 }
		 vector<float> ChoiceTexture_stack(int i) {

			 vector<float> texcoord;
			 texcoord.clear();
			 int col, row;
			 
			 row = stack_number[i] - 1;

			 if (row <= 6) {
				 if (stack_symbol[i] == "H") {
					 col = 0;
				 }
				 else if (stack_symbol[i] == "S") {
					 col = 1;
				 }
				 else if (stack_symbol[i] == "D") {
					 col = 2;
				 }
				 else if (stack_symbol[i] == "C") {
					 col = 3;
				 }

			 }
			 else if (row > 6) {

				 if (stack_symbol[i] == "H") {
					 col = 4;
				 }
				 else if (stack_symbol[i] == "S") {
					 col = 5;
				 }
				 else if (stack_symbol[i] == "D") {
					 col = 6;
				 }
				 else if (stack_symbol[i] == "C") {
					 col = 7;
				 }

			 }

			 // �e�N�X�`�����W�̊��蓖��
			 texcoord.push_back(1.0 / 7.0*(row + 1));
			 texcoord.push_back(1.0 / 8.0*col);
			 texcoord.push_back(1.0 / 7.0*(row + 1));
			 texcoord.push_back(1.0 / 8.0*(col + 1));
			 texcoord.push_back(1.0 / 7.0*row);
			 texcoord.push_back(1.0 / 8.0*(col + 1));
			 texcoord.push_back(1.0 / 7.0*row);
			 texcoord.push_back(1.0 / 8.0*col);


		 return texcoord;
		 }
		 vector<float> ChoiceTexture_suit(int i) {

			 vector<float> texcoord;
			 texcoord.clear();
			 int col, row;

			 row = suit_number[i] - 1;

			 if (row <= 6) {
				 if (i == 1) {
					 col = 0;
				 }
				 else if (i == 0) {
					 col = 1;
				 }
				 else if (i == 3) {
					 col = 2;
				 }
				 else if (i == 2) {
					 col = 3;
				 }

			 }
			 else if (row > 6) {

				 if (i == 1) {
					 col = 4;
				 }
				 else if (i == 0) {
					 col = 5;
				 }
				 else if (i == 3) {
					 col = 6;
				 }
				 else if (i == 2) {
					 col = 7;
				 }

			 }

			 // �e�N�X�`�����W�̊��蓖��
			 texcoord.push_back(1.0 / 7.0*(row + 1));
			 texcoord.push_back(1.0 / 8.0*col);
			 texcoord.push_back(1.0 / 7.0*(row + 1));
			 texcoord.push_back(1.0 / 8.0*(col + 1));
			 texcoord.push_back(1.0 / 7.0*row);
			 texcoord.push_back(1.0 / 8.0*(col + 1));
			 texcoord.push_back(1.0 / 7.0*row);
			 texcoord.push_back(1.0 / 8.0*col);


			 return texcoord;
		 }

		 /* Field�̏�Ԃ��擾 */
		 void getFieldStatus() {
			 for (int i = 0; i < 7; ++i) {
				 field_number[i] = klondike.getField_number(i);
				 field_symbol[i] = klondike.getField_symbol(i);
				 field_direction[i] = klondike.getField_direction(i);
			 }
		 }

		 /* Stack�̏�Ԃ��擾 */
		 void getStackStatus() {
			 stack_number = klondike.getStack_number();
			 stack_symbol = klondike.getStack_symbol();
		 }
		 
		 /* Suit�̏�Ԃ��擾 */
		 void getSuitStatus(){
			 suit_number = klondike.getSuit_number();
		 }

		 /*---------------------------------------------------------------------*/


};
}

