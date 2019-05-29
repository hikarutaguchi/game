#include "DxLib.h"
#include "Bomb.h"
#include "MapCtl.h"
#include "Game_ctr.h"
#include "classObj.h"

Bomb::Bomb(VECTOR2 setupPos, unsigned int length, VECTOR2 drawOffset) :Obj(drawOffset)
{
	//Init("image/bomb.png", VECTOR2(40 / 2,  140 / 7), VECTOR2(2, 7), setupPos);
	//InitAnim();
	//SetAnim("�ʏ�");
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
	AddAnim("�ʏ�",		0, 0, 2, 6, true );
	AddAnim("����",		1, 0, 7, 3, false);
	AddAnim("���ő҂�", 0, 2, 1, 1, false);
	return true;
}

bool Bomb::CheckDeth(void)
{
	if (GetAnim() == "���ő҂�")
	{
		return animEndFlag;
	}
	return false;
}

bool Bomb::CheckObjType(OBJ_TYPE type)
{
	//�������Ƃ���񂪓����Ȃ�^����������U
	return (type == OBJ_BOMB);
}
