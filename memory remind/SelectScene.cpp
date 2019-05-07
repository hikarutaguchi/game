#include "SelectScene.h"
#include "Game_ctr.h"
#include "EditScene.h"
#include "ImageMng.h"
#include "Obj.h"


SelectScene::SelectScene()
{
	Init();
}


SelectScene::~SelectScene()
{
}

unique_Base SelectScene::Updata(unique_Base own, const Game_ctr & controller)
{
	//if (controller.GetCtr(KEY_TYPE_NOW)[KEY_INPUT_3])
	//{
	//	return std::make_unique<EditScene>();
	//}

	//for (auto itr = objList->begin(); itr != objList->end(); itr++)
	//{
	//	(*itr)->UpData(objList, controller);
	//}

	//return std::move(own);
}

int SelectScene::Init(void)
{
	//if (!objList)
	//{
	//	//µÌÞ¼Þª¸Ä‚Åtrue,false‚ª•Ô‚é
	//	objList = std::make_shared<sharedObjList>();
	//}

	//objList->clear();
	//Draw();
	//return 0;
}
