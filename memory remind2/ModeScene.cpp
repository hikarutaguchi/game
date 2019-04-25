#include "ModeScene.h"
#include "Player.h"


ModeScene::ModeScene()
{
	ClsDrawScreen();
	DrawBox(0, 0, 200, 200, 0xffff0, true);

	if (CheckHitKey(KEY_INPUT_A) != 0)
	{
		//std::make_unique<GameScene>();
		std::make_unique<Player>();
	}
	ScreenFlip();
}


ModeScene::~ModeScene()
{
}
