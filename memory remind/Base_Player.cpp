#include "Base_Player.h"


#define lpScene SceneMng::GetInstance()
#define RE_START_TIME (120U) //Uをつけるとunsiged int型になる

Base_Player::Base_Player(VECTOR2 setupPos, VECTOR2 drawOffset)
{
}

Base_Player::Base_Player()
{
}


Base_Player::~Base_Player()
{
}

bool Base_Player::InitAnim(void)
{
	AddAnim("停止", 0, 0, 4, 15, true);
	AddAnim("移動", 0, 0, 4, 20, true);
	AddAnim("死亡", 4, 0, 4, 8, false);
	return true;
}

void Base_Player::SetMove(weekListObj objList, const Game_ctr & controller)
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
								Base_Player::dir = dirTbl[i][TBL_MAIN];
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
									if ((*posTbl[Base_Player::dir][TBL_SUB]) % chipSize)
									{
										(*posTbl[Base_Player::dir][TBL_SUB]) = (((*posTbl[Base_Player::dir][TBL_SUB] + chipSize / 2) / chipSize) * chipSize);
									}
									//移動処理
									(*posTbl[Base_Player::dir][TBL_MAIN]) += speedTbl[Base_Player::dir];
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
								Base_Player::dir2 = dirTbl[i][TBL_MAIN];
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
									if ((*posTbl2[Base_Player::dir2][TBL_SUB]) % chipSize)
									{
										(*posTbl2[Base_Player::dir2][TBL_SUB]) = (((*posTbl2[Base_Player::dir2][TBL_SUB] + chipSize / 2) / chipSize) * chipSize);
									}
									//移動処理
									(*posTbl2[Base_Player::dir2][TBL_MAIN]) += speedTbl[Base_Player::dir2];
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

bool Base_Player::CheckObjType(OBJ_TYPE type)
{
	//うけっとた情報が同じなら真ちがったら偽
	return (type == OBJ_PLAYER);
}

bool Base_Player::DethProcess()
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

bool Base_Player::PassF()
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

	if (!mapMove[static_cast<int>(lpMapCtl.GetMapData(sidePos(Base_Player::dir, pos, speedTbl[Base_Player::dir], IN_SIDE)))])	//IN_SIDEで１を渡したい
	{
		return false;
		_RPTN(_CRT_WARN, "player.pos:%d,%d\n", pos.x, pos.y);
		//移動不可のｵﾌﾞｼﾞｪｸﾄが隣にあった場合は処理しない
	}
	return true;
}

bool Base_Player::PassF2()
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

	if (!mapMove[static_cast<int>(lpMapCtl.GetMapData(sidePos(Base_Player::dir2, pos2, speedTbl[Base_Player::dir2], IN_SIDE)))])	//IN_SIDEで１を渡したい
	{
		return false;
		_RPTN(_CRT_WARN, "player2.pos:%d,%d\n", pos2.x, pos2.y);
		//移動不可のｵﾌﾞｼﾞｪｸﾄが隣にあった場合は処理しない
	}
	return true;
}

void Base_Player::GetItem(void)
{
}
