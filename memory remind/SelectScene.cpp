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

unique_Base SelectScene::Updata(unique_Base own, Game_ctr & controller)
{
	if (bGetCtr == PAD_FREE)
	{
		if (controller.GetCtr(CONTROLLER_1P_INPUT_BUTTON_A) == PAD_PUSH)
		{
			return std::make_unique<EditScene>();
		}
	}

	bGetCtr = controller.GetCtr(CONTROLLER_1P_INPUT_BUTTON_A);

	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->UpData(objList, controller);
	}

	return std::move(own);
}

int SelectScene::Init(void)
{
	bGetCtr = PAD_MAX;
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
