#include "Skelton.h"
#include "PlayerMng.h"


Skelton::Skelton(VECTOR2 drawOffset) :Obj(drawOffset)
{
	speed = 2;

	fireLength = 2;
	// MAIN
	posTbl = { &pos.y,  &pos.x,	 // 上
			   &pos.y,	&pos.x,  // 下
			   &pos.x,	&pos.y,  // 左
			   &pos.x,	&pos.y  // 右

	};

	posTbl2 = { &pos2.y,	&pos2.x,	// 上
				&pos2.y,	&pos2.x,	// 下
				&pos2.x,	&pos2.y,	// 左
				&pos2.x,	&pos2.y		// 右

	};
	//MAIN			
	speedTbl = { -PLAYER_DEF_SPEED,			// 上
				 PLAYER_DEF_SPEED,			// 下
				-PLAYER_DEF_SPEED,			// 左
				 PLAYER_DEF_SPEED			// 右

	};
	//MAIN	   OPP			SUB1		SUB2
	dirTbl = { DIR_UP,    DIR_DOWN,	   DIR_RIGHT,   DIR_LEFT,		// 上(左,右)
			   DIR_DOWN,  DIR_UP,	   DIR_RIGHT,	DIR_LEFT,		// 下(左,右)
			   DIR_LEFT,  DIR_RIGHT,   DIR_UP,		DIR_DOWN,		    // 左(下,上)
			   DIR_RIGHT, DIR_LEFT,	   DIR_UP,		DIR_DOWN,			// 右(下,上)

	};


	huttobi = {
		-128,			// 上
		 128,			// 下
		-128,			// 左
		 128			// 右
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

	if (lpSelCur.GetCharData(CONTROLLER_P1) == 2)
	{
		Init("image/skeleton.png", VECTOR2(64, 100), VECTOR2(4, 4), VECTOR2(64, 64));
	}
	if (lpSelCur.GetCharData(CONTROLLER_P2) == 2)
	{
		Init2("image/skeleton.png", VECTOR2(64, 100), VECTOR2(4, 4), VECTOR2(64, 128));
	}
	InitAnim();
	cnt = 240;
}

Skelton::Skelton()
{
}


Skelton::~Skelton()
{
}

void Skelton::ColTrap(CharacterStatusData * charData)
{
	if ((pos % lpMapCtl.GetChipSize()) != VECTOR2(0, 0))		//マス目ﾋﾟｯﾀﾘの時だけ処理
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
		nDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage(nDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
			/*Player::DethProcess();*/
		}
		break;
	case (MAP_ID::EKI):
		charData->HP = charData->HP - 2;
		nDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage(nDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;

		}
		break;
	case (MAP_ID::NULLL):
		charData->HP = charData->HP - 2;
		nDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage(nDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::WIND):
		charData->HP = charData->HP - 2;
		nDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage(nDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::MAGIC):
		charData->HP = charData->HP - 3;
		nDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage(nDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::MAGIC1):
		charData->HP = charData->HP - 4;
		nDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage(nDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::BORN):
		charData->HP = charData->HP - 2;
		nDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage(nDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::ESA):
		charData->HP = charData->HP - 2;
		nDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage(nDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::TOOL):
		charData->HP = charData->HP - 2;
		nDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage(nDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::HOLE):
		(*posTbl[Base_Player::dir][TBL_MAIN]) += huttobi[Base_Player::dir];
		charData->HP = charData->HP - 1;
		nDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage(nDamage);

		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	default:
		break;
	}

}

void Skelton::SetMove(weekListObj objList, const Game_ctr & controller)
{
	Base_Player::SetMove(objList, controller);
	CharacterStatusData Character1StatusData = { PLAYER_DEF_LIFE - nDamage, false,false };
	ColTrap(&Character1StatusData);
}

bool Skelton::InitAnim(void)
{
	AddAnim("停止", 0, 0, 4, 15, true);
	AddAnim("移動", 0, 0, 4, 20, true);
	AddAnim("死亡", 4, 0, 4, 8, false);
	return true;
}
