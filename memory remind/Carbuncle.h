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
	int cDamage;	// �J�[�o���N���p�̃_���[�W�ϐ�
	int cDamage2;	// �J�[�o���N���p�̃_���[�W�ϐ�
};

