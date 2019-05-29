#include <DxLib.h>
#include "SceneMng.h"
#include "GameScene.h"
#include "EditScene.h"
#include "MapCtl.h"
#include "Player.h"
#include "Game_ctr.h"
#include "ImageMng.h"
#include "ResultScene.h"
#include "CntMng.h"
#include "Fader.h"
#include "ScreenShake.h"

GameScene::GameScene()
{
	Init();

	hpPos_TBL = {
		hpPos[ONE_HP] = {0,0},
		hpPos[TWO_HP] = {64,0},
		hpPos[THREE_HP] = {128,0},
		hpPos[FOUR_HP] = {192,0},
	};

	hpFlag = {
		true,
		true,
		true,
		false,
	};
}


GameScene::~GameScene()
{

}

unique_Base GameScene::Updata(unique_Base own, Game_ctr & controller)
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
			SceneCnt += 1;
			lpCntMng.SetCnt(SceneCnt);
			return std::make_unique<EditScene>();
		}
	}

	bGetCtr = controller.GetCtr(INPUT_BUTTON_A, CONTROLLER_P1);

	lpMapCtl.Updata();

	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->UpData(objList, controller);
	}
	//叙述関数(ﾌﾟﾚﾃﾞｨｹｰﾄ)とremove_ifを用いる

	objList->remove_if([](sharedObj& obj) {return obj->CheckDeth(); });
	GameDraw();
	lpFader.Updata();
	lpScreenShake.UpData();
	return std::move(own);
}

bool GameScene::GameDraw(void)
{

	//ｿｰﾃｨﾝｸﾞ　y座標を基準に小さい順から描画する
	//ｵﾌﾞｼﾞｪｸﾄが登録されているobjLis t登録している順をいじっていいか、どうか
	//後に書くものは形が決まっている。ｿｰﾄに必ず必要なものは2つのｵﾌﾞｼﾞｪｸﾄがいる１つじゃ入れ替えられないので
	//uniqueを参照でもらってy座標をくらべて1つ目のほうが小さかったら真を返す

	(*objList).sort([](sharedObj &pos1, sharedObj &pos2) {return ((*pos1).GetPos().y) < ((*pos2).GetPos().y); });


	ClsDrawScreen();
	lpMapCtl.Draw(false);

	//　ｲﾃﾚｰﾀｰを普通に書いた場合
	/*for (std::list<Obj*>::iterator itr = objList.begin(); itr != objList.end(); itr++)*/
	//型推論を用いて書いた場合　 autoを用いて型を予想

	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->Draw();
		(*itr)->Draw2();
	}

	//for (auto itr2 = objList2->begin(); itr2 != objList2->end(); itr2++)
	//{
	//	(*itr2)->Draw2();
	//}

	//for (auto itr: objList)	//開始位置と終端位置が分かればautoでいける
	//{
	//	itr->Draw();
	//}

	//for (auto &data : (*objList))
	//{
	//	data->Draw(false);
	//}
	//auto fnc = [] {
	//	ClsDrawScreen();	ラムダ式
	//	lpMapCtl.Draw();
	//	ScreenFlip();
	//}
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
	//std::for_each((objList)->begin(), (objList)->end(), [](std::shared_ptr<Obj> &itr) {itr->Draw(); });

	DrawGraph(SCREEN_SIZE_X / 2 - 100, 0, lpImageMng.GetID("image/kannbann.png")[0], true);

	//プレイヤーのフレームを表示
	DrawGraph(0, 0, lpImageMng.GetID("image/flame.png")[0], true);
	DrawGraph(SCREEN_SIZE_X - 120, 0, lpImageMng.GetID("image/flame.png")[1], true);
	DrawGraph(0, SCREEN_SIZE_Y - 120, lpImageMng.GetID("image/flame.png")[2], true);
	DrawGraph(SCREEN_SIZE_X - 120, SCREEN_SIZE_Y - 120, lpImageMng.GetID("image/flame.png")[3], true);

	//時間表示

	timeCnt--;

	if (timeCnt <= 0)
	{
		startCnt--;
	}
	else
	{
		DrawGraph(SCREEN_SIZE_X / 2 - 75, 45, lpImageMng.GetID("image/number.png")[timeCnt / 6000 % 10], true);
		DrawGraph(SCREEN_SIZE_X / 2 - 75 + 50, 45, lpImageMng.GetID("image/number.png")[timeCnt / 600 % 10], true);
		DrawGraph(SCREEN_SIZE_X / 2 - 75 + 100, 45, lpImageMng.GetID("image/number.png")[timeCnt / 60 % 10], true);
	}

	if (startCnt < 0)
	{
		timeCnt = 10800;
		startCnt = 61;
	}
	else if (startCnt > 61)
	{
		DrawGraph(SCREEN_SIZE_X / 2 - 75 + 50, 45, lpImageMng.GetID("image/number.png")[startCnt / 60 % 10], true);
	}
	else if (startCnt < 60)
	{
		DrawGraph(0, 0, lpImageMng.GetID("image/start.png")[0], true);
	}

	////サウンド処理
	if (startCnt == 240)
	{
		PlaySoundMem(three, DX_PLAYTYPE_BACK);
	}
	else if (startCnt == 180)
	{
		PlaySoundMem(two, DX_PLAYTYPE_BACK);
	}
	else if (startCnt == 120)
	{
		PlaySoundMem(one, DX_PLAYTYPE_BACK);
	}
	else if (startCnt == 60)
	{
		PlaySoundMem(start, DX_PLAYTYPE_BACK);
	}
	if (timeCnt == 3670)
	{
		PlaySoundMem(nokori, DX_PLAYTYPE_BACK);
	}
	if (timeCnt == 3631)
	{
		PlaySoundMem(sixty, DX_PLAYTYPE_BACK);
	}
	if (timeCnt == 3600)
	{
		PlaySoundMem(byou, DX_PLAYTYPE_BACK);
	}

	auto as = 6/*lpPlayer.Life()*/;

	if (as == 8)
	{
		hpFlag[FOUR_HP] = true;
	}
	else if (as == 6)
	{
		hpFlag[FOUR_HP] = false;
	}
	else if (as == 4)
	{
		hpFlag[THREE_HP] = false;
	}
	else if (as == 2)
	{
		hpFlag[TWO_HP] = false;
	}
	else if (as == 0)
	{
		hpFlag[ONE_HP] = false;
	}

	for (int p = 0; p < CONTROLLER_MAX; p++)
	{
		for (int i = 0; i < MAX_HP; i++)
		{
			if (hpFlag[i] == true)
			{
				DrawGraph(hpPos_TBL[i].x + pPos[p].x, hpPos_TBL[i].y + pPos[p].y, lpImageMng.GetID("image/hp.png")[0], true);
			}
			else if (hpFlag[i] == false)
			{
				DrawGraph(hpPos_TBL[i].x + pPos[p].x, hpPos_TBL[i].y + pPos[p].y, lpImageMng.GetID("image/hp.png")[2], true);
			}
		}
		if (as == 7)
		{
			DrawGraph(hpPos_TBL[FOUR_HP].x + pPos[p].x, hpPos_TBL[FOUR_HP].y + pPos[p].y, lpImageMng.GetID("image/hp.png")[1], true);
		}
		else if (as == 5)
		{
			DrawGraph(hpPos_TBL[THREE_HP].x + pPos[p].x, hpPos_TBL[THREE_HP].y + pPos[p].y, lpImageMng.GetID("image/hp.png")[1], true);
		}
		else if (as == 3)
		{
			DrawGraph(hpPos_TBL[TWO_HP].x + pPos[p].x, hpPos_TBL[TWO_HP].y + pPos[p].y, lpImageMng.GetID("image/hp.png")[1], true);
		}
		else if (as == 1)
		{
			DrawGraph(hpPos_TBL[ONE_HP].x + pPos[p].x, hpPos_TBL[ONE_HP].y + pPos[p].y, lpImageMng.GetID("image/hp.png")[1], true);
		}
	}

	lpFader.Draw();
	ScreenFlip();
	return true;
}

