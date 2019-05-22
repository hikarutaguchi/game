#pragma once
#include "Player.h"

class Carbuncle :
	public Player
{
public:
	Carbuncle(VECTOR2 setupPos, VECTOR2 drawOffset);
	Carbuncle();
	~Carbuncle();

	void ColTrap(CharacterStatusData *charData);
	void SetMove(weekListObj objList, const Game_ctr &controller);
	bool InitAnim(void);
};

