#include <algorithm>
#include "DxLib.h"
#include "SceneMng.h"
#include "Player.h"
#include "Game_ctr.h"
#include "SelectCur.h"
#include "Bomb.h"

#define lpScene SceneMng::GetInstance()
#define RE_START_TIME (120U) //Uをつけるとunsiged int型になる

Player::Player(VECTOR2 setupPos, VECTOR2 drawOffset) :Obj(drawOffset)
{
	//speed = 2;

	//fireLength = 2;
	//// MAIN
	//posTbl = { &pos.y,  &pos.x,	 // 上
	//		   &pos.y,	&pos.x,  // 下
	//		   &pos.x,	&pos.y,  // 左
	//		   &pos.x,	&pos.y  // 右

	//};

	//posTbl2 = { &pos2.y,  &pos2.x,	 // 上
	//			&pos2.y,	&pos2.x,  // 下
	//			 &pos2.x,	&pos2.y,  // 左
	//			 &pos2.x,	&pos2.y  // 右

	//};
	////MAIN			
	//speedTbl = { -PLAYER_DEF_SPEED,			// 上
	//			 PLAYER_DEF_SPEED,			// 下
	//			-PLAYER_DEF_SPEED,			// 左
	//			 PLAYER_DEF_SPEED			// 右

	//};
	////MAIN	   OPP			SUB1		SUB2
	//dirTbl = { DIR_UP,    DIR_DOWN,	   DIR_RIGHT,   DIR_LEFT,		// 上(左,右)
	//		   DIR_DOWN,  DIR_UP,	   DIR_RIGHT,	DIR_LEFT,		// 下(左,右)
	//		   DIR_LEFT,  DIR_RIGHT,   DIR_UP,		DIR_DOWN,		    // 左(下,上)
	//		   DIR_RIGHT, DIR_LEFT,	   DIR_UP,		DIR_DOWN,			// 右(下,上)

	//};

	//dirTbl2 = { DIR_UP,    DIR_DOWN,	   DIR_RIGHT,   DIR_LEFT,		// 上(左,右)
	//		 DIR_DOWN,  DIR_UP,	   DIR_RIGHT,	DIR_LEFT,		// 下(左,右)
	//		 DIR_LEFT,  DIR_RIGHT,   DIR_UP,		DIR_DOWN,		    // 左(下,上)
	//		DIR_RIGHT, DIR_LEFT,	   DIR_UP,		DIR_DOWN,			// 右(下,上)

	//};

	//mapMove = {
	//	true,	// YUKA	
	//	false,	// IWA
	//	true,	// HOLE
	//	true,	// UNTI
	//	true,	// 1
	//	true,	// 2
	//	true,	// 3
	//	true,	// 4		
	//	true,	// 5
	//	true,	// 6
	//	true,	// 7
	//	true,	// 8
	//};

	//afterkeyFlag = false;
	//reStartCnt = 0U;
	//fireGuardFlag = 0U;
	//cnt = 240;


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

	cnt -= 1;

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

	//中身を分かりやすくするためにswitchを使う。
	if (cnt <= 0)
	{
		for (int i = 0; i < CONTROLLER_MAX; i++)
		{
			if (lpSelCur.GetCharFlag((P_TYPE)i))
			{
				if (lpSelCur.GetPlayerFlag((P_TYPE)i))
				{
					switch ((P_TYPE)i)
					{
					case CONTROLLER_P1:
						for (int i = 0; i < DIR_MAX; i++)
						{
							if ((controller.GetCtr(i, CONTROLLER_P1) == PAD_HOLD) || (controller.GetCtr(i, CONTROLLER_P1) == PAD_PUSH))
							{
								Player::dir = dirTbl[i][TBL_MAIN];
							}
							else if ((controller.GetCtr(i, CONTROLLER_P1) == PAD_FREE) || (controller.GetCtr(i, CONTROLLER_P1) == PAD_PULL))
							{
								if ((controller.GetCtr(INPUT_UP, CONTROLLER_P1) == PAD_FREE) && (controller.GetCtr(INPUT_DOWN, CONTROLLER_P1) == PAD_FREE)
									&& (controller.GetCtr(INPUT_LEFT, CONTROLLER_P1) == PAD_FREE) && (controller.GetCtr(INPUT_RIGHT, CONTROLLER_P1) == PAD_FREE))
								{
									SetAnim("停止");
								}
							}

							if ((controller.GetCtr(i, CONTROLLER_P1) == PAD_HOLD) || (controller.GetCtr(i, CONTROLLER_P1) == PAD_PUSH))
							{
								if (PassF() == true)
								{
									//補正処理
									if ((*posTbl[Player::dir][TBL_SUB]) % chipSize)
									{
										(*posTbl[Player::dir][TBL_SUB]) = (((*posTbl[Player::dir][TBL_SUB] + chipSize / 2) / chipSize) * chipSize);
									}
									//移動処理
									(*posTbl[Player::dir][TBL_MAIN]) += speedTbl[Player::dir];
									_RPTN(_CRT_WARN, "player.pos:%d,%d\n", pos.x, pos.y);
								}
							}
						}
						break;

					case CONTROLLER_P2:
						for (int i = 0; i < DIR_MAX; i++)
						{
							if ((controller.GetCtr(i, CONTROLLER_P2) == PAD_HOLD) || (controller.GetCtr(i, CONTROLLER_P2) == PAD_PUSH))
							{
								Player::dir2 = dirTbl[i][TBL_MAIN];
							}
							else if ((controller.GetCtr(i, CONTROLLER_P2) == PAD_FREE) || (controller.GetCtr(i, CONTROLLER_P2) == PAD_PULL))
							{
								if ((controller.GetCtr(INPUT_UP, CONTROLLER_P2) == PAD_FREE) && (controller.GetCtr(INPUT_DOWN, CONTROLLER_P2) == PAD_FREE)
									&& (controller.GetCtr(INPUT_LEFT, CONTROLLER_P2) == PAD_FREE) && (controller.GetCtr(INPUT_RIGHT, CONTROLLER_P2) == PAD_FREE))
								{
									SetAnim("停止");
								}
							}

							if ((controller.GetCtr(i, CONTROLLER_P2) == PAD_HOLD) || (controller.GetCtr(i, CONTROLLER_P2) == PAD_PUSH))
							{
								if (PassF2() == true)
								{
									//補正処理
									if ((*posTbl2[Player::dir2][TBL_SUB]) % chipSize)
									{
										(*posTbl2[Player::dir2][TBL_SUB]) = (((*posTbl2[Player::dir2][TBL_SUB] + chipSize / 2) / chipSize) * chipSize);
									}
									//移動処理
									(*posTbl2[Player::dir2][TBL_MAIN]) += speedTbl[Player::dir2];
									_RPTN(_CRT_WARN, "player.pos:%d,%d\n", pos2.x, pos2.y);
								}
							}
						}
						break;
					default:
						break;
					}
				}
			}
		}
	

	}
	lpMapCtl.GetMapID(pos, id);
	lpMapCtl.GetMapID(pos2, id2);
	SetAnim("停止");
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

bool Player::PassF()
{
	auto &chipSize = lpMapCtl.GetChipSize().x;

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

	if (!mapMove[static_cast<int>(lpMapCtl.GetMapData(sidePos(Player::dir, pos, speedTbl[Player::dir], IN_SIDE)))])	//IN_SIDEで１を渡したい
	{
		return false;
		_RPTN(_CRT_WARN, "player.pos:%d,%d\n", pos.x, pos.y);
		//移動不可のｵﾌﾞｼﾞｪｸﾄが隣にあった場合は処理しない
	}
	return true;
}

bool Player::PassF2()
{
	auto &chipSize = lpMapCtl.GetChipSize().x;

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

	if (!mapMove[static_cast<int>(lpMapCtl.GetMapData(sidePos(Player::dir2, pos2, speedTbl[Player::dir2], IN_SIDE)))])	//IN_SIDEで１を渡したい
	{
		return false;
		_RPTN(_CRT_WARN, "player2.pos:%d,%d\n", pos2.x, pos2.y);
		//移動不可のｵﾌﾞｼﾞｪｸﾄが隣にあった場合は処理しない
	}
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
