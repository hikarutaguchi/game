#pragma once
#include <list>
#include "Obj.h"
#include "classObj.h"
#include "BaseScene.h"
#include "Game_ctr.h"

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Updata(unique_Base own, Game_ctr &controller);			// ƒˆ‰¼‘zÀ‘Ì‘¤Updata

private:
	sharedListObj objList;														// ²İ½Àİ½‚µ‚½î•ñ‚ğ“o˜^
	//sharedListObj2 objList2;														// ²İ½Àİ½‚µ‚½î•ñ‚ğ“o˜^

	int SceneCnt;
	int timeCnt;
	int startCnt;
	bool fadeFinish;
	int bGetCtr;

	int Init(void);																// ŒÄ‚Ño‚µ
	bool GameDraw();															// ´ÃŞ¨¯Ä•\¦

	//ƒTƒEƒ“ƒh
	int bgm;
	int one;
	int two;
	int three;
	int sixty;
	int byou;
	int nokori;
	int stop;
	int start;
};

