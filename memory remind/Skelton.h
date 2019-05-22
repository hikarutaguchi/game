#pragma once
#include "Player.h"
class Skelton :
	public Player
{
public:
	Skelton(VECTOR2 setupPos, VECTOR2 drawOffset);
	Skelton();
	~Skelton();

	void ColTrap(CharacterStatusData *charData);
	void SetMove(weekListObj objList, const Game_ctr &controller);
	bool InitAnim(void);
};

