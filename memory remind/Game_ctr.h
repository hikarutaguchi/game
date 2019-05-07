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
	bool Updata(void);								// ���X�V
	const KEY_ARRAY &GetCtr(KEY_TYPE type) const;	// ���擾
	const int &Get_CTL(KEY_TYPE)const;
private:
	int Pad[4];
	KEY_ARRAY data;									// �������ް�
	KEY_ARRAY dataOld;								// �O�������ް�
};
