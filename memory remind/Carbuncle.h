#pragma once
#include "Base_Player.h"

class Carbuncle :
	public Base_Player
{
public:
	Carbuncle(VECTOR2 drawOffset);
	Carbuncle();
	~Carbuncle();

	void ColTrap(CharacterStatusData *charData);
	void ColTrap2(CharacterStatusData *charData);
	void SetMove(weekListObj objList, const Game_ctr &controller);
	bool InitAnim(void);

private:
	int cDamage;	// カーバンクル用のダメージ変数
	int cDamage2;	// カーバンクル用のダメージ変数
};

