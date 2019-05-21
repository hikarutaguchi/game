#include <DxLib.h>
#include "TitleScene.h"
#include "SelectScene.h"
#include "Game_ctr.h"
#include "EditScene.h"
#include "ImageMng.h"
#include "Obj.h"
#include "Fader.h"

TitleScene::TitleScene()
{
	Init();
}


TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Updata(unique_Base own, Game_ctr & controller)
{



	for (int i = 0; i < CONTROLLER_INPUT_MAX; i++)
	{
		if (controller.GetCtr(i, CONTROLLER_P1) == PAD_PUSH)
		{
			StopSoundMem(titleBgm);
			PlaySoundMem(seNextButton, DX_PLAYTYPE_BACK);	//ƒ{ƒ^ƒ“‚Ì‰¹
			lpFader.SetFadeOut(4);
		}
	}

	if (fadeFinish)
	{
		if (lpFader.GetFadeState() == FADE_OUT_END)
		{
			return std::make_unique<SelectScene>();
		}
	}

	if (lpFader.GetFadeState() == FADE_OUT_END)
	{
		lpFader.SetFadeIn(8);
		fadeFinish = true;
	}

	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->UpData(objList, controller);
	}
	animCnt += 10;
	lpFader.Updata();
	Draw();
	return std::move(own);
}

int TitleScene::Init(void)
{
	titleBgm = LoadSoundMem("sound/titleScene/bgm_title.mp3");

	PlaySoundMem(titleBgm, DX_PLAYTYPE_LOOP);

	seNextButton = LoadSoundMem("sound/titleScene/se_next.mp3");

	padFlag = false;
	if (!objList)
	{
		//µÌÞ¼Þª¸Ä‚Åtrue,false‚ª•Ô‚é
		objList = std::make_shared<sharedObjList>();
	}

	objList->clear();
	return 0;
}

void TitleScene::Draw()
{
	fadeFinish = true;
	ClsDrawScreen();
	DrawGraph(0, 0, lpImageMng.GetID("image/title.png")[0], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs((int)(animCnt % 640) - 256));
	DrawGraph(150, 700, lpImageMng.GetID("image/titlebutton.png")[0], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	lpFader.Draw();
	ScreenFlip();
}
