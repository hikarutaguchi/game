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

	const int SetSlimePlayerDamage(int Damage);					// SlimeプレイヤーのDamageをSet
	const int GetSlimeDamageData();								// SlimeプレイヤーのDamageをGet

	const int SetSkeletonPlayerDamage(int Damage);				// SlimeプレイヤーのDamageをSet
	const int GetSkeletonDamageData();							// SlimeプレイヤーのDamageをGet

	const int SetCarbunclePlayerDamage(int Damage);				// SlimeプレイヤーのDamageをSet
	const int GetCarbuncleDamageData();							// SlimeプレイヤーのDamageをGet

	/*int AttackPoint(void);
	int DamagePoint(void);*/

	const void HP_Draw();

private:
	void operator=(const PlayerMng& obj) {} // 代入演算子禁止
	PlayerMng(const PlayerMng &obj) {}		  // コピーコンストラクタ禁止

	int SDamage;		// SlimeのDamage変数
	int NDamage;		// SkeletonのDamage変数
	int CDamage;		// CarbuncleのDamage変数

	VECTOR2 hpPos[MAX_HP];
	VECTOR2 pPos[CONTROLLER_MAX];

	PLAYER_HP_TBL hpPos_TBL;
	PLAYER_HP_FLAG hpFlag;
};
