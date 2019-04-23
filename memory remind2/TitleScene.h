#pragma once
#include <list>
#include "Obj.h"
#include "BaseScene.h"
#include "ImageMng.h"
//#include "classObj.h"
#define lpImageMng ImageMng::GetInstance()

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
private:

};

