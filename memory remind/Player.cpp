#include <algorithm>
#include "DxLib.h"
#include "SceneMng.h"
#include "Player.h"
#include "Game_ctr.h"
#include "Bomb.h"

#define lpScene SceneMng::GetInstance()
#define RE_START_TIME (120U) //U�������unsiged int�^�ɂȂ�

Player::Player(VECTOR2 setupPos ,VECTOR2 drawOffset) :Obj(drawOffset)
{
	speed = 2;

	fireLength = 2;

	int Pad[4];
	for (int i = 0; i < GetJoypadNum(); i++)
	{
		for (int j = 0; j < 28; j++)
		{
			Pad[i] = GetJoypadInputState(DX_INPUT_PAD1 + i);
		}
	}
					//�@MAIN		
	keyTableID = { PAD_INPUT_DOWN,	// ������
				   PAD_INPUT_LEFT,	// ������
				   PAD_INPUT_RIGHT,	// �E����
				   PAD_INPUT_UP	// �����
	};	
					// MAIN
	posTbl = { &pos.y,	&pos.x,  // ��
			   &pos.x,	&pos.y,  // ��
			   &pos.x,	&pos.y,  // �E
			   &pos.y,  &pos.x	 // �� 
	};
				 //MAIN			
	speedTbl = { PLAYER_DEF_SPEED,			// ��
				-PLAYER_DEF_SPEED,			// ��
			   	 PLAYER_DEF_SPEED,			// �E
				-PLAYER_DEF_SPEED			// ��
	};
				//MAIN	   OPP			SUB1		SUB2
	dirTbl = {  DIR_DOWN,  DIR_UP,		 DIR_LEFT,	DIR_RIGHT,		// ��(��,�E)
				DIR_LEFT,  DIR_RIGHT,	 DIR_DOWN,	DIR_UP,		    // ��(��,��)
				DIR_RIGHT, DIR_LEFT,	 DIR_DOWN,	DIR_UP,			// �E(��,��)
				DIR_UP,    DIR_DOWN,	 DIR_LEFT,	DIR_RIGHT,		// ��(��,�E)
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
		//true,	// ITEM_CTL,		// �N�����۰�
		//true,	// ITEM_BOMB_THROW,	// ���e����
		//true,	// ITEM_FIRE_GUARD,	// ���ް��
		//true,	// ITEM_RANDOM,		// ��������яo��
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
	AddAnim("��~", 0, 0, 4, 15 ,true);
	AddAnim("�ړ�", 0, 0, 4, 20 ,true);
	AddAnim("���S", 4, 0, 4, 8, false);
	return true;
}

#include <functional>

void Player::SetMove(weekListObj objList, const Game_ctr & controller)
{
	//auto &keyTbl	= controller.GetCtr(KEY_TYPE_NOW);			//auto�̏ꍇ���̂����̂ŏ����������\
	//auto &keyTblOld = controller.GetCtr(KEY_TYPE_OLD);

	auto &chipSize  = lpMapCtl.GetChipSize().x;


	if (GetAnim() == "���S")	//���S�A�j���Đ���
	{
		if (animEndFlag)		//��ҏI��������׸�
		{
			//�����Ŏc�@�����炵���肷��
			SetAnim("��~");
			reStartCnt = RE_START_TIME;
		}
	}
	////���ƃv���C���[�̔���
	//if (!fireGuardFlag)
	//{
	//	if (lpMapCtl.GetFireMapData(pos))	//�����������玀�S
	//	{
	//		if (DethProcess())	//���S����������Ԃ�
	//		{
	//			return;
	//		}
	//	}
	//}
	reStartCnt -= (reStartCnt > 0);		// reStartCnt > 0�͐^�U�^�̏ꍇ�P�������
	visible = true;
	if ((reStartCnt / 5) % 2)	//3�ڰтɈ��false
	{
		visible = false;
	}

	//if ((keyTbl[KEY_INPUT_SPACE]) & (~keyTblOld[KEY_INPUT_SPACE]))
	//{
	//	AddObjList()(objList, std::make_unique<Bomb>( ((pos / chipSize) * chipSize), fireLength , lpSceneMng.GetDrawOffset() + VECTOR2( 0,-5 )) );	//fire�Œ������󂯎��
	//}


	//���g�𕪂���₷�����邽�߂�switch���g��
	auto sidePos = [&](DIR dir,VECTOR2 pos,int speed, SIDE_CHECK sideFlg) {
		VECTOR2 side;	//�z��ɂ��ď�����ؽĂɂ���
		switch (dir)
		{
		case DIR_LEFT:
			side = { (- (sideFlg^1) + speed), 0 };
			break;
		case DIR_RIGHT:
			//���߻��ނ�1�����Ȃ̂�-1���Ă�����,-2����2��둤�Ȃ̂ňӖ����Ȃ�
			side = { (chipSize - sideFlg) + 2, 0 };
			break;
		case DIR_UP:
			side = { 0, -(sideFlg^1) + speed };
			break;
		case DIR_DOWN:
			side = { 0, ((chipSize - sideFlg) + speed) };
			break;
		default:
			break;
		}
		return pos + side;
	};
	//�ړ���������
	auto CheckMove_Bomb = [&]() {
		bool rtnFlag = false;
		//�@
		sharedObjList tmpList = (*objList.lock());	//���g�����~�����Ȃ籽�ؽ��A�O�����~�����Ȃ炻�̂܂�	�����list���߰
		//����͏����ŏ��������̂�remove_if
		tmpList.remove_if([](sharedObj &obj_bomb) {return (!obj_bomb->CheckObjType(OBJ_BOMB)); });
		//�����蔻��
		for (auto &bomb : tmpList)	//bomb�����o��
		{
			//��r���ʕԂ�l��rtnFlag�ɕۑ��A�ۑ�����ۂ�or���
			rtnFlag |= (sidePos(dir, pos, 0,IN_SIDE) == sidePos(dirTbl[dir][DIR_TBL_OPP], bomb->GetPos(), 0,OUT_SIDE));
		}
		return !rtnFlag;
	};

	auto move = [&,dir = Player::dir](DIR_TBL_ID id) {		//�z��ɱ�������ۂ̈������Ⴄ�̂�id�ɂ���,��߰���ꂽ�O��player��dir
		//if (keyTbl[keyTableID[dirTbl[dir][id]]])
		//if (keyTableID[dirTbl[dir][id]])
		{
			//�����̾��
			Player::dir = dirTbl[dir][id];
   			//�����Ă���������
			if (!mapMove[static_cast<int>(lpMapCtl.GetMapData(sidePos(Player::dir,pos,speedTbl[Player::dir],IN_SIDE))) ])	//IN_SIDE�łP��n������
			{
				//�ړ��s�̵�޼ު�Ă��ׂɂ������ꍇ�͏������Ȃ�
				return false;
			}
			//�����̾�Ă̏�ɏ����ƌ����������Ƃ��ēn���K�v������̂ŁA�����̾�Ă̌�ɂ���
			//�ړ��̌�����Ă͂��Ă��Ăق����̂ŁA�����̾�Ă̌�ɏ���
			//���e�Ƃ̓����蔻��
			if ( !CheckMove_Bomb() )		//���if�̒��g�������Ȃ̂�or�����Ŋ��邱�Ƃ��ł���B
			{
				//���e���אڂ��Ă����ꍇ
				return false;
			}
			//�␳����
			if ( (*posTbl[Player::dir][TBL_SUB]) % chipSize)
			{
				( *posTbl[Player::dir][TBL_SUB] ) = ( ((*posTbl[Player::dir][TBL_SUB] + chipSize / 2) / chipSize) * chipSize);
			}
			//�ړ�����
			( *posTbl[Player::dir][TBL_MAIN] ) += speedTbl[Player::dir];
			_RPTN(_CRT_WARN, "player.pos:%d,%d\n", pos.x, pos.y);
			return true;
		}
		return false;
	};

	if (!(move( (DIR_TBL_ID)(DIR_TBL_SUB1 - (afterkeyFlag<< 1)) ) || move( (DIR_TBL_ID)(DIR_TBL_SUB2 - (afterkeyFlag<< 1))) ))	//sub��D������
	{
		afterkeyFlag = false;
		//�ړ����Ă��Ȃ��ꍇ
		if (!(move( (DIR_TBL_ID)(DIR_TBL_MAIN + (afterkeyFlag << 1)) ) || move( (DIR_TBL_ID)(DIR_TBL_OPP + (afterkeyFlag << 1))) ))	//�����ł��ړ����Ȃ��������~
		{
			SetAnim("��~");
			return;
		}
	}
	else
	{
		//sub���̓��͂���������flag������
		//afterkeyFlag  = keyTbl[ keyTableID [ dirTbl[dir][DIR_TBL_SUB1]] ];
		//afterkeyFlag |= static_cast<bool>(keyTbl[ keyTableID [ dirTbl[dir][DIR_TBL_SUB2]] ]);
		afterkeyFlag ^= (int)(GetAnim() == "��~"); 
	}
	SetAnim("�ړ�");
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
