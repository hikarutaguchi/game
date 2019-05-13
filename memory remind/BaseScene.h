#pragma once
#include <memory>


#define GAME_SCREEN_X 120			// �ްѴر�\���̵̾�ĉ�
#define GAME_SCREEN_Y 120			// �ްѴر�\���̵̾�ďc

#define GAME_SCREEN_SIZE_X 960		// �ްѴر���މ�
#define GAME_SCREEN_SIZE_Y 704		// �ްѴر���ޏc

#define SCREEN_SIZE_X 1200			// ��ʉ𑜓x��
#define SCREEN_SIZE_Y 944			// ��ʉ𑜓x�c

#define CHIP_SIZE 64				// Ͻ�ڻ���

class Game_ctr;						// Game_ctr���Ƃ���o��
class BaseScene;					// BaseScene�����Ƃ���o�Ă��邼�錾
using unique_Base = std::unique_ptr<BaseScene>;


class BaseScene
{
public:
	virtual ~BaseScene();
	virtual unique_Base Updata(unique_Base own, Game_ctr &controller) = 0;	// �������z�֐�UpDate
private:
	virtual int Init(void) = 0;														// �������z�֐�Init
};


