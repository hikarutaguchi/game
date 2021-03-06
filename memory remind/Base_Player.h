#pragma once
//#include <type_traits>
#include <array>
#include "Obj.h"
#include "MapCtl.h"
#include "SelectCur.h"

typedef struct
{
	int HP;
	bool DethFlag;
	bool EvoFlag;
}CharacterStatusData;


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
#define PLAYER_DEF_LIFE 6
//#define lpPlayer Player::GetInstance()


using DIR_TBL_ARRAY = std::array<int, DIR_MAX>;
using DIR_TBL_PTR_ARRAY = std::array<int*[TBL_MAX], DIR_MAX>;
using DIR_TBL_DIR = std::array<DIR[DIR_TBL_MAX], DIR_MAX>;
using MAP_MOVE_TBL = std::array<bool, static_cast<int>(MAP_ID::MAX)>;

class Base_Player :
	virtual public Obj
{
public:
	//static Player &GetInstance(void)
	//{
	//	static Player s_instance;
	//	return s_instance;
	//}
	Base_Player(VECTOR2 setupPos, VECTOR2 drawOffset);						// 引数付き(Pos,描画の際のoffset)ｺﾝｽﾄﾗｸﾀ
	Base_Player();
	~Base_Player();

	bool InitAnim(void);												// 画像呼び出し
	virtual void ColTrap(CharacterStatusData *charData) = 0;

private:


protected:
	void SetMove(weekListObj objList, const Game_ctr &controller);		//　ﾌﾟﾚｲﾔｰ移動,当たり判定
	bool CheckObjType(OBJ_TYPE type);									//　ｵﾌﾞｼﾞｪｸﾄﾀｲﾌﾟﾁｪｯｸ
	bool DethProcess();													//	死ぬ時処理
	bool PassF();
	bool PassF2();
	void GetItem(void);													//	item取得時の処理

	bool afterkeyFlag;													//　ｻﾌﾞｷｰ入力ﾌﾗｸﾞ
	int fireLength;

	int cnt;
	int life;
	int count;
	int speed;

	DIR_TBL_ARRAY speedTbl;		// ｽﾋﾟｰﾄﾞﾃｰﾌﾞﾙ
	DIR_TBL_ARRAY huttobi;		// 吹っ飛びﾃｰﾌﾞﾙ
	DIR_TBL_PTR_ARRAY posTbl;	// 座標ﾃｰﾌﾞﾙ
	DIR_TBL_PTR_ARRAY posTbl2;	// 座標ﾃｰﾌﾞﾙ
	DIR_TBL_DIR dirTbl;			// 方向ﾃｰﾌﾞﾙ
	DIR_TBL_DIR dirTbl2;			// 方向ﾃｰﾌﾞﾙ
	MAP_MOVE_TBL mapMove;		// ｵﾌﾞｼﾞｪｸﾄ移動判定ﾃｰﾌﾞﾙ

	MAP_ID id;
	MAP_ID id2;

	unsigned int reStartCnt;	// こいつが時間値を持つ間は無敵

	unsigned int fireGuardFlag;

};


