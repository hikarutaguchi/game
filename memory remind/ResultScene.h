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
	virtual unique_Base Updata(unique_Base own, const Game_ctr &controller);	// �������z�֐�UpDate

private:
	int killPoint[PLAYER_MAX];
	int goalPoint[PLAYER_MAX];
	int totalPoint[PLAYER_MAX];
	int ranking[PLAYER_MAX];

	int Init(void);
	bool nextScene;
	void Draw();
	sharedListObj objList;			// �ݽ�ݽ��������o�^
	int Pad[4];						// �p�b�h���
	bool padFlag;
};