int GameScene::Init(void)
{
	pPos[CONTROLLER_P1] = { 120,30 };
	pPos[CONTROLLER_P2] = { SCREEN_SIZE_X - 120 - (64 * 4),30 };
	pPos[CONTROLLER_P3] = { 120,SCREEN_SIZE_Y - 90 };
	pPos[CONTROLLER_P4] = { SCREEN_SIZE_X - 120 - (64 * 4),SCREEN_SIZE_Y - 90 };

	fadeFinish = false;
	timeCnt = 0;
	startCnt = 241;
	padFlag = false;
	if (!objList)
	{
		//ｵﾌﾞｼﾞｪｸﾄでtrue,falseが返る
		objList = std::make_shared<sharedObjList>();
	}
	objList->clear();
	lpImageMng.GetID("image/flame.png", VECTOR2(120, 120), VECTOR2(2, 2));		// プレイヤーのフレームを読み込み
	lpImageMng.GetID("image/number.png", VECTOR2(50, 50), VECTOR2(10, 1));		// ナンバー
	lpImageMng.GetID("image/hp.png", VECTOR2(64, 64), VECTOR2(3, 1));			// HP

	lpSceneMng.SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));
	lpMapCtl.SetUp(VECTOR2(GAME_SCREEN_SIZE_X, GAME_SCREEN_SIZE_Y), VECTOR2(CHIP_SIZE, CHIP_SIZE), SceneMng::GetInstance().GetDrawOffset());
	lpMapCtl.MapLoad(objList, false);

	//サウンド
	bgm = LoadSoundMem("sound/gameScene/bgm_game.mp3");
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
	one = LoadSoundMem("sound/gameScene/voice_1.mp3");
	two = LoadSoundMem("sound/gameScene/voice_2.mp3");
	three = LoadSoundMem("sound/gameScene/voice_3.mp3");
	sixty = LoadSoundMem("sound/gameScene/voice_60.mp3");
	byou = LoadSoundMem("sound/gameScene/voice_byou.mp3");
	nokori = LoadSoundMem("sound/gameScene/voice_nokori.mp3");
	stop = LoadSoundMem("sound/gameScene/voice_stop.mp3");
	start = LoadSoundMem("sound/gameScene/voice_start.mp3");

	return true;
}