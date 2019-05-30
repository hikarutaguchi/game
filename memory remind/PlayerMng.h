#pragma once
#include "Base_Player.h"
#include "SelectCur.h"

#define lpPlayer PlayerMng::GetInstance()

enum P_HP
{
	ONE_HP,
	TWO_HP,
	THREE_HP,
	FOUR_HP,
	MAX_HP
};

using PLAYER_HP_TBL = std::array<VECTOR2, static_cast<int>(P_HP::MAX_HP)>;
using PLAYER_HP_FLAG = std::array<bool, static_cast<int>(P_HP::MAX_HP)>;

class PlayerMng :
	public Base_Player
{
public:
	static PlayerMng &GetInstance(void)
	{
		static PlayerMng s_instance;
		return s_instance;
	}
	PlayerMng();
	~PlayerMng();

	void ColTrap(CharacterStatusData *charData);
	bool CheckObjType(OBJ_TYPE type);

	const int SetSlimePlayerDamage(int Damage);					// Slime�v���C���[��Damage��Set
	const int GetSlimeDamageData();								// Slime�v���C���[��Damage��Get

	const int SetSkeletonPlayerDamage(int Damage);				// Skeleton�v���C���[��Damage��Set
	const int GetSkeletonDamageData();							// Skeleton�v���C���[��Damage��Get

	const int SetCarbunclePlayerDamage(int Damage);				// Carbuncle�v���C���[��Damage��Set
	const int GetCarbuncleDamageData();							// Carbuncle�v���C���[��Damage��Get

	const int SetSlimePlayerDamage2(int Damage);					// Slime�v���C���[2��Damage��Set
	const int GetSlimeDamageData2();								// Slime�v���C���[2��Damage��Get

	const int SetSkeletonPlayerDamage2(int Damage);				// Skeleton�v���C���[2��Damage��Set
	const int GetSkeletonDamageData2();							// Skeleton�v���C���[2��Damage��Get

	const int SetCarbunclePlayerDamage2(int Damage);				// Carbuncle�v���C���[2��Damage��Set
	const int GetCarbuncleDamageData2();							// Carbuncle�v���C���[2��Damage��Get

	/*int AttackPoint(void);
	int DamagePoint(void);*/

	const void HP_Draw();

private:
	void operator=(const PlayerMng& obj) {} // ������Z�q�֎~
	PlayerMng(const PlayerMng &obj) {}		  // �R�s�[�R���X�g���N�^�֎~

	int SDamage;		// Slime��Damage�ϐ�
	int NDamage;		// Skeleton��Damage�ϐ�
	int CDamage;		// Carbuncle��Damage�ϐ�

	int SDamage2;		// Slime��Damage�ϐ�
	int NDamage2;		// Skeleton��Damage�ϐ�
	int CDamage2;		// Carbuncle��Damage�ϐ�

	VECTOR2 hpPos[MAX_HP];
	VECTOR2 pPos[CONTROLLER_MAX];

	PLAYER_HP_TBL hpPos_TBL;
	PLAYER_HP_FLAG hpFlag;
};
