#include <DxLib.h>
#include "Player.h"
#include "ImageMng.h"


Player::Player()
{
	InitAnim();
	ClsDrawScreen();
	Init("image/slime.png", VECTOR2(64, 100), VECTOR2(4, 4));
	Obj::Draw();
	GetAnim() == "�ړ�";
	ScreenFlip();
}


Player::~Player()
{
}

bool Player::InitAnim(void)
{
	AddAnim("��~", 0, 0, 2, 6, true);
	AddAnim("�ړ�", 0, 2, 2, 6, true);
	SetAnim("�ړ�");
	return true;
}

bool Player::CheckObjType(OBJ_TYPE type)
{
	return false;
}
