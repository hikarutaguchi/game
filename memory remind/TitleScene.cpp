#include "TitleScene.h"



TitleScene::TitleScene()
{
	ClsDrawScreen();
	DrawGraph(0, 0, lpImageMng.GetID("image/title.png")[0], true);
	ScreenFlip();
}


TitleScene::~TitleScene()
{

}
