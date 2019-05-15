#include <algorithm>
#include "DxLib.h"
#include "SceneMng.h"
#include "Player.h"
#include "Game_ctr.h"
#include "Bomb.h"

#define lpScene SceneMng::GetInstance()
#define RE_START_TIME (120U) //Uをつけるとunsiged int型になる

Player::Player(VECTOR2 setupPos, VECTOR2 drawOffset) :Obj(drawOffset)
{
	speed = 2;

	fireLength = 2;
	// MAIN
	posTbl = { &pos.y,	&pos.x,  // 下
			   &pos.x,	&pos.y,  // 左
			   &pos.x,	&pos.y,  // 右
			   &pos.y,  &pos.x	 // 上 
	};
	//MAIN			
	speedTbl = { PLAYER_DEF_SPEED,			// 下
				-PLAYER_DEF_SPEED,			// 左
				 PLAYER_DEF_SPEED,			// 右
				-PLAYER_DEF_SPEED			// 上
	};
	//MAIN	   OPP			SUB1		SUB2
	dirTbl = { DIR_DOWN,  DIR_UP,		 DIR_LEFT,	DIR_RIGHT,		// 下(左,右)
				DIR_LEFT,  DIR_RIGHT,	 DIR_DOWN,	DIR_UP,		    // 左(下,上)
				DIR_RIGHT, DIR_LEFT,	 DIR_DOWN,	DIR_UP,			// 右(下,上)
				DIR_UP,    DIR_DOWN,	 DIR_LEFT,	DIR_RIGHT,		// 上(左,右)
	};

	mapMove = {
		true,	// MAP_ID_CUR	
		true,	// MAP_ID_FLOOR1
		true,	// MAP_ID_FLOOR2
		true,	// MAP_ID_BOMB
		true,	// MAP_ID_NON
		false,	// MAP_ID_WALL1
		false,	// MAP_ID_WALL2
		false,	// MAP_ID_BLOCK		
		true,	// ITEM_BOMB,
		true,	// ITEM_FIRE,
		true,	// ITEM_SPEED,
		true,	// ITEM_WALL_PASS,
	};

	Init("image/slimes.png", VECTOR2(64, 100), VECTOR2(4, 4), setupPos);
	InitAnim();
	afterkeyFlag = false;
	reStartCnt = 0U;
	fireGuardFlag = 0U;


}

Player::Player()
{
	life = PLAYER_LIFE;
}


Player::~Player()
{

}

int Player::Life()
{
	if (count > 120)
	{
		life -= 1;
		count = 0;
	}
	count++;
	return life;
}

bool Player::InitAnim(void)
{
	AddAnim("停止", 0, 0, 4, 15, true);
	AddAnim("移動", 0, 0, 4, 20, true);
	AddAnim("死亡", 4, 0, 4, 8, false);
	return true;
}

#include <functional>

