#include <DxLib.h>
#include "SceneMng.h"
#include "ImageMng.h"
#include "EditScene.h"
#include "MapCtl.h"
#include "EditCursor.h"
#include "EditCursor2.h"
#include "Game_ctr.h"
#include "GameScene.h"
#include "CntMng.h"
#include "ResultScene.h"
#include "Fader.h"

EditScene::EditScene()
{
	Init();
}


EditScene::~EditScene()
{

}

unique_Base EditScene::Updata(unique_Base own, Game_ctr & controller)
{
	int a = lpCntMng.GetCnt();

	if (!fadeFinish)
	{
		if (lpFader.GetFadeState() == FADE_OUT_END)
		{
			lpFader.SetFadeIn(8);
			fadeFinish = true;
		}
	}

	if (lpCntMng.GetEditFlag() == true)
	{
		MapCtl::GetInstance().MapSave();
		lpFader.SetFadeOut(8);
		lpCntMng.SetEditFlag(false);
	}

	if (fadeFinish)
	{
		if (lpFader.GetFadeState() == FADE_OUT_END)
		{
			StopSoundMem(bgm);
			if (a <= 3)
			{
				return std::make_unique<GameScene>();
			}
			if (a > 3)
			{
				lpCntMng.SetCnt(-4);
				return std::make_unique<ResultScene>();
			}
		}
	}

	//if (controller.GetCtr(KEY_TYPE_NOW)[KEY_INPUT_F2]) //現在のｷｰ情報を取得
	//{
	//	//ﾛｰﾄﾞ
	//	if (MessageBox(NULL, "エディット内容をリセットしますか？", "確認ダイアログ", MB_OKCANCEL) == IDOK)	//返り値で帰ってきてる
	//	{
	//		Init();
	//	}
	//}

	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->UpData(objList, controller);
	}
	EditDraw();
	lpFader.Updata();
	return std::move(own);
}

bool EditScene::EditDraw(void)
{
	ClsDrawScreen();
	DrawGraph(0, 0, lpImageMng.GetID("image/game.png")[0], true);
	lpMapCtl.Draw(true);
	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->Draw();
	}

	VECTOR2 tmp1(0, 0);
	VECTOR2 tmp2(0, GAME_SCREEN_SIZE_Y);
	VECTOR2 offset(lpSceneMng.GetDrawOffset());
	for (; tmp1.x <= GAME_SCREEN_SIZE_X; tmp1.x += CHIP_SIZE)
	{
		tmp2.x = tmp1.x;
		DrawLine(tmp1 + offset, tmp2 + offset, 0xffffff, true);
	}
	tmp1 = VECTOR2(0, 0);
	tmp2.x = GAME_SCREEN_SIZE_X;

	for (; tmp1.y <= GAME_SCREEN_SIZE_Y; tmp1.y += CHIP_SIZE)
	{
		tmp2.y = tmp1.y;
		DrawLine(tmp1 + offset, tmp2 + offset, 0xffffff, true);
	}
	VECTOR2 pos = lpMapCtl.GetChipSize();
	/*for (int j = static_cast<int>(MAP_ID::BOMB); j < static_cast<int>(MAP_ID::MAX); j++)
	{
		DrawGraph( ( (Drawpos.x + j * pos.x) * 3 ), pos.x * 2, lpImageMng.GetID("image/map.png")[j], true);
	}*/
	Text();
	lpFader.Draw();
	ScreenFlip();
	return true;
}

void EditScene::Text()
{
	//int Color = GetColor(255, 255, 255);
	//VECTOR2 textpos = lpMapCtl.GetChipSize();
	//VECTOR2 Size = lpSceneMng.GetGameSize();
	//DrawString(CHIP_SIZE, CHIP_SIZE, "Z　or　Xで種類切り替え", Color);
	//DrawString(CHIP_SIZE * 12, 0, "使えるエディット一覧", Color);
	//DrawString(0, 580, "現在エディットのリセット	F2", Color);
	//DrawString( (Size.x / 2) - textpos.x * 2, 580, "エディット内容のロード	F5", Color);
	//DrawString(Size.x - textpos.x * 4, 580, "エディット内容のセーブ	F6", Color);
}

int EditScene::Init(void)
{
	bgm = LoadSoundMem("sound/editScene/bgm_edit.mp3");

	PlaySoundMem(bgm,DX_PLAYTYPE_LOOP);

	fadeFinish = false;
	bGetCtr = PAD_MAX;
	//ｼｰﾝが移ったらﾘｾｯﾄ
	if (!objList)
	{
		//ｵﾌﾞｼﾞｪｸﾄでtrue,falseが返る
		objList = std::make_shared<sharedObjList>();
	}
	objList->clear();

	SceneMng::GetInstance().SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));

	lpMapCtl.SetUp(VECTOR2(GAME_SCREEN_SIZE_X, GAME_SCREEN_SIZE_Y), VECTOR2(CHIP_SIZE, CHIP_SIZE), SceneMng::GetInstance().GetDrawOffset());
	ListObj_itr obj[4];
	for (int i = 0; i <= GetJoypadNum(); i++)
	{

		switch (i)
		{
		case 1:
			obj[0] = AddObjList()(objList, std::make_unique<EditCursor>(SceneMng::GetInstance().GetDrawOffset(), i));
			(*obj[0])->Init("image/yukas.png", VECTOR2(64, 64), VECTOR2(4, 3));
			break;
		case 2:
			obj[1] = AddObjList()(objList, std::make_unique<EditCursor2>(SceneMng::GetInstance().GetDrawOffset(), 1 + i));
			(*obj[1])->Init("image/yuka.png", VECTOR2(64, 64), VECTOR2(4, 3));
			break;
		default:
			break;
		}
	}

	if (lpCntMng.GetCnt() == 0)
	{
		MapCtl::GetInstance().MapLoadBase(objList, true);
	}
	else
	{
		MapCtl::GetInstance().MapLoad(objList, true);
	}

	return 0;
}

