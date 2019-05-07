#include <DxLib.h>
#include "SelectScene.h"
#include "TitleScene.h"
#include "Game_ctr.h"
#include "EditScene.h"
#include "ImageMng.h"
#include "Obj.h"


SelectScene::SelectScene()
{
	Init();

}


SelectScene::~SelectScene()
{
}

unique_Base SelectScene::Updata(unique_Base own, const Game_ctr & controller)
{
	for (int i = 0; i < GetJoypadNum(); i++)
	{
		Pad[i] = GetJoypadInputState(DX_INPUT_PAD1 + i);
		if ((Pad[i] & PAD_INPUT_4) && ((Pad[i] & PAD_INPUT_2)))
		{
			return std::make_unique<EditScene>();
		}
	}
	return std::move(own);
}

int SelectScene::Init(void)
{
	lpImageMng.GetID("image/button_UI.png", VECTOR2(300, 64), VECTOR2(2, 3));		//プレイヤーのフレームを読み込み
	padFlag = false;
	if (!objList)
	{
		//ｵﾌﾞｼﾞｪｸﾄでtrue,falseが返る
		objList = std::make_shared<sharedObjList>();
	}

	objList->clear();
	Draw();
	return 0;
}

void SelectScene::Draw()
{
	ClsDrawScreen();
	DrawGraph(0, 0, lpImageMng.GetID("image/modeselect.png")[0], true);
	DrawGraph(500, 50, lpImageMng.GetID("image/button_UI.png")[2], true);
	DrawGraph(850, 50, lpImageMng.GetID("image/button_UI.png")[4], true);
	ScreenFlip();
}
