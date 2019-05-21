#pragma once
#include <list>
#include "Obj.h"
#include "classObj.h"
#include "BaseScene.h"

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Updata(unique_Base own, Game_ctr &controller);			// �������z���̑�Updata

private:
	sharedListObj objList;														// �ݽ�ݽ��������o�^

	int SceneCnt;
	int timeCnt;
	int startCnt;
	bool fadeFinish;
	int bGetCtr;
	int Init(void);																// �Ăяo��
	bool GameDraw();															// ��ި�ĕ\��
	int Pad[4];						// �p�b�h���
	bool padFlag;
};

