#include "Carbuncle.h"
#include "PlayerMng.h"


Carbuncle::Carbuncle(VECTOR2 drawOffset) :Obj(drawOffset)
{
	speed = 2;

	fireLength = 2;
	// MAIN
	posTbl = { &pos.y,  &pos.x,	 // ��
			   &pos.y,	&pos.x,  // ��
			   &pos.x,	&pos.y,  // ��
			   &pos.x,	&pos.y  // �E

	};

	posTbl2 = { &pos2.y,	&pos2.x,	// ��
				&pos2.y,	&pos2.x,	// ��
				&pos2.x,	&pos2.y,	// ��
				&pos2.x,	&pos2.y		// �E

	};
	//MAIN			
	speedTbl = { -PLAYER_DEF_SPEED,			// ��
				 PLAYER_DEF_SPEED,			// ��
				-PLAYER_DEF_SPEED,			// ��
				 PLAYER_DEF_SPEED			// �E

	};

	huttobi = {
			-128,			// ��
			 128,			// ��
			-128,			// ��
			 128			// �E
	};

	//MAIN	   OPP			SUB1		SUB2
	dirTbl = { DIR_UP,    DIR_DOWN,	   DIR_RIGHT,   DIR_LEFT,		// ��(��,�E)
			   DIR_DOWN,  DIR_UP,	   DIR_RIGHT,	DIR_LEFT,		// ��(��,�E)
			   DIR_LEFT,  DIR_RIGHT,   DIR_UP,		DIR_DOWN,		    // ��(��,��)
			   DIR_RIGHT, DIR_LEFT,	   DIR_UP,		DIR_DOWN,			// �E(��,��)

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
		false,	// GOALE
		true,	// NON1
		true,	// NON2
		true,	// NON3
	};

	if (lpSelCur.GetCharData(CONTROLLER_P1) == 3)
	{
		Init("image/Carbuncle.png", VECTOR2(64, 100), VECTOR2(4, 4), VECTOR2(64, 64));
	}

	if (lpSelCur.GetCharData(CONTROLLER_P2) == 3)
	{
		Init2("image/Carbuncle.png", VECTOR2(64, 100), VECTOR2(4, 4), VECTOR2(64, 128));
	}
	InitAnim();
	cnt = 240;
}

Carbuncle::Carbuncle()
{
}


Carbuncle::~Carbuncle()
{
}

void Carbuncle::ColTrap(CharacterStatusData * charData)
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
		charData->HP = charData->HP - 2;
		cDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetCarbunclePlayerDamage(cDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
			/*Player::DethProcess();*/
		}
		break;
	case (MAP_ID::EKI):
		charData->HP = charData->HP - 2;
		cDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetCarbunclePlayerDamage(cDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;

		}
		break;
	case (MAP_ID::NULLL):
		charData->HP = charData->HP - 2;
		cDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetCarbunclePlayerDamage(cDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::WIND):
		charData->HP = charData->HP - 2;
		cDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetCarbunclePlayerDamage(cDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::MAGIC):
		charData->HP = charData->HP - 2;
		cDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetCarbunclePlayerDamage(cDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::MAGIC1):
		charData->HP = charData->HP - 2;
		cDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetCarbunclePlayerDamage(cDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::BORN):
		charData->HP = charData->HP - 2;
		cDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetCarbunclePlayerDamage(cDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::ESA):
		charData->HP = charData->HP - 3;
		cDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetCarbunclePlayerDamage(cDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::TOOL):
		charData->HP = charData->HP - 4;
		cDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetCarbunclePlayerDamage(cDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::HOLE):
		(*posTbl[Base_Player::dir][TBL_MAIN]) += huttobi[Base_Player::dir];
		charData->HP = charData->HP - 1;
		cDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetCarbunclePlayerDamage(cDamage);

		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	default:
		break;
	}
}

void Carbuncle::SetMove(weekListObj objList, const Game_ctr & controller)
{
	Base_Player::SetMove(objList, controller);
	CharacterStatusData Character1StatusData = { PLAYER_DEF_LIFE - cDamage, false,false };
	ColTrap(&Character1StatusData);
}

bool Carbuncle::InitAnim(void)
{
	AddAnim("��~", 0, 0, 4, 15, true);
	AddAnim("�ړ�", 0, 0, 4, 20, true);
	AddAnim("���S", 4, 0, 4, 8, false);
	return true;
}
