#pragma once
#include "Obj.h"

class Player :
	public Obj
{
public:
	Player();
	~Player();
	bool InitAnim(void);
private:
	bool CheckObjType(OBJ_TYPE type);
};

