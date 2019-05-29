#include <algorithm>
#include "DxLib.h"
#include "SceneMng.h"
#include "Player.h"
#include "Game_ctr.h"
#include "SelectCur.h"
#include "Bomb.h"

#define lpScene SceneMng::GetInstance()
#define RE_START_TIME (120U) //U�������unsiged int�^�ɂȂ�

Player::Player(VECTOR2 setupPos, VECTOR2 drawOffset) :Obj(drawOffset)
{
	//speed = 2;

	//fireLength = 2;
	//// MAIN
	//posTbl = { &pos.y,  &pos.x,	 // ��
	//		   &pos.y,	&pos.x,  // ��
	//		   &pos.x,	&pos.y,  // ��
	//		   &pos.x,	&pos.y  // �E

	//};

	//posTbl2 = { &pos2.y,  &pos2.x,	 // ��
	//			&pos2.y,	&pos2.x,  // ��
	//			 &pos2.x,	&pos2.y,  // ��
	//			 &pos2.x,	&pos2.y  // �E

	//};
	////MAIN			
	//speedTbl = { -PLAYER_DEF_SPEED,			// ��
	//			 PLAYER_DEF_SPEED,			// ��
	//			-PLAYER_DEF_SPEED,			// ��
	//			 PLAYER_DEF_SPEED			// �E

	//};
	////MAIN	   OPP			SUB1		SUB2
	//dirTbl = { DIR_UP,    DIR_DOWN,	   DIR_RIGHT,   DIR_LEFT,		// ��(��,�E)
	//		   DIR_DOWN,  DIR_UP,	   DIR_RIGHT,	DIR_LEFT,		// ��(��,�E)
	//		   DIR_LEFT,  DIR_RIGHT,   DIR_UP,		DIR_DOWN,		    // ��(��,��)
	//		   DIR_RIGHT, DIR_LEFT,	   DIR_UP,		DIR_DOWN,			// �E(��,��)

	//};

	//dirTbl2 = { DIR_UP,    DIR_DOWN,	   DIR_RIGHT,   DIR_LEFT,		// ��(��,�E)
	//		 DIR_DOWN,  DIR_UP,	   DIR_RIGHT,	DIR_LEFT,		// ��(��,�E)
	//		 DIR_LEFT,  DIR_RIGHT,   DIR_UP,		DIR_DOWN,		    // ��(��,��)
	//		DIR_RIGHT, DIR_LEFT,	   DIR_UP,		DIR_DOWN,			// �E(��,��)

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
	AddAnim("��~", 0, 0, 4, 15, true);
	AddAnim("�ړ�", 0, 0, 4, 20, true);
	AddAnim("���S", 4, 0, 4, 8, false);
	return true;
}

#include <functional>

void Player::SetMove(weekListObj objList, const Game_ctr & controller)
{
	auto &chipSize = lpMapCtl.GetChipSize().x;

	cnt -= 1;

	if (GetAnim() == "���S")	//���S�A�j���Đ���
	{
		if (animEndFlag)		//��ҏI��������׸�
		{
			//�����Ŏc�@�����炵���肷��
			SetAnim("��~");
			reStartCnt = RE_START_TIME;
		}
	}
	reStartCnt -= (reStartCnt > 0);		// reStartCnt > 0�͐^�U�^�̏ꍇ�P�������
	visible = true;
	if ((reStartCnt / 5) % 2)	//3�ڰтɈ��false
	{
		visible = false;
	}

	//���g�𕪂���₷�����邽�߂�switch���g���B
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
									SetAnim("��~");
								}
							}

							if ((controller.GetCtr(i, CONTROLLER_P1) == PAD_HOLD) || (controller.GetCtr(i, CONTROLLER_P1) == PAD_PUSH))
							{
								if (PassF() == true)
								{
									//�␳����
									if ((*posTbl[Player::dir][TBL_SUB]) % chipSize)
									{
										(*posTbl[Player::dir][TBL_SUB]) = (((*posTbl[Player::dir][TBL_SUB] + chipSize / 2) / chipSize) * chipSize);
									}
									//�ړ�����
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
									SetAnim("��~");
								}
							}

							if ((controller.GetCtr(i, CONTROLLER_P2) == PAD_HOLD) || (controller.GetCtr(i, CONTROLLER_P2) == PAD_PUSH))
							{
								if (PassF2() == true)
								{
									//�␳����
									if ((*posTbl2[Player::dir2][TBL_SUB]) % chipSize)
									{
										(*posTbl2[Player::dir2][TBL_SUB]) = (((*posTbl2[Player::dir2][TBL_SUB] + chipSize / 2) / chipSize) * chipSize);
									}
									//�ړ�����
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
	SetAnim("��~");
}

bool Player::CheckObjType(OBJ_TYPE type)
{
	//�������Ƃ���񂪓����Ȃ�^����������U
	return (type == OBJ_PLAYER);
}

bool Player::DethProcess()
{
	if (reStartCnt)
	{
		return false;
	}
	dir = DIR_DOWN;
	SetAnim("���S");
	fireGuardFlag = 0U;
	return true;
}

bool Player::PassF()
{
	auto &chipSize = lpMapCtl.GetChipSize().x;

	auto sidePos = [&](DIR dir, VECTOR2 pos, int speed, SIDE_CHECK sideFlg) {
		VECTOR2 side;	//�z��ɂ��ď�����ؽĂɂ���
		switch (dir)
		{
		case DIR_LEFT:
			side = { (-(sideFlg ^ 1) + speed), 0 };
			break;
		case DIR_RIGHT:
			//���߻��ނ�1�����Ȃ̂�-1���Ă�����,-2����2��둤�Ȃ̂ňӖ����Ȃ�
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

	if (!mapMove[static_cast<int>(lpMapCtl.GetMapData(sidePos(Player::dir, pos, speedTbl[Player::dir], IN_SIDE)))])	//IN_SIDE�łP��n������
	{
		return false;
		_RPTN(_CRT_WARN, "player.pos:%d,%d\n", pos.x, pos.y);
		//�ړ��s�̵�޼ު�Ă��ׂɂ������ꍇ�͏������Ȃ�
	}
	return true;
}

bool Player::PassF2()
{
	auto &chipSize = lpMapCtl.GetChipSize().x;

	auto sidePos = [&](DIR dir, VECTOR2 pos, int speed, SIDE_CHECK sideFlg) {
		VECTOR2 side;	//�z��ɂ��ď�����ؽĂɂ���
		switch (dir)
		{
		case DIR_LEFT:
			side = { (-(sideFlg ^ 1) + speed), 0 };
			break;
		case DIR_RIGHT:
			//���߻��ނ�1�����Ȃ̂�-1���Ă�����,-2����2��둤�Ȃ̂ňӖ����Ȃ�
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

	if (!mapMove[static_cast<int>(lpMapCtl.GetMapData(sidePos(Player::dir2, pos2, speedTbl[Player::dir2], IN_SIDE)))])	//IN_SIDE�łP��n������
	{
		return false;
		_RPTN(_CRT_WARN, "player2.pos:%d,%d\n", pos2.x, pos2.y);
		//�ړ��s�̵�޼ު�Ă��ׂɂ������ꍇ�͏������Ȃ�
	}
	return true;
}


void Player::GetItem(void)
{
	//if ((pos % lpMapCtl.GetChipSize()) != VECTOR2(0, 0))		//�����߯�؂̎����������������̂ł��������
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
