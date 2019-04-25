#pragma once
#include <array>
#include "FIRE_DIR.h"
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

	unsigned int fireLength[static_cast<unsigned int>(FIRE_LENGTH::MAX)]; // 炎の長さを格納する配列

	const std::array<VECTOR2,static_cast<unsigned int>(FIRE_DIR::MAX)> dirPos;
	std::array<bool, static_cast<unsigned int>(FIRE_DIR::MAX)> fireDirFlag;		// 炎が伸びていいかﾌﾗｸﾞ
};

