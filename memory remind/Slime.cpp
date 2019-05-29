#include "Slime.h"



Slime::Slime(VECTOR2 drawOffset) :Obj(drawOffset)
{
	speed = 2;

	fireLength = 2;
	// MAIN
	posTbl = { &pos.y,  &pos.x,	 // ��
				   &pos.y,	&pos.x,  // ��
				   &pos.x,	&pos.y,  // ��
				   &pos.x,	&pos.y  // �E

	};


	posTbl2 = { &pos2.y,  &pos2.x,	 // ��
				&pos2.y,	&pos2.x,  // ��
			 &pos2.x,	&pos2.y,  // ��
			 &pos2.x,	&pos2.y  // �E

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
		true,	// HOLE
		true,	// UNTI
		true,	// 1
		true,	// 2
		true,	// 3
		true,	// 4		
		true,	// 5
		true,	// 6
		true,	// 7
		true,	// 8
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
	case (MAP_ID::EKI):
	case (MAP_ID::NULLL):
	case (MAP_ID::WIND):
	case (MAP_ID::MAGIC):
	case (MAP_ID::MAGIC1):
	case (MAP_ID::BORN):
	case (MAP_ID::ESA):
	case (MAP_ID::TOOL):
	case (MAP_ID::HOLE):
		//Player::DethProcess();
		(*posTbl[Player::dir][TBL_MAIN]) += huttobi[Player::dir];
		break;
	default:
		break;
	}

}

void Slime::SetMove(weekListObj objList, const Game_ctr & controller)
{
	Player::SetMove(objList, controller);
	CharacterStatusData Character1StatusData = { 10, false,false };
	ColTrap(&Character1StatusData);
}

bool Slime::InitAnim(void)
{
	AddAnim("��~", 0, 0, 4, 15, true);
	AddAnim("�ړ�", 0, 0, 4, 20, true);
	AddAnim("���S", 4, 0, 4, 8, false);
	return true;
}
