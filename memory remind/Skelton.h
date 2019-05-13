#pragma once
#include "Player.h"
class Skelton :
	public Player
{
public:
	Skelton();
	~Skelton();

	void SetMove(weekListObj objList, const Game_ctr &controller);
	bool InitAnim(void);
};

