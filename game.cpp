#include "stdafx.h"

/* field����suit�Ɉړ��ł��邩�ǂ��� */
bool move_field2suit(int endFront_number, string endFront_symbol, string *suit_symbol,int *suit_number,int& dest)
{
	for (int i = 0; i < 4; ++i) {
		if (suit_symbol[i] == endFront_symbol) {
			if ((suit_number[i] + 1) == endFront_number) {

				dest = i;
				return true;

			}
		}
	}
	return false;
}

/* field���ŕʂ̗�Ɉړ��ł��邩�ǂ��� */
bool move_field2field(int firstFront_number, bool firstFront_color, int col, vector<int> *field_number, vector<bool> *field_color, int& dest)
{
	for (int i = 0; i < 7; ++i) {

		if (i != col) { // ������ł͂Ȃ�
			if (field_number[i].size() != 0) {
				// �������A�����Ă��邩�F���قȂ�ꍇ
				if (field_number[i].back() == (firstFront_number + 1)) {
					if (firstFront_color != field_color[i].back()) {

						dest = i;
						return true;
					}
				}
			}

			// �L���O���u����ꍇ
			if (field_number[i].size() == 0 && firstFront_number == 13) {
				
				dest = i;
				return true;
		
			}
		}
	}
	return false;
}

/* stack����suit�Ɉړ��ł��邩�ǂ��� */
bool move_stack2suit(int stack_number, string stack_symbol, string *suit_symbol, int *suit_number, int& dest) {
	
	for (int i = 0; i < 4; ++i) {
		if (suit_symbol[i] == stack_symbol) {
			if ((suit_number[i] + 1) == stack_number) {

				dest = i;
				return true;

			}
		}
	}
	return false;

}

/* stack����field�Ɉړ��ł��邩�ǂ��� */
bool move_stack2filed(int stack_number,string stack_symbol,bool color, vector<int> *field_number, vector<bool> *field_color, int& dest) {

	for (int i = 0; i < 7; ++i) {

			if(field_number[i].size() != 0) {

				// �������A�����Ă��邩�F���قȂ�ꍇ
				if (field_number[i].back() == (stack_number + 1)) {
					if (color != field_color[i].back()) {

						dest = i;
						return true;
					}
				}
			}

			// �L���O���u����ꍇ
			if (field_number[i].size() == 0 && stack_number == 13) {

				dest = i;
				return true;

			}
	}
	return false;

}

/*--------------------------�����o�֐�-----------------------------*/

/* �R���X�g���N�^ */
Klondike::Klondike()
{

	for (int i = 0; i < 7; ++i) {
		field_number[i].clear();
		field_symbol[i].clear();
		field_direction[i].clear();
		field_color[i].clear();
	}

	stack_number.clear();
	stack_symbol.clear();
	
	for (int i = 0; i < 4; ++i) {
		suit_number[i] = 0;
	}

	ite = 0;
}

