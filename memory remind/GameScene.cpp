#include <DxLib.h>
#include "SceneMng.h"
#include "GameScene.h"
#include "EditScene.h"
#include "MapCtl.h"
#include "Bomb.h"
#include "Game_ctr.h"


GameScene::GameScene()
{
	Init();
}


GameScene::~GameScene()
{

}

unique_Base GameScene::Updata(unique_Base own, const Game_ctr & controller)
{
	if (controller.GetCtr(KEY_TYPE_NOW)[KEY_INPUT_F1] & (~controller.GetCtr(KEY_TYPE_OLD)[KEY_INPUT_F1]))
	{
		return std::make_unique<EditScene>();
	}

	lpMapCtl.Updata();

	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->UpData(objList, controller);
	}
	//叙述関数(ﾌﾟﾚﾃﾞｨｹｰﾄ)とremove_ifを用いる

	objList->remove_if([](sharedObj& obj) {return obj->CheckDeth(); });
	GameDraw();
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
	}
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
	ScreenFlip();
	return true;
}

int GameScene::Init(void)
{
	if (!objList)
	{
		//ｵﾌﾞｼﾞｪｸﾄでtrue,falseが返る
		objList = std::make_shared<sharedObjList>();
	}
	objList->clear();
	lpSceneMng.SetDrawOffset( VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y) );
	lpMapCtl.SetUp( VECTOR2(GAME_SCREEN_SIZE_X, GAME_SCREEN_SIZE_Y) , VECTOR2(CHIP_SIZE, CHIP_SIZE), SceneMng::GetInstance().GetDrawOffset());
	lpMapCtl.MapLoad(objList, false);
	return true;
}

