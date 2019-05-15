#include <algorithm>
#include "DxLib.h"
#include "SceneMng.h"
#include "Player.h"
#include "Game_ctr.h"
#include "Bomb.h"

#define lpScene SceneMng::GetInstance()
#define RE_START_TIME (120U) //U‚ğ‚Â‚¯‚é‚Æunsiged intŒ^‚É‚È‚é

Player::Player(VECTOR2 setupPos, VECTOR2 drawOffset) :Obj(drawOffset)
{
	speed = 2;

	fireLength = 2;
	// MAIN
	posTbl = { &pos.y,	&pos.x,  // ‰º
			   &pos.x,	&pos.y,  // ¶
			   &pos.x,	&pos.y,  // ‰E
			   &pos.y,  &pos.x	 // ã 
	};
	//MAIN			
	speedTbl = { PLAYER_DEF_SPEED,			// ‰º
				-PLAYER_DEF_SPEED,			// ¶
				 PLAYER_DEF_SPEED,			// ‰E
				-PLAYER_DEF_SPEED			// ã
	};
	//MAIN	   OPP			SUB1		SUB2
	dirTbl = { DIR_DOWN,  DIR_UP,		 DIR_LEFT,	DIR_RIGHT,		// ‰º(¶,‰E)
				DIR_LEFT,  DIR_RIGHT,	 DIR_DOWN,	DIR_UP,		    // ¶(‰º,ã)
				DIR_RIGHT, DIR_LEFT,	 DIR_DOWN,	DIR_UP,			// ‰E(‰º,ã)
				DIR_UP,    DIR_DOWN,	 DIR_LEFT,	DIR_RIGHT,		// ã(¶,‰E)
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
	AddAnim("’â~", 0, 0, 4, 15, true);
	AddAnim("ˆÚ“®", 0, 0, 4, 20, true);
	AddAnim("€–S", 4, 0, 4, 8, false);
	return true;
}

#include <functional>

void Player::SetMove(weekListObj objList, const Game_ctr & controller)
{
	auto &chipSize = lpMapCtl.GetChipSize().x;


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

	//’†g‚ğ•ª‚©‚è‚â‚·‚­‚·‚é‚½‚ß‚Éswitch‚ğg‚¤
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

	switch (controller.GetCtr(CONTROLLER_1P_INPUT_UP))
	{
	case PAD_HOLD:	case PAD_PUSH:
		Player::dir = dirTbl[DIR_UP][TBL_MAIN];		//•ûŒü‚Ì¾¯Ä

				//“®‚¢‚Ä‚¢‚¢‚©ˆ—
		if (!mapMove[static_cast<int>(lpMapCtl.GetMapData(sidePos(Player::dir, pos, speedTbl[DIR_UP], IN_SIDE)))])	//IN_SIDE‚Å‚P‚ğ“n‚µ‚½‚¢
		{
			//ˆÚ“®ˆ—
			(*posTbl[Player::dir][TBL_MAIN]) = *posTbl[Player::dir][TBL_SUB];
			_RPTN(_CRT_WARN, "player.pos:%d,%d\n", pos.x, pos.y);
			//ˆÚ“®•s‰Â‚ÌµÌŞ¼Şª¸Ä‚ª—×‚É‚ ‚Á‚½ê‡‚Íˆ—‚µ‚È‚¢
		}
		//•â³ˆ—
		if ((*posTbl[Player::dir][TBL_SUB]) % chipSize)
		{
			(*posTbl[Player::dir][TBL_SUB]) = (((*posTbl[Player::dir][TBL_SUB] + chipSize / 2) / chipSize) * chipSize);
		}
		//ˆÚ“®ˆ—
		(*posTbl[Player::dir][TBL_MAIN]) += speedTbl[Player::dir];
		_RPTN(_CRT_WARN, "player.pos:%d,%d\n", pos.x, pos.y);
		break;
	case PAD_FREE:	case PAD_PULL:
		if ((controller.GetCtr(CONTROLLER_1P_INPUT_UP) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_DOWN) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_LEFT) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_RIGHT) == PAD_FREE))
		{
			SetAnim("’â~");
		}
		break;
	default:
		break;
	}
	//---------------------------------------------------------------------------------
	switch (controller.GetCtr(CONTROLLER_1P_INPUT_DOWN))
	{
	case PAD_HOLD:	case PAD_PUSH:
		Player::dir = dirTbl[DIR_DOWN][0];		//•ûŒü‚Ì¾¯Ä

				//“®‚¢‚Ä‚¢‚¢‚©ˆ—
		if (!mapMove[static_cast<int>(lpMapCtl.GetMapData(sidePos(Player::dir, pos, speedTbl[DIR_DOWN], IN_SIDE)))])	//IN_SIDE‚Å‚P‚ğ“n‚µ‚½‚¢
		{
			//ˆÚ“®•s‰Â‚ÌµÌŞ¼Şª¸Ä‚ª—×‚É‚ ‚Á‚½ê‡‚Íˆ—‚µ‚È‚¢
		}
		//•â³ˆ—
		if ((*posTbl[Player::dir][TBL_SUB]) % chipSize)
		{
			(*posTbl[Player::dir][TBL_SUB]) = (((*posTbl[Player::dir][TBL_SUB] + chipSize / 2) / chipSize) * chipSize);
		}
		//ˆÚ“®ˆ—
		(*posTbl[Player::dir][TBL_MAIN]) += speedTbl[Player::dir];
		_RPTN(_CRT_WARN, "player.pos:%d,%d\n", pos.x, pos.y);
		break;
	case PAD_FREE:	case PAD_PULL:
		if ((controller.GetCtr(CONTROLLER_1P_INPUT_UP) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_DOWN) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_LEFT) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_RIGHT) == PAD_FREE))
		{
			SetAnim("’â~");
		}
		break;
	default:
		break;
	}
	//---------------------------------------------------------------------------------
	switch (controller.GetCtr(CONTROLLER_1P_INPUT_LEFT))
	{
	case PAD_HOLD:	case PAD_PUSH:
		Player::dir = dirTbl[DIR_LEFT][0];		//•ûŒü‚Ì¾¯Ä

				//“®‚¢‚Ä‚¢‚¢‚©ˆ—
		if (!mapMove[static_cast<int>(lpMapCtl.GetMapData(sidePos(Player::dir, pos, speedTbl[DIR_DOWN], IN_SIDE)))])	//IN_SIDE‚Å‚P‚ğ“n‚µ‚½‚¢
		{
			//ˆÚ“®•s‰Â‚ÌµÌŞ¼Şª¸Ä‚ª—×‚É‚ ‚Á‚½ê‡‚Íˆ—‚µ‚È‚¢
		}
		//•â³ˆ—
		if ((*posTbl[Player::dir][TBL_SUB]) % chipSize)
		{
			(*posTbl[Player::dir][TBL_SUB]) = (((*posTbl[Player::dir][TBL_SUB] + chipSize / 2) / chipSize) * chipSize);
		}
		//ˆÚ“®ˆ—
		(*posTbl[Player::dir][TBL_MAIN]) += speedTbl[Player::dir];
		_RPTN(_CRT_WARN, "player.pos:%d,%d\n", pos.x, pos.y);
		break;
	case PAD_FREE:	case PAD_PULL:
		if ((controller.GetCtr(CONTROLLER_1P_INPUT_UP) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_DOWN) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_LEFT) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_RIGHT) == PAD_FREE))
		{
			SetAnim("’â~");
		}
		break;
	default:
		break;
	}
	//---------------------------------------------------------------------------------
	switch (controller.GetCtr(CONTROLLER_1P_INPUT_RIGHT))
	{
	case PAD_HOLD:	case PAD_PUSH:
		Player::dir = dirTbl[DIR_RIGHT][0];		//•ûŒü‚Ì¾¯Ä

				//“®‚¢‚Ä‚¢‚¢‚©ˆ—
		if (!mapMove[static_cast<int>(lpMapCtl.GetMapData(sidePos(Player::dir, pos, speedTbl[DIR_DOWN], IN_SIDE)))])	//IN_SIDE‚Å‚P‚ğ“n‚µ‚½‚¢
		{
			//ˆÚ“®•s‰Â‚ÌµÌŞ¼Şª¸Ä‚ª—×‚É‚ ‚Á‚½ê‡‚Íˆ—‚µ‚È‚¢
		}
		//•â³ˆ—
		if ((*posTbl[Player::dir][TBL_SUB]) % chipSize)
		{
			(*posTbl[Player::dir][TBL_SUB]) = (((*posTbl[Player::dir][TBL_SUB] + chipSize / 2) / chipSize) * chipSize);
		}
		//ˆÚ“®ˆ—
		(*posTbl[Player::dir][TBL_MAIN]) += speedTbl[Player::dir];
		_RPTN(_CRT_WARN, "player.pos:%d,%d\n", pos.x, pos.y);
		break;
	case PAD_FREE:	case PAD_PULL:
		if ((controller.GetCtr(CONTROLLER_1P_INPUT_UP) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_DOWN) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_LEFT) == PAD_FREE)
			&& (controller.GetCtr(CONTROLLER_1P_INPUT_RIGHT) == PAD_FREE))
		{
			SetAnim("’â~");
		}
		break;
	default:
		break;
	}
	SetAnim("ˆÚ“®");
}

bool Player::CheckObjType(OBJ_TYPE type)
{
	//‚¤‚¯‚Á‚Æ‚½î•ñ‚ª“¯‚¶‚È‚ç^‚¿‚ª‚Á‚½‚ç‹U
	return (type == OBJ_PLAYER);
}

bool Player::DethProcess()
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

void Player::GetItem(void)
{
	//if ((pos % lpMapCtl.GetChipSize()) != VECTOR2(0, 0))		//¡–ÚËß¯ÀØ‚Ì‚¾‚¯ˆ—‚µ‚½‚¢‚Ì‚Å‚±‚ê‚ÅÁª¯¸
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
