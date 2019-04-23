#include "DxLib.h"
#include "VECTOR2.h"
#include "TitleScene.h"
#include "ModeScene.h"
#include "SceneMng.h"

SceneMng::SceneMng()
{
	SysInit();
}



SceneMng::~SceneMng()
{
}

void SceneMng::Run(void)
{
	activeScene = std::make_unique<TitleScene>();
	// ---------- ｹﾞｰﾑﾙｰﾌﾟ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//ClsDrawScreen();
		//VECTOR2 tmp1(0, 0);
		//VECTOR2 tmp2(0, GAME_SCREEN_SIZE_Y);
		////VECTOR2 offset(lpSceneMng.GetDrawOffset());
		//for (; tmp1.x <= GAME_SCREEN_SIZE_X; tmp1.x += CHIP_SIZE)
		//{
		//	tmp2.x = tmp1.x;
		//	DrawLine(tmp1/* + offset*/, tmp2/* + offset*/, 0xffffff, true);
		//}
		//tmp1 = VECTOR2(0, 0);
		//tmp2.x = GAME_SCREEN_SIZE_X;

		//for (; tmp1.y <= GAME_SCREEN_SIZE_Y; tmp1.y += CHIP_SIZE)
		//{
		//	tmp2.y = tmp1.y;
		//	DrawLine(tmp1/* + offset*/, tmp2/* + offset*/, 0xffffff, true);
		//}
		//ScreenFlip();
		//gameCtr->UpDate();			//キー情報取得
		if (CheckHitKey(KEY_INPUT_SPACE) != 0)
		{
			std::make_unique<ModeScene>();
		}
		//activeScene = activeScene->Update(std::move(activeScene), *gameCtr);
	}
}

VECTOR2 SceneMng::GetScreenSize(void)
{
	return VECTOR2(SCREEN_SIZE_X, SCREEN_SIZE_Y);
}

bool SceneMng::SetDrawOffset(VECTOR2 vec)
{
	drawOffset = vec;
	return true;
}

const VECTOR2 & SceneMng::GetDrawOffset(void)
{
	return SceneMng::drawOffset;
}

bool SceneMng::SysInit(void)
{
	// ｼｽﾃﾑ処理	
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);								// true:window　false:ﾌﾙｽｸﾘｰﾝ
	if (DxLib_Init() == -1) return false;				// DXﾗｲﾌﾞﾗﾘ初期化処理
	SetDrawScreen(DX_SCREEN_BACK);						// ひとまずﾊﾞｯｸﾊﾞｯﾌｧに描画
	//gameCtr = std::make_unique<GameCtr>();

	return true;
}

int DrawLine(VECTOR2 vec1, VECTOR2 vec2, unsigned int Color, int Thickness)
{
	DxLib::DrawLine(vec1.x, vec1.y, vec2.x, vec2.y, Color, Thickness);
	return 0;
}

