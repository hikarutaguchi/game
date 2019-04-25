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
	unique_Base Updata(unique_Base own, const Game_ctr &controller);			// ƒˆ‰¼‘zÀ‘Ì‘¤Updata

private:
	sharedListObj objList;														// ²İ½Àİ½‚µ‚½î•ñ‚ğ“o˜^
	int Init(void);																// ŒÄ‚Ño‚µ
	bool GameDraw();															// ´ÃŞ¨¯Ä•\¦
};

