#include "Base_Player.h"


#define lpScene SceneMng::GetInstance()
#define RE_START_TIME (120U) //U�������unsiged int�^�ɂȂ�

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
	AddAnim("��~", 0, 0, 4, 15, true);
	AddAnim("�ړ�", 0, 0, 4, 20, true);
	AddAnim("���S", 4, 0, 4, 8, false);
	return true;
}

void Base_Player::SetMove(weekListObj objList, const Game_ctr & controller)
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
								Base_Player::dir = dirTbl[i][TBL_MAIN];
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
									if ((*posTbl[Base_Player::dir][TBL_SUB]) % chipSize)
									{
										(*posTbl[Base_Player::dir][TBL_SUB]) = (((*posTbl[Base_Player::dir][TBL_SUB] + chipSize / 2) / chipSize) * chipSize);
									}
									//�ړ�����
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
									SetAnim("��~");
								}
							}

							if ((controller.GetCtr(i, CONTROLLER_P2) == PAD_HOLD) || (controller.GetCtr(i, CONTROLLER_P2) == PAD_PUSH))
							{
								if (PassF2() == true)
								{
									//�␳����
									if ((*posTbl2[Base_Player::dir2][TBL_SUB]) % chipSize)
									{
										(*posTbl2[Base_Player::dir2][TBL_SUB]) = (((*posTbl2[Base_Player::dir2][TBL_SUB] + chipSize / 2) / chipSize) * chipSize);
									}
									//�ړ�����
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
	SetAnim("��~");
}

bool Base_Player::CheckObjType(OBJ_TYPE type)
{
	//�������Ƃ���񂪓����Ȃ�^����������U
	return (type == OBJ_PLAYER);
}

bool Base_Player::DethProcess()
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

bool Base_Player::PassF()
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

	if (!mapMove[static_cast<int>(lpMapCtl.GetMapData(sidePos(Base_Player::dir, pos, speedTbl[Base_Player::dir], IN_SIDE)))])	//IN_SIDE�łP��n������
	{
		return false;
		_RPTN(_CRT_WARN, "player.pos:%d,%d\n", pos.x, pos.y);
		//�ړ��s�̵�޼ު�Ă��ׂɂ������ꍇ�͏������Ȃ�
	}
	return true;
}

bool Base_Player::PassF2()
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

	if (!mapMove[static_cast<int>(lpMapCtl.GetMapData(sidePos(Base_Player::dir2, pos2, speedTbl[Base_Player::dir2], IN_SIDE)))])	//IN_SIDE�łP��n������
	{
		return false;
		_RPTN(_CRT_WARN, "player2.pos:%d,%d\n", pos2.x, pos2.y);
		//�ړ��s�̵�޼ު�Ă��ׂɂ������ꍇ�͏������Ȃ�
	}
	return true;
}

void Base_Player::GetItem(void)
{
}
