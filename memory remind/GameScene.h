#pragma once
#include <list>
#include "Obj.h"
#include "classObj.h"
#include "BaseScene.h"
#include "Game_ctr.h"

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

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Updata(unique_Base own, Game_ctr &controller);			// 純粋仮想実体側Updata

private:
	sharedListObj objList;														// ｲﾝｽﾀﾝｽした情報を登録
	PLAYER_HP_TBL hpPos_TBL;
	PLAYER_HP_FLAG hpFlag;
	int SceneCnt;
	int timeCnt;
	int startCnt;
	bool fadeFinish;
	int bGetCtr;
	int Init(void);																// 呼び出し
	bool GameDraw();															// ｴﾃﾞｨｯﾄ表示
	int Pad[4];						// パッド情報
	bool padFlag;
	VECTOR2 hpPos[MAX_HP];
	VECTOR2 pPos[CONTROLLER_MAX];
	//サウンド
	int bgm;
	int one;
	int two;
	int three;
	int sixty;
	int byou;
	int nokori;
	int stop;
	int start;
};

