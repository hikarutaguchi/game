#include "DxLib.h"
#include "Bomb.h"
#include "MapCtl.h"
#include "Game_ctr.h"
#include "classObj.h"

Bomb::Bomb(VECTOR2 setupPos, unsigned int length, VECTOR2 drawOffset) :Obj(drawOffset)
{
	//Init("image/bomb.png", VECTOR2(40 / 2,  140 / 7), VECTOR2(2, 7), setupPos);
	//InitAnim();
	//SetAnim("’Êí");
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
	AddAnim("’Êí",		0, 0, 2, 6, true );
	AddAnim("”š”­",		1, 0, 7, 3, false);
	AddAnim("Á–Å‘Ò‚¿", 0, 2, 1, 1, false);
	return true;
}

bool Bomb::CheckDeth(void)
{
	if (GetAnim() == "Á–Å‘Ò‚¿")
	{
		return animEndFlag;
	}
	return false;
}

bool Bomb::CheckObjType(OBJ_TYPE type)
{
	//‚¤‚¯‚Á‚Æ‚½î•ñ‚ª“¯‚¶‚È‚ç^‚¿‚ª‚Á‚½‚ç‹U
	return (type == OBJ_BOMB);
}
