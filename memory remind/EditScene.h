#pragma once
#include <list>
#include "Obj.h"
#include "BaseScene.h"
#include "classObj.h"


class EditScene :
	public BaseScene
{
public:
	EditScene();
	~EditScene();
	virtual unique_Base Updata(unique_Base own, const Game_ctr &controller);

private:
	sharedListObj objList;			// ｲﾝｽﾀﾝｽした情報を登録
	int Init(void);					// 呼び出し
	void Text();					// 文字表示関数
	bool EditDraw();				// ｴﾃﾞｨｯﾄ表示
	VECTOR2 Drawpos;
};
