#pragma once
#include "BaseScene.h"
#include "classObj.h"

class SelectScene :
	public BaseScene
{

public:
	SelectScene();
	~SelectScene();
	virtual unique_Base Updata(unique_Base own, Game_ctr &controller);	// �������z�֐�UpDate

private:
	int Init(void);
	bool nextScene;
	void Draw();
	int bGetCtr;
	sharedListObj objList;			// �ݽ�ݽ��������o�^
	int Pad[4];						// �p�b�h���
	bool padFlag;

};

