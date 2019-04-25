#include <DxLib.h>
#include "Player.h"
#include "ImageMng.h"


Player::Player()
{
	InitAnim();
	ClsDrawScreen();
	Init("image/slime.png", VECTOR2(64, 100), VECTOR2(4, 4));
	Obj::Draw();
	GetAnim() == "移動";
	ScreenFlip();
}


Player::~Player()
{
}

bool Player::InitAnim(void)
{
	AddAnim("停止", 0, 0, 2, 6, true);
	AddAnim("移動", 0, 2, 2, 6, true);
	SetAnim("移動");
	return true;
}

bool Player::CheckObjType(OBJ_TYPE type)
{
	return false;
}
