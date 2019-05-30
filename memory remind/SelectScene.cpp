#include <DxLib.h>
#include "SelectScene.h"
#include "TitleScene.h"
#include "Game_ctr.h"
#include "EditScene.h"
#include "ImageMng.h"
#include "Obj.h"
#include "SelectCur.h"
#include "Fader.h"


SelectScene::SelectScene()
{
	Init();
}


SelectScene::~SelectScene()
{
}

unique_Base SelectScene::Updata(unique_Base own, Game_ctr & controller)
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
		if ((lpSelCur.GetCharFlag(CONTROLLER_P1) == true) && (lpSelCur.GetCharFlag(CONTROLLER_P2) == true))
		{
			if (controller.GetCtr(INPUT_BUTTON_A, CONTROLLER_P1) == PAD_PUSH)
			{
				lpFader.SetFadeOut(4);
			}
		}
	}
	if (fadeFinish)
	{
		if (lpFader.GetFadeState() == FADE_OUT_END)
		{
			StopSoundMem(bgm);
			return std::make_unique<EditScene>();
		}
	}

	bGetCtr = controller.GetCtr(INPUT_BUTTON_A, CONTROLLER_P1);

	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->UpData(objList, controller);
	}
	lpFader.Updata();
	lpSelCur.MoveCur(controller);
	return std::move(own);
}

int SelectScene::Init(void)
{
	fadeFinish = false;
	bGetCtr = PAD_MAX;
	lpImageMng.GetID("image/button_UI.png", VECTOR2(300, 64), VECTOR2(2, 3));		//プレイヤーのフレームを読み込み
	padFlag = false;
	if (!objList)
	{
		//ｵﾌﾞｼﾞｪｸﾄでtrue,falseが返る
		objList = std::make_shared<sharedObjList>();
	}

	objList->clear();

	bgm = LoadSoundMem("sound/selectScene/bgm_select.mp3");
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);

	//Draw();
	return 0;
}

void SelectScene::Draw()
{
	//ClsDrawScreen();
	//DrawGraph(0, 0, lpImageMng.GetID("image/modeselect.png")[0], true);
	//DrawGraph(500, 50, lpImageMng.GetID("image/button_UI.png")[2], true);
	//DrawGraph(850, 50, lpImageMng.GetID("image/button_UI.png")[4], true);
	//ScreenFlip();
}
