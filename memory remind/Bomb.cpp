#include "DxLib.h"
#include "Bomb.h"
#include "MapCtl.h"
#include "Game_ctr.h"
#include "classObj.h"

Bomb::Bomb(VECTOR2 setupPos, unsigned int length, VECTOR2 drawOffset) :Obj(drawOffset)
{
	//Init("image/bomb.png", VECTOR2(40 / 2,  140 / 7), VECTOR2(2, 7), setupPos);
	//InitAnim();
	//SetAnim("通常");
	//count = 180;
}


Bomb::~Bomb()
{
}

void Bomb::SetMove(weekListObj objList, const Game_ctr & controller)
{
}

bool Bomb::InitAnim(void)
{
	AddAnim("通常",		0, 0, 2, 6, true );
	AddAnim("爆発",		1, 0, 7, 3, false);
	AddAnim("消滅待ち", 0, 2, 1, 1, false);
	return true;
}

bool Bomb::CheckDeth(void)
{
	if (GetAnim() == "消滅待ち")
	{
		return animEndFlag;
	}
	return false;
}

bool Bomb::CheckObjType(OBJ_TYPE type)
{
	//うけっとた情報が同じなら真ちがったら偽
	return (type == OBJ_BOMB);
}
