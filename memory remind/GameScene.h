#pragma once
#include <list>
#include "Obj.h"
#include "classObj.h"
#include "BaseScene.h"
#include "Game_ctr.h"

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Updata(unique_Base own, Game_ctr &controller);			// �������z���̑�Updata

private:
	sharedListObj objList;														// �ݽ�ݽ��������o�^
	//sharedListObj2 objList2;														// �ݽ�ݽ��������o�^

	int SceneCnt;
	int timeCnt;
	int startCnt;
	bool fadeFinish;
	int bGetCtr;

	int Init(void);																// �Ăяo��
	bool GameDraw();															// ��ި�ĕ\��

	//�T�E���h
	int bgm;
	int one;
	int two;
	int three;
	int sixty;
	int byou;
	int nokori;
	int stop;
	int start;
};

