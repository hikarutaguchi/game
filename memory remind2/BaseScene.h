#pragma once
#include <DxLib.h>
#include <memory>
#include "VECTOR2.h"

#define SCREEN_SIZE_X 1328		//��ʉ𑜓x
#define SCREEN_SIZE_Y 1072		//��ʉ𑜓x

#define GAME_SCREEN_X 40		//��ʕ\���̃I�t�Z�b�g
#define GAME_SCREEN_Y 75

#define GAME_SCREEN_SIZE_X 1088	//�Q�[���G���A�̃T�C�Y
#define GAME_SCREEN_SIZE_Y 832

#define CHIP_SIZE 64			//�摜�����T�C�Y

class BaseScene;					// BaseScene�����Ƃ���o�Ă��邼�錾
using unique_Base = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	~BaseScene();
private:

};

