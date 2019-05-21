#include <DxLib.h>
#include "ResultScene.h"
#include "TitleScene.h"
#include "Game_ctr.h"
#include "ImageMng.h"
#include "Obj.h"
#include "Player.h"
#include "Fader.h"

ResultScene::ResultScene()
{
	Init();
}

ResultScene::~ResultScene()
{
}

unique_Base ResultScene::Updata(unique_Base own, Game_ctr & controller)
{
	if (!fadeFinish)
	{
		if (lpFader.GetFadeState() == FADE_OUT_END)
		{
			lpFader.SetFadeIn(8);
			fadeFinish = true;
		}
	}

	if (bGetCtr == PAD_FREE)
	{
		if (controller.GetCtr(INPUT_BUTTON_A, CONTROLLER_P1) == PAD_PUSH)
		{
			lpFader.SetFadeOut(8);
		}
	}
	if (fadeFinish)
	{
		if (lpFader.GetFadeState() == FADE_OUT_END)
		{
			return std::make_unique<TitleScene>();
		}
	}

	bGetCtr = controller.GetCtr(INPUT_BUTTON_A, CONTROLLER_P1);

	lpFader.Updata();
	Draw();
	return std::move(own);
}


int ResultScene::Init(void)
{
	fadeFinish = false;
	padFlag = false;
	if (!objList)
	{
		//µÌÞ¼Þª¸Ä‚Åtrue,false‚ª•Ô‚é
		objList = std::make_shared<sharedObjList>();
	}

	objList->clear();
	return 0;
}

void ResultScene::Draw()
{
	ClsDrawScreen();
	DrawGraph(0, 0, lpImageMng.GetID("image/akuma.png")[0], true);
	lpFader.Draw();
	ScreenFlip();
}