void Player::SetMove(weekListObj objList, const Game_ctr & controller)
{
	auto &chipSize = lpMapCtl.GetChipSize().x;


	if (GetAnim() == "死亡")	//死亡アニメ再生中
	{
		if (animEndFlag)		//ｱﾆﾒ終わったかﾌﾗｸﾞ
		{
			//ここで残機を減らしたりする
			SetAnim("停止");
			reStartCnt = RE_START_TIME;
		}
	}
	reStartCnt -= (reStartCnt > 0);		// reStartCnt > 0は真偽真の場合１引かれる
	visible = true;
	if ((reStartCnt / 5) % 2)	//3ﾌﾚｰﾑに一回false
	{
		visible = false;
	}

	//中身を分かりやすくするためにswitchを使う
	auto sidePos = [&](DIR dir, VECTOR2 pos, int speed, SIDE_CHECK sideFlg) {
		VECTOR2 side;	//配列にして初期化ﾘｽﾄにする
		switch (dir)
		{
		case DIR_LEFT:
			side = { (-(sideFlg ^ 1) + speed), 0 };
			break;
		case DIR_RIGHT:
			//ﾁｯﾌﾟｻｲｽﾞの1つ内側なので-1してあげる,-2だと2つ後ろ側なので意味がない
			side = { (chipSize - sideFlg) + 2, 0 };
			break;
		case DIR_UP:
			side = { 0, -(sideFlg ^ 1) + speed };
			break;
		case DIR_DOWN:
			side = { 0, ((chipSize - sideFlg) + speed) };
			break;
		default:
			break;
		}
		return pos + side;
	};

	switch (controller.GetCtr(CONTROLLER_1P_INPUT_UP))
	{
	case PAD_HOLD:	case PAD_PUSH:
		Player::dir = dirTbl[DIR_UP][TBL_MAIN];		//方向のｾｯﾄ

				//動いていいか処理
		if (!mapMove[static_cast<int>(lpMapCtl.GetMapData(sidePos(Player::dir, pos, speedTbl[DIR_UP], IN_SIDE)))])	//IN_SIDEで１を渡したい
		{
			//移動処理
			(*posTbl[Player::dir][TBL_MAIN]) = *posTbl[Player::dir][TBL_SUB];
			_RPTN(_CRT_WARN, "player.pos:%d,%d\n", pos.x, pos.y);
			//移動不可のｵﾌﾞｼﾞｪｸﾄが隣にあった場合は処理しない
		}
		//補正処理
		if ((*posTbl[Player::dir][TBL_SUB]) % chipSize)
		{
			(*posTbl[Player::dir][TBL_SUB]) = (((*posTbl[Player::dir][TBL_SUB] + chipSize / 2) / chipSize) * chipSize);
		}
		//移動処理
		(*posTbl[Player::dir][TBL_MAIN]) += speedTbl[Player::dir];
		_RPTN(_CRT_WARN, "player.pos:%d,%d\n", pos.x, pos.y);
		break;
	case PAD_FREE:	case PAD_PULL:
		if ((controller.GetCtr(CONTROLLER_1P_INPUT_UP) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_DOWN) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_LEFT) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_RIGHT) == PAD_FREE))
		{
			SetAnim("停止");
		}
		break;
	default:
		break;
	}
	//---------------------------------------------------------------------------------
	switch (controller.GetCtr(CONTROLLER_1P_INPUT_DOWN))
	{
	case PAD_HOLD:	case PAD_PUSH:
		Player::dir = dirTbl[DIR_DOWN][0];		//方向のｾｯﾄ

				//動いていいか処理
		if (!mapMove[static_cast<int>(lpMapCtl.GetMapData(sidePos(Player::dir, pos, speedTbl[DIR_DOWN], IN_SIDE)))])	//IN_SIDEで１を渡したい
		{
			//移動不可のｵﾌﾞｼﾞｪｸﾄが隣にあった場合は処理しない
		}
		//補正処理
		if ((*posTbl[Player::dir][TBL_SUB]) % chipSize)
		{
			(*posTbl[Player::dir][TBL_SUB]) = (((*posTbl[Player::dir][TBL_SUB] + chipSize / 2) / chipSize) * chipSize);
		}
		//移動処理
		(*posTbl[Player::dir][TBL_MAIN]) += speedTbl[Player::dir];
		_RPTN(_CRT_WARN, "player.pos:%d,%d\n", pos.x, pos.y);
		break;
	case PAD_FREE:	case PAD_PULL:
		if ((controller.GetCtr(CONTROLLER_1P_INPUT_UP) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_DOWN) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_LEFT) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_RIGHT) == PAD_FREE))
		{
			SetAnim("停止");
		}
		break;
	default:
		break;
	}
	//---------------------------------------------------------------------------------
	switch (controller.GetCtr(CONTROLLER_1P_INPUT_LEFT))
	{
	case PAD_HOLD:	case PAD_PUSH:
		Player::dir = dirTbl[DIR_LEFT][0];		//方向のｾｯﾄ

				//動いていいか処理
		if (!mapMove[static_cast<int>(lpMapCtl.GetMapData(sidePos(Player::dir, pos, speedTbl[DIR_DOWN], IN_SIDE)))])	//IN_SIDEで１を渡したい
		{
			//移動不可のｵﾌﾞｼﾞｪｸﾄが隣にあった場合は処理しない
		}
		//補正処理
		if ((*posTbl[Player::dir][TBL_SUB]) % chipSize)
		{
			(*posTbl[Player::dir][TBL_SUB]) = (((*posTbl[Player::dir][TBL_SUB] + chipSize / 2) / chipSize) * chipSize);
		}
		//移動処理
		(*posTbl[Player::dir][TBL_MAIN]) += speedTbl[Player::dir];
		_RPTN(_CRT_WARN, "player.pos:%d,%d\n", pos.x, pos.y);
		break;
	case PAD_FREE:	case PAD_PULL:
		if ((controller.GetCtr(CONTROLLER_1P_INPUT_UP) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_DOWN) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_LEFT) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_RIGHT) == PAD_FREE))
		{
			SetAnim("停止");
		}
		break;
	default:
		break;
	}
	//---------------------------------------------------------------------------------
	switch (controller.GetCtr(CONTROLLER_1P_INPUT_RIGHT))
	{
	case PAD_HOLD:	case PAD_PUSH:
		Player::dir = dirTbl[DIR_RIGHT][0];		//方向のｾｯﾄ

				//動いていいか処理
		if (!mapMove[static_cast<int>(lpMapCtl.GetMapData(sidePos(Player::dir, pos, speedTbl[DIR_DOWN], IN_SIDE)))])	//IN_SIDEで１を渡したい
		{
			//移動不可のｵﾌﾞｼﾞｪｸﾄが隣にあった場合は処理しない
		}
		//補正処理
		if ((*posTbl[Player::dir][TBL_SUB]) % chipSize)
		{
			(*posTbl[Player::dir][TBL_SUB]) = (((*posTbl[Player::dir][TBL_SUB] + chipSize / 2) / chipSize) * chipSize);
		}
		//移動処理
		(*posTbl[Player::dir][TBL_MAIN]) += speedTbl[Player::dir];
		_RPTN(_CRT_WARN, "player.pos:%d,%d\n", pos.x, pos.y);
		break;
	case PAD_FREE:	case PAD_PULL:
		if ((controller.GetCtr(CONTROLLER_1P_INPUT_UP) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_DOWN) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_LEFT) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_RIGHT) == PAD_FREE))
		{
			SetAnim("停止");
		}
		break;
	default:
		break;
	}
	SetAnim("移動");
}

