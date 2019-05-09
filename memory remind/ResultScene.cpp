#include <DxLib.h>
#include "ResultScene.h"
#include "TitleScene.h"
#include "Game_ctr.h"
#include "ImageMng.h"
#include "Obj.h"

ResultScene::ResultScene()
{
	Init();
}

ResultScene::~ResultScene()
{
}

unique_Base ResultScene::Updata(unique_Base own, const Game_ctr & controller)
{
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
