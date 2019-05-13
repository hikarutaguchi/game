#pragma once
#include "Player.h"

class Carbuncle :
	public Player
{
public:
	Carbuncle();
	~Carbuncle();

	void SetMove(weekListObj objList, const Game_ctr &controller);
	bool InitAnim(void);
};

