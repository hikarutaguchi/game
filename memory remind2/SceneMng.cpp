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
	// ---------- �ް�ٰ��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//gameCtr->UpDate();			//�L�[���擾
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
	// ���я���	
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);		// 65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);								// true:window�@false:�ٽ�ذ�
	if (DxLib_Init() == -1) return false;				// DXײ���؏���������
	SetDrawScreen(DX_SCREEN_BACK);						// �ЂƂ܂��ޯ��ޯ̧�ɕ`��
	//gameCtr = std::make_unique<GameCtr>();

	return true;
}

int DrawLine(VECTOR2 vec1, VECTOR2 vec2, unsigned int Color, int Thickness)
{
	DxLib::DrawLine(vec1.x, vec1.y, vec2.x, vec2.y, Color, Thickness);
	return 0;
}

