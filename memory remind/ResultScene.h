#pragma once
#include "BaseScene.h"
#include "classObj.h"
#include "Player.h"

class ResultScene :
	public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	virtual unique_Base Updata(unique_Base own, Game_ctr &controller);	// �������z�֐�UpDate

private:
	int bGetCtr;
	bool fadeFinish;
	int Init(void);
	bool nextScene;
	void Draw();
	sharedListObj objList;			// �ݽ�ݽ��������o�^
	int Pad[4];						// �p�b�h���
	bool padFlag;
};