/* �����o�ϐ��̏����� */
void Klondike::initialize()
{
	/* �ď����� */
	for (int i = 0; i < 7; ++i) {
		field_number[i].clear();
		field_symbol[i].clear();
		field_direction[i].clear();
		field_color[i].clear();
	}

	stack_number.clear();
	stack_symbol.clear();

	for (int i = 0; i < 4; ++i) {
		suit_number[i] = 0;
	}
	ite = 0;


	// 4��ނ̕������g�����v�ɐ������i�[
	vector<int> trump[4];
	
	// ������
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 13; ++j) {
			trump[i].push_back(j + 1);
		}
	}

	// �[�������̔����n���ύX
	srand((unsigned int)time(NULL));


	/* field�̐ݒ� */

	for (int i = 0; i < 7; ++i) { // field_number[i]�����field_symbol[i]�ɂ���
		
		for (int j = 0; j < i + 1; ++j) { // i+1��vector�̗v�f��ǉ�����
		
			int field_size = 0;
			
			do {

				int random_symbol = rand() % 4; // �����_���ɕ���I��
				field_size = trump[random_symbol].size(); // �I�񂾕��̃T�C�Y

				if (field_size != 0) {

					int random_number = rand() % field_size; // �I�񂾕��̉��Ԗڂ̐���������Ă��邩

					field_number[i].push_back(trump[random_symbol][random_number]);
					trump[random_symbol].erase(trump[random_symbol].begin() + random_number);

					if (random_symbol == 0) {
						field_symbol[i].push_back("S");
					}
					else if (random_symbol == 1) {
						field_symbol[i].push_back("H");
					}
					else if (random_symbol == 2) {
						field_symbol[i].push_back("C");
					}
					else if (random_symbol == 3) {
						field_symbol[i].push_back("D");
					}
					else {
						cout << "Error" << endl;
					}
				}

			} while (field_size == 0);
		}
	}


	/* Stack�̐ݒ� */

	for (int i = 0; i < 24; ++i) {
		
		int trump_size = 0;

		do {

			int random_symbol = rand() % 4; // �����_���ɕ���I��
			trump_size = trump[random_symbol].size(); // �I�񂾃x�N�g���̃T�C�Y
		

			if (trump_size != 0) {
				int random_number = rand() % trump_size; // �I�񂾕��̉��Ԗڂ̐���������Ă��邩

				stack_number.push_back(trump[random_symbol][random_number]);
				trump[random_symbol].erase(trump[random_symbol].begin() + random_number);

				if (random_symbol == 0) {
					stack_symbol.push_back("S");
				}
				else if (random_symbol == 1) {
					stack_symbol.push_back("H");
				}
				else if (random_symbol == 2) {
					stack_symbol.push_back("C");
				}
				else if (random_symbol == 3) {
					stack_symbol.push_back("D");
				}
				else {
					cout << "Error" << endl;
				}
			}
		} while (trump_size == 0);
	}


	/* field�ɂ���g�����v�̌���(�\or��)�̏����� */

	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < i; ++j) {
			field_direction[i].push_back(0);
		}
		// �Ō�̗v�f�̂ݕ\
		field_direction[i].push_back(1);
	}


	/* field�ɂ���g�����v�̐F(��or��)�̏����� */

	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < field_symbol[i].size(); ++j) {
	
			if (field_symbol[i][j] == "S" || field_symbol[i][j] == "C") {
				field_color[i].push_back(0); // �X�y�[�h���N���[�o�[�������獕�F
			}
			else if (field_symbol[i][j] == "H" || field_symbol[i][j] == "D") {
				field_color[i].push_back(1); // �n�[�g���_�C����������ԐF
			}

		}
	}


#if 1
	for (int i = 0; i < 7; ++i) {
		cout << "��D" << i + 1 << endl;
		for (int j = 0; j < field_number[i].size(); ++j) {
			cout << field_number[i][j] << endl;
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 24; ++i) {
		cout << "�R�D" << endl;
		cout << stack_number[i] << endl;
	}
#endif
}

void Klondike::move_field(int col)	// num:�ǂ̗���N���b�N������
{
	/* �ϐ��錾 */
	
	// �x�N�g���̃T�C�Y
	int size = field_number[col].size();

	if (size != 0) {

		// �\�ɂȂ��Ă��鏉�߂̃J�[�h�̐��ƕ��ƐF�̕ϐ��錾
		int firstFront_number;
		string firstFront_symbol;
		bool firstFront_color;

		// �\�ɂȂ��Ă���I���̃J�[�h�̐��ƕ��̕ϐ��錾
		int endFront_number;
		string endFront_symbol;

		// �\�ɂȂ��Ă���J�[�h�̐�
		int FrontNumber;


		/* ��� */

		for (int i = 0; i < field_direction[col].size(); ++i) {

			if (field_direction[col][i] == true) {

				firstFront_number = field_number[col][i];
				firstFront_symbol = field_symbol[col][i];
				firstFront_color = field_color[col][i];
				FrontNumber = field_direction[col].size() - i;
				break;
			}
		}

		endFront_number = field_number[col].back();
		endFront_symbol = field_symbol[col].back();


		/* �J�[�h�̈ړ� */

		// �J�[�h�̈ړ���̏ꏊ�̕ϐ��錾
		int dest;

		// field����suit�Ɉړ�����ꍇ
		if (move_field2suit(endFront_number, endFront_symbol, suit_symbol, suit_number, dest) == true) {

			// �ǉ�
			suit_number[dest] = endFront_number;

			// �폜
			field_number[col].pop_back();
			field_symbol[col].pop_back();
			field_direction[col].pop_back();
			field_color[col].pop_back();
		

			if (field_direction[col].size() != 0) {
				if (field_direction[col].back() == false) {
					field_direction[col].back() = true;
				}
			}

		}
		// field���ňړ�����ꍇ
		else if (move_field2field(firstFront_number, firstFront_color, col, field_number, field_color, dest) == true) {

			// �ǉ�
			for (int i = 0; i < FrontNumber; ++i) {
				field_number[dest].push_back(field_number[col][size - FrontNumber + i]);
				field_symbol[dest].push_back(field_symbol[col][size - FrontNumber + i]);
				field_direction[dest].push_back(field_direction[col][size - FrontNumber + i]);
				field_color[dest].push_back(field_color[col][size - FrontNumber + i]);
			}

			// �폜
			for (int i = 0; i < FrontNumber; ++i) {

				field_number[col].pop_back();
				field_symbol[col].pop_back();
				field_direction[col].pop_back();
				field_color[col].pop_back();

			}

			if (field_direction[col].size() != 0) {
				if (field_direction[col].back() == false) {
					field_direction[col].back() = true;
				}
			}

		}

	}
}

