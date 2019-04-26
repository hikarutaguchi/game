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
	//���q�֐�(����ި���)��remove_if��p����

	objList->remove_if([](sharedObj& obj) {return obj->CheckDeth(); });
	GameDraw();
	return std::move(own);
}

bool GameScene::GameDraw(void)
{
	//��èݸށ@y���W����ɏ�����������`�悷��
	//��޼ު�Ă��o�^����Ă���objLis t�o�^���Ă��鏇���������Ă������A�ǂ���
	//��ɏ������̂͌`�����܂��Ă���B��ĂɕK���K�v�Ȃ��̂�2�̵�޼ު�Ă�����P�������ւ����Ȃ��̂�
	//unique���Q�Ƃł������y���W������ׂ�1�ڂ̂ق���������������^��Ԃ�
	(*objList).sort([](sharedObj &pos1, sharedObj &pos2) {return ((*pos1).GetPos().y) < ((*pos2).GetPos().y); });


	ClsDrawScreen();
	lpMapCtl.Draw(false);
	//�@��ڰ���𕁒ʂɏ������ꍇ
	/*for (std::list<Obj*>::iterator itr = objList.begin(); itr != objList.end(); itr++)*/
	//�^���_��p���ď������ꍇ�@ auto��p���Č^��\�z
	for (auto itr = objList->begin(); itr != objList->end(); itr++)
	{
		(*itr)->Draw();
	}
	//for (auto itr: objList)	//�J�n�ʒu�ƏI�[�ʒu���������auto�ł�����
	//{
	//	itr->Draw();
	//}

	//for (auto &data : (*objList))
	//{
	//	data->Draw(false);
	//}
	//auto fnc = [] {
	//	ClsDrawScreen();	�����_��
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
		//��޼ު�Ă�true,false���Ԃ�
		objList = std::make_shared<sharedObjList>();
	}
	objList->clear();
	lpSceneMng.SetDrawOffset( VECTOR2(GAME_SCREEN_X, GAME_SCREEN_Y) );
	lpMapCtl.SetUp( VECTOR2(GAME_SCREEN_SIZE_X, GAME_SCREEN_SIZE_Y) , VECTOR2(CHIP_SIZE, CHIP_SIZE), SceneMng::GetInstance().GetDrawOffset());
	lpMapCtl.MapLoad(objList, false);
	return true;
}

