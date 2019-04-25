#include <DxLib.h>
#include "Player.h"
#include "ImageMng.h"


Player::Player()
{
	InitAnim();
	ClsDrawScreen();
	Init("image/slime.png", VECTOR2(64, 100), VECTOR2(4, 4));
	Obj::Draw();
	GetAnim() == "ˆÚ“®";
	ScreenFlip();
}


Player::~Player()
{
}

bool Player::InitAnim(void)
{
	AddAnim("’âŽ~", 0, 0, 2, 6, true);
	AddAnim("ˆÚ“®", 0, 2, 2, 6, true);
	SetAnim("ˆÚ“®");
	return true;
}

bool Player::CheckObjType(OBJ_TYPE type)
{
	return false;
}
