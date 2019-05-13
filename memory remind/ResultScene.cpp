#include <DxLib.h>
#include "ResultScene.h"
#include "TitleScene.h"
#include "Game_ctr.h"
#include "ImageMng.h"
#include "Obj.h"
#include "Player.h"

ResultScene::ResultScene()
{
	Init();
}

ResultScene::~ResultScene()
{
}

unique_Base ResultScene::Updata(unique_Base own, const Game_ctr & controller)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		killPoint[i] = 1;
		goalPoint[i] = 1;
		totalPoint[i] = killPoint[i] + goalPoint[i];
	}

	//‡ˆÊˆ—
	

	for (int i = 0; i < GetJoypadNum(); i++)
	{
		Pad[i] = GetJoypadInputState(DX_INPUT_PAD1 + i);
		if ((Pad[i] & PAD_INPUT_1) && ((Pad[i] & PAD_INPUT_3)))
		{
			return std::make_unique<TitleScene>();
		}
	}
	return std::move(own);
}


int ResultScene::Init(void)
{
	holdbox = 0;
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		killPoint[i] = 0;
		goalPoint[i] = 0;
		totalPoint[i] = 0;
		ranking[i] = 0;
	}
	padFlag = false;
	if (!objList)
	{
		//µÌÞ¼Þª¸Ä‚Åtrue,false‚ª•Ô‚é
		objList = std::make_shared<sharedObjList>();
	}

	objList->clear();
	Draw();
	return 0;
}

void ResultScene::Draw()
{
	ClsDrawScreen();
	DrawGraph(0, 0, lpImageMng.GetID("image/akuma.png")[0], true);
	ScreenFlip();
}
