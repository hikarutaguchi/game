#pragma once
#include <list>
#include "Obj.h"
#include "classObj.h"
#include "BaseScene.h"

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Updata(unique_Base own, const Game_ctr &controller);			// 純粋仮想実体側Updata

private:
	sharedListObj objList;														// ｲﾝｽﾀﾝｽした情報を登録
	int timeCnt;
	int startCnt;
	int Init(void);																// 呼び出し
	bool GameDraw();															// ｴﾃﾞｨｯﾄ表示
	int Pad[4];						// パッド情報
	bool padFlag;
};

