#pragma once
#include <list>
#include "Obj.h"
#include "BaseScene.h"
#include "classObj.h"


class EditScene :
	public BaseScene
{
public:
	EditScene();
	~EditScene();
	virtual unique_Base Updata(unique_Base own, const Game_ctr &controller);

private:
	sharedListObj objList;			// �ݽ�ݽ��������o�^
	int Init(void);					// �Ăяo��
	void Text();					// �����\���֐�
	bool EditDraw();				// ��ި�ĕ\��
	VECTOR2 Drawpos;
	int Pad[4];
	bool padFlag;
};
