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

	const int SetSkeletonPlayerDamage(int Damage);				// SkeletonプレイヤーのDamageをSet
	const int GetSkeletonDamageData();							// SkeletonプレイヤーのDamageをGet

	const int SetCarbunclePlayerDamage(int Damage);				// CarbuncleプレイヤーのDamageをSet
	const int GetCarbuncleDamageData();							// CarbuncleプレイヤーのDamageをGet

	const int SetSlimePlayerDamage2(int Damage);					// Slimeプレイヤー2のDamageをSet
	const int GetSlimeDamageData2();								// Slimeプレイヤー2のDamageをGet

	const int SetSkeletonPlayerDamage2(int Damage);				// Skeletonプレイヤー2のDamageをSet
	const int GetSkeletonDamageData2();							// Skeletonプレイヤー2のDamageをGet

	const int SetCarbunclePlayerDamage2(int Damage);				// Carbuncleプレイヤー2のDamageをSet
	const int GetCarbuncleDamageData2();							// Carbuncleプレイヤー2のDamageをGet

	const bool SetRestartHpFlag(bool rhpflag);
	const bool GetRestartHpFlag();

	/*int AttackPoint(void);
	int DamagePoint(void);*/

	const void HP_Draw();

private:
	void operator=(const PlayerMng& obj) {} // 代入演算子禁止
	PlayerMng(const PlayerMng &obj) {}		  // コピーコンストラクタ禁止

	bool HpFlag;		// HPのリセット用変数
	int SDamage;		// SlimeのDamage変数
	int NDamage;		// SkeletonのDamage変数
	int CDamage;		// CarbuncleのDamage変数

	int SDamage2;		// SlimeのDamage変数
	int NDamage2;		// SkeletonのDamage変数
	int CDamage2;		// CarbuncleのDamage変数

	VECTOR2 hpPos[MAX_HP];
	VECTOR2 pPos[CONTROLLER_MAX];

	PLAYER_HP_TBL hpPos_TBL;
	PLAYER_HP_FLAG hpFlag;
};
