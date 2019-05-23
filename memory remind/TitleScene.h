#pragma once
#include "BaseScene.h"
#include "classObj.h"

typedef struct Cloud
{
	int Cnt;
	int getID;
	int High;
	int speed;
	bool visivle;
};

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();

	virtual unique_Base Updata(unique_Base own, Game_ctr &controller);

private:
	int Init(void);
	void Draw();
	sharedListObj objList;			// �ݽ�ݽ��������o�^
	int Pad[4];						// �p�b�h���
	int animCnt;
	bool fadeFinish;
	bool padFlag;
	int titleLogoCnt;
	Cloud cloud[4];
	int bgm;
	int timeCnt;
	int seNextButton;
};

