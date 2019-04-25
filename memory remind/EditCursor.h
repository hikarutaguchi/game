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
	void SetMove(weekListObj objList, const Game_ctr &controller);		// �ړ����
	bool CheckObjType(OBJ_TYPE type);									// ��޼ު����������

	int keyGetRng;														// ��t�ڰѐ�
	int inputFram;														// �����ڰѐ�

	MAP_ID id;
};
