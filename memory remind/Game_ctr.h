#pragma once
#include <array>

using KEY_ARRAY = std::array<char, 256>;

enum KEY_TYPE {
	KEY_TYPE_NOW,
	KEY_TYPE_OLD,
	KEY_TYPE_MAX
};


class Game_ctr
{
public:
	Game_ctr();
	~Game_ctr();
	bool Updata(void);								// 情報更新
	const KEY_ARRAY &GetCtr(KEY_TYPE type) const;	// ｷｰ取得
	const int &Get_CTL(void)const;
private:
	int Pad[4];
	KEY_ARRAY data;									// ｷｰ入力ﾃﾞｰﾀ
	KEY_ARRAY dataOld;								// 前ｷｰ入力ﾃﾞｰﾀ
};