bool Player::CheckObjType(OBJ_TYPE type)
{
	//うけっとた情報が同じなら真ちがったら偽
	return (type == OBJ_PLAYER);
}

bool Player::DethProcess()
{
	if (reStartCnt)
	{
		return false;
	}
	dir = DIR_DOWN;
	SetAnim("死亡");
	fireGuardFlag = 0U;
	return true;
}

void Player::GetItem(void)
{
	//if ((pos % lpMapCtl.GetChipSize()) != VECTOR2(0, 0))		//升目ﾋﾟｯﾀﾘの時だけ処理したいのでこれでﾁｪｯｸ
	//{
	//	return;
	//}

	//auto itemID = [=]() 
	//{
	//	auto id = lpMapCtl.GetMapData(pos);
	//	return (id == MAP_ID::ITEM_RANDOM ? static_cast<MAP_ID>(ITEM_ID_START + GetRand(ITEM_MAX - 1)) : id);
	//};

	//auto parametorUP = [=](auto& parametorFlag, auto limnum)
	//{
	//	parametorFlag += (parametorFlag < limnum);
	//	lpMapCtl.SetMapData(pos, MAP_ID::NON);
	//};

	//switch (itemID())
	//{
	//	case MAP_ID::ITEM_FIRE_GUARD:
	//		parametorUP(fireGuardFlag, 1);
	//		break;
	//}
}
