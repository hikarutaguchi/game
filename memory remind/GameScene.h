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
	unique_Base Updata(unique_Base own, const Game_ctr &controller);			// �������z���̑�Updata

private:
	sharedListObj objList;														// �ݽ�ݽ��������o�^
	int Init(void);																// �Ăяo��
	bool GameDraw();															// ��ި�ĕ\��
};

