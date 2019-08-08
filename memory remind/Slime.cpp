#include "Slime.h"
#include "PlayerMng.h"
#include "CntMng.h"
#include "ScreenShake.h"

Slime::Slime(VECTOR2 drawOffset) :Obj(drawOffset)
{
	speed = 2;

	fireLength = 2;
	// MAIN
	posTbl = {  &pos.y, &pos.x,	 // ��
				&pos.y,	&pos.x,  // ��
				&pos.x,	&pos.y,  // ��
				&pos.x,	&pos.y   // �E

	};


	posTbl2 = { &pos2.y,  &pos2.x,	  // ��
				&pos2.y,	&pos2.x,  // ��
				&pos2.x,	&pos2.y,  // ��
				 &pos2.x,	&pos2.y   // �E

	};

	//MAIN			
	speedTbl = { -PLAYER_DEF_SPEED,			// ��
				 PLAYER_DEF_SPEED,			// ��
				-PLAYER_DEF_SPEED,			// ��
				 PLAYER_DEF_SPEED			// �E

	};
	//MAIN	   OPP			SUB1		SUB2
	dirTbl = { DIR_UP,    DIR_DOWN,	   DIR_RIGHT,   DIR_LEFT,		// ��(��,�E)
			   DIR_DOWN,  DIR_UP,	   DIR_RIGHT,	DIR_LEFT,		// ��(��,�E)
			   DIR_LEFT,  DIR_RIGHT,   DIR_UP,		DIR_DOWN,		    // ��(��,��)
			   DIR_RIGHT, DIR_LEFT,	   DIR_UP,		DIR_DOWN,			// �E(��,��)

	};


	huttobi = {
		-128,			// ��
		 128,			// ��
		-128,			// ��
		 128			// �E
	};

	mapMove = {
		true,	// YUKA	
		false,	// IWA
		true,	// T1
		true,	// T2
		true,	// T3
		true,	// T4
		true,	// T5
		true,	// T6
		true,	// T7
		true,	// T8
		true,	// T9
		true,	// TA
		true,	// GOALE
		true,	// NON1
		true,	// NON2
		true,	// NON3
	};

	if (lpSelCur.GetCharData(CONTROLLER_P1) == 1)
	{
		Init("image/slimes.png", VECTOR2(64, 100), VECTOR2(4, 4), VECTOR2(64, 64));
	}

	if (lpSelCur.GetCharData(CONTROLLER_P2) == 1)
	{
		Init2("image/slimes.png", VECTOR2(64, 100), VECTOR2(4, 4), VECTOR2(64, 128));
	}
	InitAnim();
	cnt = 240;
	lpCntMng.SetGoalFlag(true, CONTROLLER_P1);
	lpCntMng.SetGoalFlag(true, CONTROLLER_P2);
	lpCntMng.SetGoalFlag(true, CONTROLLER_P3);
	lpCntMng.SetGoalFlag(true, CONTROLLER_P4);
}

Slime::Slime()
{
}


Slime::~Slime()
{
}

void Slime::ColTrap(CharacterStatusData * charData)
{
	if ((pos % lpMapCtl.GetChipSize()) != VECTOR2(0, 0))		//�}�X���߯�؂̎���������
	{
		return;
	}

	MAP_ID trapID = lpMapCtl.GetMapID(pos, id);

	switch (trapID)
	{
	case (MAP_ID::YUKA):
	case (MAP_ID::IWA):
		break;
	case (MAP_ID::UNTI):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		sDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSlimePlayerDamage(sDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
			/*Player::DethProcess();*/
		}
		break;
	case (MAP_ID::EKI):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 3;
		sDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSlimePlayerDamage(sDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;

		}
		break;
	case (MAP_ID::NULLL):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 4;
		sDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSlimePlayerDamage(sDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::WIND):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		sDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSlimePlayerDamage(sDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::MAGIC):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		sDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSlimePlayerDamage(sDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::MAGIC1):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		sDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSlimePlayerDamage(sDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::BORN):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		sDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSlimePlayerDamage(sDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::ESA):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		sDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSlimePlayerDamage(sDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::TOOL):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		sDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSlimePlayerDamage(sDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::HOLE):
		(*posTbl[Base_Player::dir][TBL_MAIN]) += huttobi[Base_Player::dir];
		charData->HP = charData->HP - 1;
		sDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSlimePlayerDamage(sDamage);
		lpScreenShaker.Shake();
		//GoalCnt[0]++;

		//lpCntMng.GoalSetCnt(sGoalCnt[0], CONTROLLER_P1);		// �f�o�b�N�ps

		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::GOAL):
		if (visible)
		{
			sGoalCnt[0]++;
		}

		lpCntMng.GoalSetCnt(sGoalCnt[0], CONTROLLER_P1);
		lpCntMng.SetGoalFlag(true, CONTROLLER_P1);
		visible = false;
		break;
	default:
		break;
	}
	if (charData->DethFlag == true)
	{
		lpCntMng.SetGoalFlag(true, CONTROLLER_P1);
		visible = false;
	}
}

