#pragma once
#include "Obj.h"
#include "MapCtl.h"

class EditCursor :
	public Obj
{
public:
	EditCursor(VECTOR2 drawOffset);
	EditCursor();
	~EditCursor();

	void Draw(void);
private:
	void SetMove(weekListObj objList, const Game_ctr &controller);		// 移動ｾｯﾄ
	bool CheckObjType(OBJ_TYPE type);									// ｵﾌﾞｼﾞｪｸﾄﾀｲﾌﾟﾁｪｯｸ

	int keyGetRng;														// 受付ﾌﾚｰﾑ数
	int inputFram;														// 入力ﾌﾚｰﾑ数

	int count;
	int itemButton;
	int setButton;
	int resetButton;
	VECTOR2 befo2pos;
	VECTOR2 beforepos;
	MAP_ID befo2ID;
	MAP_ID beforeID;
	MAP_ID id;

	//サウンド
	int kettei;
	int cansell;
	int choice;
	int bu_bu;
};
