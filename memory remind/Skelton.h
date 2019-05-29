#pragma once
#include "Base_Player.h"

class Skelton :
	public Base_Player
{
public:
	Skelton(VECTOR2 drawOffset);
	Skelton();
	~Skelton();

	void ColTrap(CharacterStatusData *charData);
	void SetMove(weekListObj objList, const Game_ctr &controller);
	bool InitAnim(void);

private:
	int nDamage;	// スケルトン用のダメージ変数
};

