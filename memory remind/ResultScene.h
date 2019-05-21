#pragma once
#include "BaseScene.h"
#include "classObj.h"
#include "Player.h"

class ResultScene :
	public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	virtual unique_Base Updata(unique_Base own, Game_ctr &controller);	// 純粋仮想関数UpDate

private:
	int bGetCtr;
	bool fadeFinish;
	int Init(void);
	bool nextScene;
	void Draw();
	sharedListObj objList;			// ｲﾝｽﾀﾝｽした情報を登録
	int Pad[4];						// パッド情報
	bool padFlag;
};

