#include <DxLib.h>
#include "SceneMng.h"
#include "GameScene.h"
#include "EditScene.h"
#include "MapCtl.h"
#include "PlayerMng.h"
#include "Game_ctr.h"
#include "ImageMng.h"
#include "ResultScene.h"
#include "CntMng.h"
#include "Fader.h"
#include "ScreenShake.h"

GameScene::GameScene()
{
	Init();
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

	if ((lpCntMng.GetGoalFlag(CONTROLLER_P1) == true) && (lpCntMng.GetGoalFlag(CONTROLLER_P2) == true))
	{
		StopSoundMem(bgm);
		lpFader.SetFadeOut(8);
		lpCntMng.GetGoalFlag(CONTROLLER_P1) = false;
		lpCntMng.GetGoalFlag(CONTROLLER_P2) = false;
	}

	if (fadeFinish)
	{
		if (lpFader.GetFadeState() == FADE_OUT_END)
		{
			SceneCnt += 1;
			lpCntMng.SetCnt(SceneCnt);
			lpPlayer.SetRestartHpFlag(true);
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
	DrawGraph(0, 0, lpImageMng.GetID("image/game.png")[0], true);
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

	// HP表示
	lpPlayer.HP_Draw();

#ifdef _DEBUG 
	DrawFormatString(0, 0, 0x0ffff0, "sDamage = %d", lpPlayer.GetSlimeDamageData());
	DrawFormatString(0, 15, 0x0ffff0, "nDamage = %d", lpPlayer.GetSkeletonDamageData());
	DrawFormatString(0, 30, 0x0ffff0, "cDamage = %d", lpPlayer.GetCarbuncleDamageData());
	DrawFormatString(0, 45, 0x0ffff0, "sDamage2 = %d", lpPlayer.GetSlimeDamageData2());
	DrawFormatString(0, 60, 0x0ffff0, "nDamage2 = %d", lpPlayer.GetSkeletonDamageData2());
	DrawFormatString(0, 75, 0x0ffff0, "cDamage2 = %d", lpPlayer.GetCarbuncleDamageData2());
	DrawFormatString(0, 90, 0x0ffff0, "restartHpFlag = %d", (int)lpPlayer.GetRestartHpFlag());
#endif

	lpFader.Draw();
	ScreenFlip();
	return true;
}

int GameScene::Init(void)
{
	fadeFinish = false;
	timeCnt = 0;
	startCnt = 241;

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