void Klondike::open_stack() {
	for (int i = 0; i < 3; ++i) {
		
		int num = stack_number.front();
		stack_number.erase(stack_number.begin());
		stack_number.push_back(num);

		string str = stack_symbol.front();
		stack_symbol.erase(stack_symbol.begin());
		stack_symbol.push_back(str);

	}
}

void Klondike::shift_stack() {
	ite++;

	// 3��܂�
	if (ite < 4) {
		stack_number.push_back(stack_number.front());
		stack_number.erase(stack_number.begin());

		stack_symbol.push_back(stack_symbol.front());
		stack_symbol.erase(stack_symbol.begin());
	}
}

void Klondike::move_stack() {

	// �J�[�h�̈ړ���̏ꏊ�̕ϐ��錾
	int dest;

	bool color;
	if (stack_symbol[0] == "S" || stack_symbol[0] == "C") {
		color = false;
	}
	else {
		color = true;
	}


	if (move_stack2suit(stack_number[0], stack_symbol[0], suit_symbol, suit_number, dest)) {

		// �ǉ�
		suit_number[dest] = stack_number[0];

		// �폜
		stack_number.erase(stack_number.begin());
		stack_symbol.erase(stack_symbol.begin());


	}else if (move_stack2filed(stack_number[0], stack_symbol[0], color, field_number, field_color, dest) == true) {
		
		// �ǉ�
		field_number[dest].push_back(stack_number[0]);
		field_symbol[dest].push_back(stack_symbol[0]);
		field_direction[dest].push_back(1);
		field_color[dest].push_back(color);

		// �폜
		stack_number.erase(stack_number.begin());
		stack_symbol.erase(stack_symbol.begin());

	}

}

/*----------------------get�֐�----------------------*/

// Field
vector<int> Klondike::getField_number(int col)
{
	return vector<int>(field_number[col]);
}
vector<string> Klondike::getField_symbol(int col)
{
	return vector<string>(field_symbol[col]);
}
vector<bool> Klondike::getField_direction(int col)
{
	return vector<bool>(field_direction[col]);
}

// Stack
vector<int> Klondike::getStack_number()
{
	vector<int> stack_number_dash;
	if (stack_number.size() > 3) {
		for (int i = 0; i < 3; ++i) {
			stack_number_dash.push_back(stack_number[i]);
		}
	}
	else {
		for (int i = 0; i < stack_number.size();++i){
			stack_number_dash.push_back(stack_number[i]);
		}
	}

	return vector<int>(stack_number_dash);
}
vector<string> Klondike::getStack_symbol()
{
	vector<string> stack_symbol_dash;

	if (stack_symbol.size() > 3) {
		for (int i = 0; i < 3; ++i) {
			stack_symbol_dash.push_back(stack_symbol[i]);
		}
	}
	else {
		for (int i = 0; i < stack_number.size(); ++i) {
			stack_symbol_dash.push_back(stack_symbol[i]);
		}
		
	}
	
	return	vector<string>(stack_symbol_dash);
}

// Suit
vector<int> Klondike::getSuit_number()
{
	vector<int> suit_number_dash;
	
	for (int i = 0; i < 4; ++i) {
		suit_number_dash.push_back(suit_number[i]);
	}

	return vector<int>(suit_number_dash);
}


/*---------------------------------------------------*/