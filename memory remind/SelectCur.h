#pragma once
#include"Game_ctr.h"
#include"VECTOR2.h"

enum Character {
	NON,
	slime,
	skeleton,
	carbuncle,
	Char_MAX,
};

enum CTR_TYPE
{
	SELECT,
	CANSELL,
	LEFT,
	RIGHT,
	DOWN,
	TYPE_MAX
};

#define lpSelCur SelectCur::GetInstance()

using P_TYPE_CHAR = std::array<int, static_cast<int>(P_TYPE::CONTROLLER_MAX)>;
using P_TYPE_TBL  = std::array<bool, static_cast<int>(P_TYPE::CONTROLLER_MAX)>;
using P_POS_TBL   = std::array<VECTOR2, static_cast<int>(P_TYPE::CONTROLLER_MAX)>;
using CHAR_FLAG_TBL = std::array<bool, static_cast<int>(P_TYPE::CONTROLLER_MAX)>;

class SelectCur
{
public:
	static SelectCur &GetInstance(void)
	{
		static SelectCur s_instance;
		return s_instance;
	}
	SelectCur();
	~SelectCur();

	void Init();
	int GetCharData(P_TYPE playerNum);		// �I�����ꂽCharID��Ԃ�

	void MoveCur(Game_ctr & controller);	// �I���J�[�\��

	bool GetCharFlag(P_TYPE pType);			// �L������I���������ǂ�����Flag��Ԃ�
	bool GetPlayerFlag(P_TYPE pType);

private:
	void Draw(void);

	P_TYPE_TBL  playerFlag;				// �v���C���[�̐��ɉ�����Flag���Ǘ�
	CHAR_FLAG_TBL CharFlag;				// �L�������I������Ă��邩�ǂ��� false = �I������Ă��Ȃ� true = �I������Ă���
	P_POS_TBL   posTBL;					// �e�J�[�\���̍��W
	P_TYPE_CHAR CharID;					// �L�����I��ID
	P_POS_TBL DrawTBL;
	CTR_TYPE ctrType[CONTROLLER_MAX];
	VECTOR2 tmpPos[CONTROLLER_MAX];		//���ړ��ϐ�
	VECTOR2 pos;						// �I���J�[�\����Pos

	int GetCtr[CONTROLLER_MAX][TYPE_MAX];

	//�T�E���h
	int kettei;
	int cansell;
	int menu;
	int choice;
};
