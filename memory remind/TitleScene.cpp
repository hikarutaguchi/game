#include <DxLib.h>
#include "TitleScene.h"
#include "Game_ctr.h"
#include "EditScene.h"
#include "ImageMng.h"
#include "Obj.h"

TitleScene::TitleScene()
{
	Init();
}


TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Updata(unique_Base own, const Game_ctr & controller)
{
	for (int i = 0; i < GetJoypadNum(); i++)
	{
		Pad[i] = GetJoypadInputState(DX_INPUT_PAD1 + i);
		for (int j = 0; j < 28; j++)
		{
			if ((Pad[i] & (1 << j)))
			{
				if (!padFlag)
				{
					return std::make_unique<EditScene>();
				}
			}
		}
	}

	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->UpData(objList, controller);
	}

	return std::move(own);
}

int TitleScene::Init(void)
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

void TitleScene::Draw()
{
	ClsDrawScreen();
	DrawGraph(0, 0, lpImageMng.GetID("image/title.png")[0], true);
	DrawGraph(100, 700, lpImageMng.GetID("image/titlebutton.png")[0], true);
	ScreenFlip();
}
