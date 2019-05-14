#include <DxLib.h>
#include "SceneMng.h"
#include "ImageMng.h"
#include "EditScene.h"
#include "MapCtl.h"
#include "EditCursor.h"
#include "Game_ctr.h"
#include "GameScene.h"


EditScene::EditScene()
{
	Init();
}


EditScene::~EditScene()
{

}

unique_Base EditScene::Updata(unique_Base own, Game_ctr & controller)
{

	//if ( (controller.GetCtr(KEY_TYPE_NOW)[KEY_INPUT_F1]) & (~controller.GetCtr(KEY_TYPE_OLD)[KEY_INPUT_F1]) )
	//{
	//	return std::make_unique<GameScene>();
	//}

	if (bGetCtr == PAD_FREE)
	{
		if (controller.GetCtr(CONTROLLER_1P_INPUT_BUTTON_A) == PAD_PUSH)
		{
			return std::make_unique<GameScene>();
		}
	}

	bGetCtr = controller.GetCtr(CONTROLLER_1P_INPUT_BUTTON_A);

	//if (controller.GetCtr(KEY_TYPE_NOW)[KEY_INPUT_F5]) //���̷݂������擾
	//{
	//	MapCtl::GetInstance().MapLoad(objList, true);
	//}
	//if (controller.GetCtr(KEY_TYPE_NOW)[KEY_INPUT_F6])
	//{
	//	//����
	//	if (MessageBox(NULL, "�G�f�B�b�g���e���Z�[�u���܂����H", "�m�F�_�C�A���O", MB_OKCANCEL) == IDOK)
	//	{
	//		MapCtl::GetInstance().MapSave();
	//	}
	//}
	//if (controller.GetCtr(KEY_TYPE_NOW)[KEY_INPUT_F2]) //���̷݂������擾
	//{
	//	//۰��
	//	if (MessageBox(NULL, "�G�f�B�b�g���e�����Z�b�g���܂����H", "�m�F�_�C�A���O", MB_OKCANCEL) == IDOK)	//�Ԃ�l�ŋA���Ă��Ă�
	//	{
	//		Init();
	//	}
	//}

	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->UpData(objList, controller);
	}
	EditDraw();
	return std::move(own);
}

bool EditScene::EditDraw(void)
{
	ClsDrawScreen();
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
	ScreenFlip();
	return true;
}

void EditScene::Text()
{
	//int Color = GetColor(255, 255, 255);
	//VECTOR2 textpos = lpMapCtl.GetChipSize();
	//VECTOR2 Size = lpSceneMng.GetGameSize();
	//DrawString(CHIP_SIZE, CHIP_SIZE, "Z�@or�@X�Ŏ�ސ؂�ւ�", Color);
	//DrawString(CHIP_SIZE * 12, 0, "�g����G�f�B�b�g�ꗗ", Color);
	//DrawString(0, 580, "���݃G�f�B�b�g�̃��Z�b�g	F2", Color);
	//DrawString( (Size.x / 2) - textpos.x * 2, 580, "�G�f�B�b�g���e�̃��[�h	F5", Color);
	//DrawString(Size.x - textpos.x * 4, 580, "�G�f�B�b�g���e�̃Z�[�u	F6", Color);
}

int EditScene::Init(void)
{
	bGetCtr = PAD_MAX;
	//��݂��ڂ�����ؾ��
	if (!objList)
	{
		//��޼ު�Ă�true,false���Ԃ�
		objList = std::make_shared<sharedObjList>();
	}

	objList->clear();

	SceneMng::GetInstance().SetDrawOffset(VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y));

	lpMapCtl.SetUp(VECTOR2(GAME_SCREEN_SIZE_X, GAME_SCREEN_SIZE_Y), VECTOR2(CHIP_SIZE, CHIP_SIZE), SceneMng::GetInstance().GetDrawOffset());
	auto obj = AddObjList()(objList, std::make_unique<EditCursor>(SceneMng::GetInstance().GetDrawOffset()));
	(*obj)->Init("image/yuka.png", VECTOR2(64, 64), VECTOR2(4, 3));
	MapCtl::GetInstance().MapLoadBase(objList, true);

	return 0;
}

