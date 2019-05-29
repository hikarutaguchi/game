#include "Base_Player.h"


#define lpScene SceneMng::GetInstance()
#define RE_START_TIME (120U) //U‚ğ‚Â‚¯‚é‚Æunsiged intŒ^‚É‚È‚é

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
	AddAnim("’â~", 0, 0, 4, 15, true);
	AddAnim("ˆÚ“®", 0, 0, 4, 20, true);
	AddAnim("€–S", 4, 0, 4, 8, false);
	return true;
}

void Base_Player::SetMove(weekListObj objList, const Game_ctr & controller)
{
	auto &chipSize = lpMapCtl.GetChipSize().x;

	cnt -= 1;

	if (GetAnim() == "€–S")	//€–SƒAƒjƒÄ¶’†
	{
		if (animEndFlag)		//±ÆÒI‚í‚Á‚½‚©Ì×¸Ş
		{
			//‚±‚±‚Åc‹@‚ğŒ¸‚ç‚µ‚½‚è‚·‚é
			SetAnim("’â~");
			reStartCnt = RE_START_TIME;
		}
	}
	reStartCnt -= (reStartCnt > 0);		// reStartCnt > 0‚Í^‹U^‚Ìê‡‚Pˆø‚©‚ê‚é
	visible = true;
	if ((reStartCnt / 5) % 2)	//3ÌÚ°Ñ‚Éˆê‰ñfalse
	{
		visible = false;
	}

	//’†g‚ğ•ª‚©‚è‚â‚·‚­‚·‚é‚½‚ß‚Éswitch‚ğg‚¤B
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
									SetAnim("’â~");
								}
							}

							if ((controller.GetCtr(i, CONTROLLER_P1) == PAD_HOLD) || (controller.GetCtr(i, CONTROLLER_P1) == PAD_PUSH))
							{
								if (PassF() == true)
								{
									//•â³ˆ—
									if ((*posTbl[Base_Player::dir][TBL_SUB]) % chipSize)
									{
										(*posTbl[Base_Player::dir][TBL_SUB]) = (((*posTbl[Base_Player::dir][TBL_SUB] + chipSize / 2) / chipSize) * chipSize);
									}
									//ˆÚ“®ˆ—
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
									SetAnim("’â~");
								}
							}

							if ((controller.GetCtr(i, CONTROLLER_P2) == PAD_HOLD) || (controller.GetCtr(i, CONTROLLER_P2) == PAD_PUSH))
							{
								if (PassF2() == true)
								{
									//•â³ˆ—
									if ((*posTbl2[Base_Player::dir2][TBL_SUB]) % chipSize)
									{
										(*posTbl2[Base_Player::dir2][TBL_SUB]) = (((*posTbl2[Base_Player::dir2][TBL_SUB] + chipSize / 2) / chipSize) * chipSize);
									}
									//ˆÚ“®ˆ—
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
	SetAnim("’â~");
}

bool Base_Player::CheckObjType(OBJ_TYPE type)
{
	//‚¤‚¯‚Á‚Æ‚½î•ñ‚ª“¯‚¶‚È‚ç^‚¿‚ª‚Á‚½‚ç‹U
	return (type == OBJ_PLAYER);
}

bool Base_Player::DethProcess()
{
	if (reStartCnt)
	{
		return false;
	}
	dir = DIR_DOWN;
	SetAnim("€–S");
	fireGuardFlag = 0U;
	return true;
}

bool Base_Player::PassF()
{
	auto &chipSize = lpMapCtl.GetChipSize().x;

	auto sidePos = [&](DIR dir, VECTOR2 pos, int speed, SIDE_CHECK sideFlg) {
		VECTOR2 side;	//”z—ñ‚É‚µ‚Ä‰Šú‰»Ø½Ä‚É‚·‚é
		switch (dir)
		{
		case DIR_LEFT:
			side = { (-(sideFlg ^ 1) + speed), 0 };
			break;
		case DIR_RIGHT:
			//Á¯Ìß»²½Ş‚Ì1‚Â“à‘¤‚È‚Ì‚Å-1‚µ‚Ä‚ ‚°‚é,-2‚¾‚Æ2‚ÂŒã‚ë‘¤‚È‚Ì‚ÅˆÓ–¡‚ª‚È‚¢
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

	if (!mapMove[static_cast<int>(lpMapCtl.GetMapData(sidePos(Base_Player::dir, pos, speedTbl[Base_Player::dir], IN_SIDE)))])	//IN_SIDE‚Å‚P‚ğ“n‚µ‚½‚¢
	{
		return false;
		_RPTN(_CRT_WARN, "player.pos:%d,%d\n", pos.x, pos.y);
		//ˆÚ“®•s‰Â‚ÌµÌŞ¼Şª¸Ä‚ª—×‚É‚ ‚Á‚½ê‡‚Íˆ—‚µ‚È‚¢
	}
	return true;
}

bool Base_Player::PassF2()
{
	auto &chipSize = lpMapCtl.GetChipSize().x;

	auto sidePos = [&](DIR dir, VECTOR2 pos, int speed, SIDE_CHECK sideFlg) {
		VECTOR2 side;	//”z—ñ‚É‚µ‚Ä‰Šú‰»Ø½Ä‚É‚·‚é
		switch (dir)
		{
		case DIR_LEFT:
			side = { (-(sideFlg ^ 1) + speed), 0 };
			break;
		case DIR_RIGHT:
			//Á¯Ìß»²½Ş‚Ì1‚Â“à‘¤‚È‚Ì‚Å-1‚µ‚Ä‚ ‚°‚é,-2‚¾‚Æ2‚ÂŒã‚ë‘¤‚È‚Ì‚ÅˆÓ–¡‚ª‚È‚¢
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

	if (!mapMove[static_cast<int>(lpMapCtl.GetMapData(sidePos(Base_Player::dir2, pos2, speedTbl[Base_Player::dir2], IN_SIDE)))])	//IN_SIDE‚Å‚P‚ğ“n‚µ‚½‚¢
	{
		return false;
		_RPTN(_CRT_WARN, "player2.pos:%d,%d\n", pos2.x, pos2.y);
		//ˆÚ“®•s‰Â‚ÌµÌŞ¼Şª¸Ä‚ª—×‚É‚ ‚Á‚½ê‡‚Íˆ—‚µ‚È‚¢
	}
	return true;
}

void Base_Player::GetItem(void)
{
}
