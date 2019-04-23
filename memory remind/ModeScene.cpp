#include "ModeScene.h"



ModeScene::ModeScene()
{
	ClsDrawScreen();
		VECTOR2 tmp1(0, 0);
		VECTOR2 tmp2(0, GAME_SCREEN_SIZE_Y);
		//VECTOR2 offset(lpSceneMng.GetDrawOffset());
		for (; tmp1.x <= GAME_SCREEN_SIZE_X; tmp1.x += CHIP_SIZE)
		{
			tmp2.x = tmp1.x;
			DrawLine(tmp1/* + offset*/, tmp2/* + offset*/, 0xffffff, true);
		}
		tmp1 = VECTOR2(0, 0);
		tmp2.x = GAME_SCREEN_SIZE_X;

		for (; tmp1.y <= GAME_SCREEN_SIZE_Y; tmp1.y += CHIP_SIZE)
		{
			tmp2.y = tmp1.y;
			DrawLine(tmp1/* + offset*/, tmp2/* + offset*/, 0xffffff, true);
		}
		ScreenFlip();
}


ModeScene::~ModeScene()
{
}
