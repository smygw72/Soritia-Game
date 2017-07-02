#include "stdafx.h"

/* fieldからsuitに移動できるかどうか */
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

/* field内で別の列に移動できるかどうか */
bool move_field2field(int firstFront_number, bool firstFront_color, int col, vector<int> *field_number, vector<bool> *field_color, int& dest)
{
	for (int i = 0; i < 7; ++i) {

		if (i != col) { // 同じ列ではない
			if (field_number[i].size() != 0) {
				// 数字が連続しているかつ色が異なる場合
				if (field_number[i].back() == (firstFront_number + 1)) {
					if (firstFront_color != field_color[i].back()) {

						dest = i;
						return true;
					}
				}
			}

			// キングが置ける場合
			if (field_number[i].size() == 0 && firstFront_number == 13) {
				
				dest = i;
				return true;
		
			}
		}
	}
	return false;
}

/* stackからsuitに移動できるかどうか */
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

/* stackからfieldに移動できるかどうか */
bool move_stack2filed(int stack_number,string stack_symbol,bool color, vector<int> *field_number, vector<bool> *field_color, int& dest) {

	for (int i = 0; i < 7; ++i) {

			if(field_number[i].size() != 0) {

				// 数字が連続しているかつ色が異なる場合
				if (field_number[i].back() == (stack_number + 1)) {
					if (color != field_color[i].back()) {

						dest = i;
						return true;
					}
				}
			}

			// キングが置ける場合
			if (field_number[i].size() == 0 && stack_number == 13) {

				dest = i;
				return true;

			}
	}
	return false;

}

/*--------------------------メンバ関数-----------------------------*/

/* コンストラクタ */
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

/* メンバ変数の初期化 */
void Klondike::initialize()
{
	/* 再初期化 */
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


	// 4種類の柄を持つトランプに数字を格納
	vector<int> trump[4];
	
	// 初期化
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 13; ++j) {
			trump[i].push_back(j + 1);
		}
	}

	// 擬似乱数の発生系列を変更
	srand((unsigned int)time(NULL));


	/* fieldの設定 */

	for (int i = 0; i < 7; ++i) { // field_number[i]およびfield_symbol[i]について
		
		for (int j = 0; j < i + 1; ++j) { // i+1回vectorの要素を追加する
		
			int field_size = 0;
			
			do {

				int random_symbol = rand() % 4; // ランダムに柄を選ぶ
				field_size = trump[random_symbol].size(); // 選んだ柄のサイズ

				if (field_size != 0) {

					int random_number = rand() % field_size; // 選んだ柄の何番目の数字を取ってくるか

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


	/* Stackの設定 */

	for (int i = 0; i < 24; ++i) {
		
		int trump_size = 0;

		do {

			int random_symbol = rand() % 4; // ランダムに柄を選ぶ
			trump_size = trump[random_symbol].size(); // 選んだベクトルのサイズ
		

			if (trump_size != 0) {
				int random_number = rand() % trump_size; // 選んだ柄の何番目の数字を取ってくるか

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


	/* fieldにあるトランプの向き(表or裏)の初期化 */

	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < i; ++j) {
			field_direction[i].push_back(0);
		}
		// 最後の要素のみ表
		field_direction[i].push_back(1);
	}


	/* fieldにあるトランプの色(黒or赤)の初期化 */

	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < field_symbol[i].size(); ++j) {
	
			if (field_symbol[i][j] == "S" || field_symbol[i][j] == "C") {
				field_color[i].push_back(0); // スペードかクローバーだったら黒色
			}
			else if (field_symbol[i][j] == "H" || field_symbol[i][j] == "D") {
				field_color[i].push_back(1); // ハートかダイヤだったら赤色
			}

		}
	}


#if 1
	for (int i = 0; i < 7; ++i) {
		cout << "場札" << i + 1 << endl;
		for (int j = 0; j < field_number[i].size(); ++j) {
			cout << field_number[i][j] << endl;
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < 24; ++i) {
		cout << "山札" << endl;
		cout << stack_number[i] << endl;
	}
#endif
}

void Klondike::move_field(int col)	// num:どの列をクリックしたか
{
	/* 変数宣言 */
	
	// ベクトルのサイズ
	int size = field_number[col].size();

	if (size != 0) {

		// 表になっている初めのカードの数と柄と色の変数宣言
		int firstFront_number;
		string firstFront_symbol;
		bool firstFront_color;

		// 表になっている終わりのカードの数と柄の変数宣言
		int endFront_number;
		string endFront_symbol;

		// 表になっているカードの数
		int FrontNumber;


		/* 代入 */

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


		/* カードの移動 */

		// カードの移動先の場所の変数宣言
		int dest;

		// fieldからsuitに移動する場合
		if (move_field2suit(endFront_number, endFront_symbol, suit_symbol, suit_number, dest) == true) {

			// 追加
			suit_number[dest] = endFront_number;

			// 削除
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
		// field内で移動する場合
		else if (move_field2field(firstFront_number, firstFront_color, col, field_number, field_color, dest) == true) {

			// 追加
			for (int i = 0; i < FrontNumber; ++i) {
				field_number[dest].push_back(field_number[col][size - FrontNumber + i]);
				field_symbol[dest].push_back(field_symbol[col][size - FrontNumber + i]);
				field_direction[dest].push_back(field_direction[col][size - FrontNumber + i]);
				field_color[dest].push_back(field_color[col][size - FrontNumber + i]);
			}

			// 削除
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

	// 3回まで
	if (ite < 4) {
		stack_number.push_back(stack_number.front());
		stack_number.erase(stack_number.begin());

		stack_symbol.push_back(stack_symbol.front());
		stack_symbol.erase(stack_symbol.begin());
	}
}

void Klondike::move_stack() {

	// カードの移動先の場所の変数宣言
	int dest;

	bool color;
	if (stack_symbol[0] == "S" || stack_symbol[0] == "C") {
		color = false;
	}
	else {
		color = true;
	}


	if (move_stack2suit(stack_number[0], stack_symbol[0], suit_symbol, suit_number, dest)) {

		// 追加
		suit_number[dest] = stack_number[0];

		// 削除
		stack_number.erase(stack_number.begin());
		stack_symbol.erase(stack_symbol.begin());


	}else if (move_stack2filed(stack_number[0], stack_symbol[0], color, field_number, field_color, dest) == true) {
		
		// 追加
		field_number[dest].push_back(stack_number[0]);
		field_symbol[dest].push_back(stack_symbol[0]);
		field_direction[dest].push_back(1);
		field_color[dest].push_back(color);

		// 削除
		stack_number.erase(stack_number.begin());
		stack_symbol.erase(stack_symbol.begin());

	}

}

/*----------------------get関数----------------------*/

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