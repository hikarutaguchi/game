#pragma once
#include "BaseScene.h"
#include "classObj.h"
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
	bool padFlag;

};

