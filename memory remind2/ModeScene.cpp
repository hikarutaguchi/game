#include "ModeScene.h"



ModeScene::ModeScene()
{
	ClsDrawScreen();
	DrawBox(0, 0, 200, 200, 0xffff0, true);
	if (CheckHitKey(KEY_INPUT_A) != 0)
	{
<<<<<<< HEAD
		//asd
=======
>>>>>>> ea93142a8a04ca9fd7a109912d2cc546108e880c
		std::make_unique<GameScene>();
	}
	ScreenFlip();
}


ModeScene::~ModeScene()
{
}
