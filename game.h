#pragma once

#include <iostream>
#include <time.h>
#include <vector>

using namespace std;


class Klondike{

private:
	
	/* 場札 */
	vector<int> field_number[7]; // 数字
	vector<string> field_symbol[7]; // マーク
	vector<bool> field_direction[7]; // 向き(表or裏)
	vector<bool> field_color[7]; // 色(黒or赤)

	/* 山札 */
	vector<int> stack_number; // 数字
	vector<string> stack_symbol; // マーク

	/* 組札 */
	int suit_number[4]; // 数字(S,H,C,Dの順)
	string suit_symbol[4] = { "S","H","C","D" }; // マーク(S,H,C,Dの順)


	/* shiftを押した回数を数える */
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