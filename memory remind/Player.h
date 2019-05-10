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
	Player(VECTOR2 setupPos,VECTOR2 drawOffset);						// 引数付き(Pos,描画の際のoffset)ｺﾝｽﾄﾗｸﾀ
	Player();
	~Player();
	int Life();
	bool InitAnim(void);												// 画像呼び出し
private:

	void SetMove(weekListObj objList,const Game_ctr &controller);		//　ﾌﾟﾚｲﾔｰ移動,当たり判定
	bool CheckObjType(OBJ_TYPE type);									//　ｵﾌﾞｼﾞｪｸﾄﾀｲﾌﾟﾁｪｯｸ
	bool afterkeyFlag;													//　ｻﾌﾞｷｰ入力ﾌﾗｸﾞ
	bool DethProcess();													//	死ぬ時処理
	void GetItem(void);													//	item取得時の処理
	int fireLength;

	int life;
	int count;
	int speed;
	DIR_TBL_ARRAY keyTableID;	// 入力ｷｰﾃｰﾌﾞﾙ
	DIR_TBL_ARRAY speedTbl;		// ｽﾋﾟｰﾄﾞﾃｰﾌﾞﾙ
	DIR_TBL_PTR_ARRAY posTbl;	// 座標ﾃｰﾌﾞﾙ
	DIR_TBL_DIR dirTbl;			// 方向ﾃｰﾌﾞﾙ
	MAP_MOVE_TBL mapMove;		// ｵﾌﾞｼﾞｪｸﾄ移動判定ﾃｰﾌﾞﾙ

	unsigned int reStartCnt;	// こいつが時間値を持つ間は無敵

	unsigned int fireGuardFlag;
};

