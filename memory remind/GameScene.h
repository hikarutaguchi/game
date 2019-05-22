#pragma once
#include <list>
#include "Obj.h"
#include "classObj.h"
#include "BaseScene.h"
#include "Game_ctr.h"

enum P_HP
{
	ONE_HP,
	TWO_HP,
	THREE_HP,
	FOUR_HP,
	MAX_HP
};

using PLAYER_HP_TBL = std::array<VECTOR2, static_cast<int>(P_HP::MAX_HP)>;
using PLAYER_HP_FLAG = std::array<bool, static_cast<int>(P_HP::MAX_HP)>;

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Updata(unique_Base own, Game_ctr &controller);			// �������z���̑�Updata

private:
	sharedListObj objList;														// �ݽ�ݽ��������o�^
	PLAYER_HP_TBL hpPos_TBL;
	PLAYER_HP_FLAG hpFlag;
	int SceneCnt;
	int timeCnt;
	int startCnt;
	bool fadeFinish;
	int bGetCtr;
	int Init(void);																// �Ăяo��
	bool GameDraw();															// ��ި�ĕ\��
	int Pad[4];						// �p�b�h���
	bool padFlag;
	VECTOR2 hpPos[MAX_HP];
	VECTOR2 pPos[CONTROLLER_MAX];
	//�T�E���h
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

