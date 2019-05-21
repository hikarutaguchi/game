#pragma once
#include"Game_ctr.h"
#include"VECTOR2.h"

enum Character {
	Slime,
	Skeleton,
	Carbuncle,
	Char_MAX,
};

enum Cursor {
	P1,
	P2,
	P3,
	P4,
	P_TYPE_MAX
};

enum CTR_TYPE
{
	SELECT,
	CANSELL,
	LEFT,
	RIGHT,
	TYPE_MAX
};

#define lpSelCur SelectCur::GetInstance()

using P_TYPE_CHAR = std::array<int, static_cast<int>(Cursor::P_TYPE_MAX)>;
using P_TYPE_TBL  = std::array<bool, static_cast<int>(Cursor::P_TYPE_MAX)>;
using P_POS_TBL   = std::array<VECTOR2, static_cast<int>(Cursor::P_TYPE_MAX)>;
using CHAR_FLAG_TBL = std::array<bool, static_cast<int>(Cursor::P_TYPE_MAX)>;

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

	int GetCharData(Cursor playerNum);	// 選択されたCharIDを返す

	void MoveCur(Game_ctr & controller);	// 選択カーソル

	bool GetCharFlag(void);
	bool GetCharFlag2(void);

private:
	void Draw(void);

	P_TYPE_CHAR CharID;					// キャラ選択ID
	P_POS_TBL   posTBL;

	int GetCtr[CONTROLLER_MAX][TYPE_MAX];
	CTR_TYPE ctrType[CONTROLLER_MAX];
	CHAR_FLAG_TBL CharFlag;					// キャラが選択されているかどうか false = 選択されていない true = 選択されている

	VECTOR2 pos;					// 選択カーソルのPos
};
