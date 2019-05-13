#pragma once
#include "Obj.h"
#include "MapCtl.h"
#include "VECTOR2.h"
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
	MAP_ID id;
};
