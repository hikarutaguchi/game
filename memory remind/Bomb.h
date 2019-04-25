#pragma once
#include <array>
#include "Obj.h"

enum class FIRE_LENGTH {
	NOW,		//　現在の長さ
	LIM,		//　限界の長さ
	MAX
};

class Bomb :
	public Obj
{
public:
	Bomb(VECTOR2 setupPos, unsigned int length , VECTOR2 drawOffset);
	~Bomb();
private:
	void SetMove(weekListObj objList, const Game_ctr &controller);		// 純粋仮想関数実体側
	bool InitAnim(void);												// 画像呼び出し
	bool CheckDeth(void);												// ｶｳﾝﾄﾁｪｯｸ用関数
	bool CheckObjType(OBJ_TYPE type);									// ｵﾌﾞｼﾞｪｸﾄﾀｲﾌﾟﾁｪｯｸ
																		// ﾎﾞﾑの爆発が伸びているか管理する関数

	int count;															// 爆発ｶｳﾝﾄ	

};

