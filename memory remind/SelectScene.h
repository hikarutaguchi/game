#pragma once
#include "BaseScene.h"
#include "classObj.h"

class SelectScene :
	public BaseScene
{
public:
	SelectScene();
	~SelectScene();
	virtual unique_Base Updata(unique_Base own, const Game_ctr &controller);	// 純粋仮想関数UpDate

private:
	int Init(void);
	void Draw();
	sharedListObj objList;			// ｲﾝｽﾀﾝｽした情報を登録
	int Pad[4];						// パッド情報
	bool padFlag;
};

