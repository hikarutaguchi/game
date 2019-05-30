#pragma once
#include "Base_Player.h"

class Slime :
	public Base_Player
{
public:
	Slime(VECTOR2 drawOffset);
	Slime();
	~Slime();

	void ColTrap(CharacterStatusData *charData);
	void ColTrap2(CharacterStatusData *charData);
	void SetMove(weekListObj objList, const Game_ctr &controller);
	bool InitAnim(void);

private:
	int sDamage; // �X���C���p�̃_���[�W�ϐ�
	int sDamage2;
};

