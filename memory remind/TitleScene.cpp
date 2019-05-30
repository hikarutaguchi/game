#include <DxLib.h>
#include "TitleScene.h"
#include "SelectScene.h"
#include "Game_ctr.h"
#include "EditScene.h"
#include "ImageMng.h"
#include "Obj.h"
#include "Fader.h"

#define PI 3.141592

TitleScene::TitleScene()
{
	Init();
}


TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Updata(unique_Base own, Game_ctr & controller)
{
	timeCnt++;
	for (int i = 0; i < CONTROLLER_INPUT_MAX; i++)
	{
		for (int j = 0; j < CONTROLLER_MAX; j++)
		{
			if (controller.GetCtr(i, (P_TYPE)j) == PAD_PUSH)
			{
				StopSoundMem(bgm);
				if (CheckSoundMem(seNextButton) == 0)
				{
					PlaySoundMem(seNextButton, DX_PLAYTYPE_BACK);	//ƒ{ƒ^ƒ“‚Ì‰¹
				}
				lpFader.SetFadeOut(4);
			}
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

	if (titleLogoCnt <= 256)	titleLogoCnt++;

	for (int i = 0; i < 4; i++)
	{
		if (cloud[i].Cnt >= SCREEN_SIZE_X + 400)
		{
			if (GetRand(3) == 0) cloud[i].visivle = false;
			cloud[i].getID = GetRand(19);
			cloud[i].High = GetRand(400);
			cloud[i].speed = GetRand(3) + 1;
			cloud[i].Cnt = 0;
		}
		cloud[i].Cnt += cloud[i].speed;
	}
	animCnt += 10;
	lpFader.Updata();
	Draw();
	return std::move(own);
}

int TitleScene::Init(void)
{
	titleLogoCnt = 0;

	for (int i = 0; i < 4; i++)
	{
		cloud[i].Cnt = SCREEN_SIZE_X + 397 + i;
		cloud[i].getID = 0;
		cloud[i].High = 0;
		cloud[i].speed = 1;
		cloud[i].visivle = true;
	}
	lpImageMng.GetID("image/cloud_s.png", VECTOR2(400, 200), VECTOR2(2, 10));

	bgm = LoadSoundMem("sound/titleScene/bgm_title.mp3");

	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);

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
	DrawGraph(0, 0, lpImageMng.GetID("image/titleBack_Sky.png")[0], true);

	if (cloud[0].visivle)	DrawGraph(cloud[0].Cnt - 400, cloud[0].High + (20 * sin(PI * 2 / 180 * timeCnt)), lpImageMng.GetID("image/cloud_s.png")[cloud[0].getID], true);
	if (cloud[1].visivle)	DrawGraph(SCREEN_SIZE_X - cloud[1].Cnt, cloud[1].High + (20 * sin(PI * 2 / 180 * timeCnt)), lpImageMng.GetID("image/cloud_s.png")[cloud[1].getID], true);
	if (cloud[2].visivle)	DrawGraph(cloud[2].Cnt - 400, cloud[2].High + (20 * sin(PI * 2 / 180 * timeCnt)), lpImageMng.GetID("image/cloud_s.png")[cloud[2].getID], true);
	if (cloud[3].visivle)	DrawGraph(SCREEN_SIZE_X - cloud[3].Cnt, cloud[3].High + (20 * sin(PI * 2 / 180 * timeCnt)), lpImageMng.GetID("image/cloud_s.png")[cloud[3].getID], true);

	DrawGraph(0, 0, lpImageMng.GetID("image/titleBack.png")[0], true);

	if ((titleLogoCnt <= 256) && (CheckSoundMem(seNextButton) == 0))
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs((int)(titleLogoCnt % 640)));
		DrawGraph(200, titleLogoCnt - 56, lpImageMng.GetID("image/titles.png")[0], true);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawGraph(200, 200 + (10 * sin(PI * 2 / 180 * timeCnt)), lpImageMng.GetID("image/titles.png")[0], true);
	}

	if (CheckSoundMem(seNextButton) == 0)
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs((int)(animCnt % 640) - 256));
	}
	DrawGraph(150, 700, lpImageMng.GetID("image/titlebutton.png")[0], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	lpFader.Draw();
	ScreenFlip();
}