void Slime::ColTrap2(CharacterStatusData * charData)
{
	if ((pos2 % lpMapCtl.GetChipSize()) != VECTOR2(0, 0))		//�}�X���߯�؂̎���������
	{
		return;
	}

	MAP_ID trapID = lpMapCtl.GetMapID(pos2, id2);

	switch (trapID)
	{
	case (MAP_ID::YUKA):
	case (MAP_ID::IWA):
		break;
	case (MAP_ID::UNTI):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		sDamage2 = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSlimePlayerDamage2(sDamage2);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
			/*Player::DethProcess();*/
		}
		break;
	case (MAP_ID::EKI):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 3;
		sDamage2 = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSlimePlayerDamage2(sDamage2);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;

		}
		break;
	case (MAP_ID::NULLL):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 4;
		sDamage2 = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSlimePlayerDamage2(sDamage2);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::WIND):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		sDamage2 = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSlimePlayerDamage2(sDamage2);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::MAGIC):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		sDamage2 = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSlimePlayerDamage2(sDamage2);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::MAGIC1):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		sDamage2 = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSlimePlayerDamage2(sDamage2);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::BORN):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		sDamage2 = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSlimePlayerDamage2(sDamage2);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::ESA):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		sDamage2 = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSlimePlayerDamage2(sDamage2);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::TOOL):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		sDamage2 = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSlimePlayerDamage2(sDamage2);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::HOLE):
		lpScreenShaker.Shake();
		(*posTbl2[Base_Player::dir2][TBL_MAIN]) += huttobi[Base_Player::dir2];
		charData->HP = charData->HP - 1;
		sDamage2 = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSlimePlayerDamage2(sDamage2);

		//sGoalCnt[1]++;

		//lpCntMng.GoalSetCnt(sGoalCnt[1], CONTROLLER_P2);		// �f�o�b�N�p

		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::GOAL):
		if (visible)
		{
			sGoalCnt[1]++;
		}

		lpCntMng.GoalSetCnt(sGoalCnt[1], CONTROLLER_P2);
		lpCntMng.SetGoalFlag(true, CONTROLLER_P2);
		visible = false;
		break;
	default:
		break;
	}
	if (charData->DethFlag == true)
	{
		lpScreenShaker.Shake();
		lpCntMng.SetGoalFlag(true, CONTROLLER_P2);
		visible = false;
	}
}

void Slime::SetMove(weekListObj objList, const Game_ctr & controller)
{
	if (visible)
	{
		Base_Player::SetMove(objList, controller);
		CharacterStatusData Character1StatusData = { PLAYER_DEF_LIFE - sDamage, false,false };
		ColTrap(&Character1StatusData);
	}
	CharacterStatusData Character2StatusData = { PLAYER_DEF_LIFE - sDamage2, false,false };
	ColTrap2(&Character2StatusData);
}

bool Slime::InitAnim(void)
{
	AddAnim("��~", 0, 0, 4, 15, true);
	AddAnim("�ړ�", 0, 0, 4, 20, true);
	AddAnim("���S", 4, 0, 4, 8, false);
	return true;
}
