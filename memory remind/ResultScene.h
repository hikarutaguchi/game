#pragma once
#include "BaseScene.h"
#include "classObj.h"
#include "PlayerMng.h"

class ResultScene :
	public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	virtual unique_Base Updata(unique_Base own, Game_ctr &controller);	// 純粋仮想関数UpDate

	const VECTOR2 & PointUpDrawPos();		// P1リザルト表示
	const VECTOR2 & PointUpDrawPos2();		// P2リザルト表示

private:
	int Init(void);
	void Draw();

	int bGetCtr;
	bool fadeFinish;
	bool nextScene;
	
	sharedListObj objList;			// ｲﾝｽﾀﾝｽした情報を登録

	VECTOR2 PointPos;		
	int Poscnt;
	int resultCnt;
	bool FlameFlag;

	VECTOR2 PointPos2;
	int Poscnt2;
	int resultCnt2;
	bool FlameFlag2;
};

