#pragma once
#include "BaseScene.h"
#include "classObj.h"
class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();

	virtual unique_Base Updata(unique_Base own, const Game_ctr &controller);

private:

	int Init(void);
	void Draw();
	sharedListObj objList;			// ²İ½Àİ½‚µ‚½î•ñ‚ğ“o˜^

};

