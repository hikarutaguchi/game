#pragma once
//#include <type_traits>
#include <array>
#include "Obj.h"
#include "MapCtl.h"

enum TBL_ID {
	TBL_MAIN,
	TBL_SUB,
	TBL_MAX
};

enum DIR_TBL_ID {
	DIR_TBL_MAIN,
	DIR_TBL_OPP,
	DIR_TBL_SUB1,
	DIR_TBL_SUB2,
	DIR_TBL_MAX
};

enum SIDE_CHECK {
	OUT_SIDE,
	IN_SIDE,
	SIDE_MAX
};

#define PLAYER_DEF_SPEED 2
#define PLAYER_LIFE 6
#define lpPlayer Player::GetInstance()

using DIR_TBL_ARRAY		= std::array<int, DIR_MAX>;
using DIR_TBL_PTR_ARRAY = std::array<int*[TBL_MAX], DIR_MAX>;
using DIR_TBL_DIR		= std::array<DIR[DIR_TBL_MAX], DIR_MAX>;
using MAP_MOVE_TBL		= std::array<bool, static_cast<int>(MAP_ID::MAX)>;

class Player :
	public Obj
{
public:
	static Player &GetInstance(void)
	{
		static Player s_instance;
		return s_instance;
	}
	Player(VECTOR2 setupPos,VECTOR2 drawOffset);						// �����t��(Pos,�`��̍ۂ�offset)�ݽ�׸�
	Player();
	~Player();
	int Life();
	bool InitAnim(void);												// �摜�Ăяo��
private:

	void SetMove(weekListObj objList,const Game_ctr &controller);		//�@��ڲ԰�ړ�,�����蔻��
	bool CheckObjType(OBJ_TYPE type);									//�@��޼ު����������
	bool afterkeyFlag;													//�@��޷������׸�
	bool DethProcess();													//	���ʎ�����
	void GetItem(void);													//	item�擾���̏���
	int fireLength;

	int life;
	int count;
	int speed;
	DIR_TBL_ARRAY keyTableID;	// ���ͷ�ð���
	DIR_TBL_ARRAY speedTbl;		// ��߰��ð���
	DIR_TBL_PTR_ARRAY posTbl;	// ���Wð���
	DIR_TBL_DIR dirTbl;			// ����ð���
	MAP_MOVE_TBL mapMove;		// ��޼ު�Ĉړ�����ð���

	unsigned int reStartCnt;	// ���������Ԓl�����Ԃ͖��G

	unsigned int fireGuardFlag;
};

