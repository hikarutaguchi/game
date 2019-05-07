#pragma once
#include "BaseScene.h"

class SelectScene :
	public BaseScene
{
public:
	SelectScene();
	~SelectScene();
	virtual unique_Base Updata(unique_Base own, const Game_ctr &controller);	// ƒˆ‰¼‘zŠÖ”UpDate
private:
	virtual int Init(void);
};

