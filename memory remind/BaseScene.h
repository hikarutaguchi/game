#pragma once
#include <DxLib.h>
#include <memory>
#include "VECTOR2.h"

#define SCREEN_SIZE_X 1328		//画面解像度
#define SCREEN_SIZE_Y 1072		//画面解像度

#define GAME_SCREEN_X 40		//画面表示のオフセット
#define GAME_SCREEN_Y 75

#define GAME_SCREEN_SIZE_X 1088	//ゲームエリアのサイズ
#define GAME_SCREEN_SIZE_Y 832

#define CHIP_SIZE 64			//画像分割サイズ

class BaseScene;					// BaseSceneがあとから出てくるぞ宣言
using unique_Base = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	~BaseScene();
private:

};

