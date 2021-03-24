#pragma once

#include <iostream>
#include <time.h>
#include <vector>

using namespace std;


class Klondike{

private:
	
	/* ��D */
	vector<int> field_number[7]; // ����
	vector<string> field_symbol[7]; // �}�[�N
	vector<bool> field_direction[7]; // ����(�\or��)
	vector<bool> field_color[7]; // �F(��or��)

	/* �R�D */
	vector<int> stack_number; // ����
	vector<string> stack_symbol; // �}�[�N

	/* �g�D */
	int suit_number[4]; // ����(S,H,C,D�̏�)
	string suit_symbol[4] = { "S","H","C","D" }; // �}�[�N(S,H,C,D�̏�)


	/* shift���������񐔂𐔂��� */
	int ite;


public:
	Klondike();

	void initialize();
	void move_field(int col);
	void open_stack();
	void move_stack();
	void shift_stack();

	vector<int> getField_number(int col);
	vector<string> getField_symbol(int col);
	vector<bool> getField_direction(int col);
	vector<int> getStack_number();
	vector<string> getStack_symbol();
	vector<int> getSuit_number();

};