#pragma once
#include "BaseScene.h"

class SelectScene :
	public BaseScene
{
public:
	SelectScene();
	~SelectScene();
	virtual unique_Base Updata(unique_Base own, const Game_ctr &controller);	// �������z�֐�UpDate
private:
	virtual int Init(void);
};

