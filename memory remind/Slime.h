#pragma once
#include "Player.h"
class Slime :
	public Player
{
public:
	Slime();
	~Slime();

	void SetMove(weekListObj objList, const Game_ctr &controller);
	bool InitAnim(void);
};

