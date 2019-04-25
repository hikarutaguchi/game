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
	bool Updata(void);								// î•ñXV
	const KEY_ARRAY &GetCtr(KEY_TYPE type) const;	// ·°æ“¾
private:
	KEY_ARRAY data;									// ·°“ü—ÍÃŞ°À
	KEY_ARRAY dataOld;								// ‘O·°“ü—ÍÃŞ°À
};
