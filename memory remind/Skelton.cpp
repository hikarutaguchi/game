#include "Skelton.h"
#include "PlayerMng.h"
#include "CntMng.h"
#include "ScreenShake.h"

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

	if (lpSelCur.GetCharData(CONTROLLER_P1) == 2)
	{
		Init("image/skeleton.png", VECTOR2(64, 100), VECTOR2(4, 4), VECTOR2(64, 64));
	}
	if (lpSelCur.GetCharData(CONTROLLER_P2) == 2)
	{
		Init2("image/skeleton.png", VECTOR2(64, 100), VECTOR2(4, 4), VECTOR2(64, 128));
	}

	lpCntMng.SetGoalFlag(true, CONTROLLER_P1);
	lpCntMng.SetGoalFlag(true, CONTROLLER_P2);
	lpCntMng.SetGoalFlag(true, CONTROLLER_P3);
	lpCntMng.SetGoalFlag(true, CONTROLLER_P4);

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
		lpScreenShaker.Shake();
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
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		nDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage(nDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;

		}
		break;
	case (MAP_ID::NULLL):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		nDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage(nDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::WIND):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		nDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage(nDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::MAGIC):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 3;
		nDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage(nDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::MAGIC1):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 4;
		nDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage(nDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::BORN):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		nDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage(nDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::ESA):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		nDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage(nDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::TOOL):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		nDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage(nDamage);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::HOLE):
		lpScreenShaker.Shake();
		(*posTbl[Base_Player::dir][TBL_MAIN]) += huttobi[Base_Player::dir];
		charData->HP = charData->HP - 1;
		nDamage = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage(nDamage);

		//nGoalCnt[0]++;

		//lpCntMng.GoalSetCnt(nGoalCnt[0], CONTROLLER_P1);		// デバック用

		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::GOAL):
		if (visible)
		{
			nGoalCnt[0]++;
		}

		lpCntMng.GoalSetCnt(nGoalCnt[0], CONTROLLER_P1);		
		lpCntMng.SetGoalFlag(true, CONTROLLER_P1);
		visible = false;
		break;
	default:
		break;
	}

	if (charData->DethFlag == true)
	{
		lpScreenShaker.Shake();
		lpCntMng.SetGoalFlag(true, CONTROLLER_P1);
		visible = false;
	}

}

void Skelton::ColTrap2(CharacterStatusData * charData)
{
	if ((pos2 % lpMapCtl.GetChipSize()) != VECTOR2(0, 0))		//マス目ﾋﾟｯﾀﾘの時だけ処理
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
		nDamage2 = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage2(nDamage2);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
			/*Player::DethProcess();*/
		}
		break;
	case (MAP_ID::EKI):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		nDamage2 = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage2(nDamage2);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;

		}
		break;
	case (MAP_ID::NULLL):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		nDamage2 = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage2(nDamage2);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::WIND):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		nDamage2 = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage2(nDamage2);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::MAGIC):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 3;
		nDamage2 = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage2(nDamage2);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::MAGIC1):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 4;
		nDamage2 = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage2(nDamage2);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::BORN):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		nDamage2 = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage2(nDamage2);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::ESA):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		nDamage2 = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage2(nDamage2);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::TOOL):
		lpScreenShaker.Shake();
		charData->HP = charData->HP - 2;
		nDamage2 = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage2(nDamage2);
		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::HOLE):
		lpScreenShaker.Shake();
		(*posTbl2[Base_Player::dir2][TBL_MAIN]) += huttobi[Base_Player::dir2];
		charData->HP = charData->HP - 1;
		nDamage2 = PLAYER_DEF_LIFE - charData->HP;
		lpPlayer.SetSkeletonPlayerDamage2(nDamage2);

		//nGoalCnt[1]++;

		//lpCntMng.GoalSetCnt(nGoalCnt[1], CONTROLLER_P2);		// デバック用

		if (charData->HP == 0)
		{
			charData->DethFlag = true;
		}
		break;
	case (MAP_ID::GOAL):
		if (visible)
		{
			nGoalCnt[1]++;
		}

		lpCntMng.GoalSetCnt(nGoalCnt[1], CONTROLLER_P2);	
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

void Skelton::SetMove(weekListObj objList, const Game_ctr & controller)
{
	if (visible)
	{
		Base_Player::SetMove(objList, controller);
		CharacterStatusData Character1StatusData = { PLAYER_DEF_LIFE - nDamage, false,false };
		ColTrap(&Character1StatusData);
	}
	CharacterStatusData Character2StatusData = { PLAYER_DEF_LIFE - nDamage2, false,false };
	ColTrap2(&Character2StatusData);
}

bool Skelton::InitAnim(void)
{
	AddAnim("停止", 0, 0, 4, 15, true);
	AddAnim("移動", 0, 0, 4, 20, true);
	AddAnim("死亡", 4, 0, 4, 8, false);
	return true;
}
