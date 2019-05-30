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
	void ColTrap2(CharacterStatusData *charData);
	void SetMove(weekListObj objList, const Game_ctr &controller);
	bool InitAnim(void);

private:
	int nDamage;		// �X�P���g���p�̃_���[�W�ϐ�
	int nDamage2;		// �X�P���g���p�̃_���[�W�ϐ�
	int nGoalCnt[4];	// �X�P���g���̃S�[��������
};

