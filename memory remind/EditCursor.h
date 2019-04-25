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
	void SetMove(weekListObj objList, const Game_ctr &controller);		// ˆÚ“®¾¯Ä
	bool CheckObjType(OBJ_TYPE type);									// µÌŞ¼Şª¸ÄÀ²ÌßÁª¯¸

	int keyGetRng;														// ó•tÌÚ°Ñ”
	int inputFram;														// “ü—ÍÌÚ°Ñ”

	MAP_ID id;
};
