#pragma once
#include "Player.h"

class Slime :
	public Player
{
public:
	Slime(VECTOR2 drawOffset);
	Slime();
	~Slime();

	void ColTrap(CharacterStatusData *charData);
	void SetMove(weekListObj objList, const Game_ctr &controller);
	bool InitAnim(void);
};

