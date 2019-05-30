#include <DxLib.h>
#include "ResultScene.h"
#include "TitleScene.h"
#include "Game_ctr.h"
#include "ImageMng.h"
#include "Obj.h"
#include "Fader.h"
#include "CntMng.h"

#define FLAME_RATE 5

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

const VECTOR2 & ResultScene::PointUpDrawPos()
{
	if (lpCntMng.GoalGetCnt() != 0)
	{
		if (Poscnt < (lpCntMng.GoalGetCnt() * 75))
		{
			resultCnt++;

			if (resultCnt % FLAME_RATE == 0)
			{
				FlameFlag = true;
			}
			else
			{
				FlameFlag = false;
			}
		}
		else
		{
			FlameFlag = false;
		}
	}
	if (FlameFlag)
	{
		PointPos = { 0, Poscnt++ };
	}

	return PointPos;
}

const VECTOR2 & ResultScene::PointUpDrawPos2()
{
	if (lpCntMng.GoalGetCnt2() != 0)
	{
		if (Poscnt2 < (lpCntMng.GoalGetCnt2() * 75))
		{
			resultCnt2++;

			if (resultCnt2 % FLAME_RATE == 0)
			{
				FlameFlag2 = true;
			}
			else
			{
				FlameFlag2 = false;
			}
		}
		else
		{
			FlameFlag2 = false;
		}
	}
	if (FlameFlag2)
	{
		PointPos2 = { 0, Poscnt2++ };
	}

	return PointPos2;
}


int ResultScene::Init(void)
{
	fadeFinish = false;
	FlameFlag = false;
	FlameFlag2 = false;

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
#ifdef _DEBUG
	DrawFormatString(0, 90, 0xffff00, "point.x= %d", PointUpDrawPos().x);
	DrawFormatString(0, 105, 0xffff00, "point.y= %d", PointUpDrawPos().y);
	DrawFormatString(0, 120, 0xffff00, "resultCnt= %d", resultCnt % 10);
	DrawFormatString(0, 135, 0xffff00, "Poscnt= %d", Poscnt);
	DrawFormatString(0, 150, 0xffff00, "resultFlag= %d", (int)FlameFlag);

	DrawFormatString(0, 200, 0xffff00, "point2.x= %d", PointUpDrawPos2().x);
	DrawFormatString(0, 215, 0xffff00, "point2.y= %d", PointUpDrawPos2().y);
	DrawFormatString(0, 230, 0xffff00, "resultCnt2= %d", resultCnt2 % 10);
	DrawFormatString(0, 245, 0xffff00, "Poscnt2= %d", Poscnt2);
	DrawFormatString(0, 260, 0xffff00, "resultFlag2= %d", (int)FlameFlag2);
#endif
	/*DrawGraph(0, 0, lpImageMng.GetID("image/akuma.png")[0], true);*/

	switch (lpSelCur.GetCharData(CONTROLLER_P1))
	{
	case 1:
		DrawBox(180, 600 - PointUpDrawPos().y, 243, 600, 0xff0000, true);
		DrawGraph(180, 500 - PointUpDrawPos().y, lpImageMng.GetID("image/slimes.png", VECTOR2(64, 100), VECTOR2(4, 4))[1], true);

		break;

	case 2:
		DrawBox(180, 600 - PointUpDrawPos().y, 243, 600, 0xff0000, true);
		DrawGraph(180, 500 - PointUpDrawPos().y, lpImageMng.GetID("image/skeleton.png", VECTOR2(64, 100), VECTOR2(4, 4))[0], true);
		break;

	case 3:
		DrawBox(180, 600 - PointUpDrawPos().y, 243, 600, 0xff0000, true);
		DrawGraph(180, 500 - PointUpDrawPos().y, lpImageMng.GetID("image/Carbuncle.png", VECTOR2(64, 100), VECTOR2(4, 4))[0], true);
		break;
	}

	switch (lpSelCur.GetCharData(CONTROLLER_P2))
	{
	case 1:
		DrawBox(540, 600 - PointUpDrawPos2().y, 603, 600, 0xff0f00, true);
		DrawGraph(540, 500 - PointUpDrawPos2().y, lpImageMng.GetID("image/slimes.png", VECTOR2(64, 100), VECTOR2(4, 4))[1], true);
		break;

	case 2:
		DrawBox(540, 600 - PointUpDrawPos2().y, 603, 600, 0xff0f00, true);
		DrawGraph(540, 500 - PointUpDrawPos2().y, lpImageMng.GetID("image/skeleton.png", VECTOR2(64, 100), VECTOR2(4, 4))[0], true);
		break;

	case 3:
		DrawBox(540, 600 - PointUpDrawPos2().y, 603, 600, 0xff0f00, true);
		DrawGraph(540, 500 - PointUpDrawPos2().y, lpImageMng.GetID("image/Carbuncle.png", VECTOR2(64, 100), VECTOR2(4, 4))[0], true);
		break;
	}

	lpFader.Draw();
	ScreenFlip();
}
