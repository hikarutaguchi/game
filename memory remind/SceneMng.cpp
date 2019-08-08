#include "DxLib.h"
#include "VECTOR2.h"
#include "SceneMng.h"
#include "ImageMng.h"
#include "EditCursor.h"
//#include "EditScene.h"
#include "TitleScene.h"
#include "MapCtl.h"
#include "PlayerMng.h"
#include "Game_ctr.h"
#include "ScreenShake.h"



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
	// ---------- �ް�ٰ��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		lpScreenShaker.PrepareShake();
		gameCtr->Updata();
		activeScene = activeScene->Updata(std::move(activeScene), *gameCtr);
		lpScreenShaker.UpdateShake();
	}

}

VECTOR2 SceneMng::GetScreenSize(void)
{
	return VECTOR2(SCREEN_SIZE_X, SCREEN_SIZE_Y);
}

VECTOR2 SceneMng::GetGameSize(void)
{
	return VECTOR2(GAME_SCREEN_SIZE_X, GAME_SCREEN_SIZE_Y);
}

bool SceneMng::SetDrawOffset(VECTOR2 vec)
{
	drawOffset = vec;
	return true;
}

const VECTOR2 & SceneMng::GetDrawOffset(void)
{
	return drawOffset;
}



bool SceneMng::DeleteObjList(std::list<Obj*>::iterator itr)
{
	//iterator��delete����̂́A���ނɱ�������̂Ɠ�������
	delete (*itr);
	return true;
}

bool SceneMng::SysInit(void)
{
	// ���я���
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);								// true:window�@false:�ٽ�ذ�
	SetWindowText("memory remind");
	if (DxLib_Init() == -1) return false;				// DXײ���؏���������
	SetDrawScreen(DX_SCREEN_BACK);						// �ЂƂ܂��ޯ��ޯ̧�ɕ`��
	gameCtr = std::make_unique<Game_ctr>();				// �ްѺ��۰װ�׽�̒��g���쐬
	return true;
}

int DrawLine(VECTOR2 vec1, VECTOR2 vec2, unsigned int Color, int Thickness)
{
	DxLib::DrawLine(vec1.x, vec1.y, vec2.x, vec2.y, Color, Thickness);
	return 0;
}
