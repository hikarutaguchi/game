#pragma once
#include <string>
#include <map>
#include "classObj.h"
#include "VECTOR2.h"

class Game_ctr;

enum ANIM_TBL {			// AddAnimをｷｰでｱｸｾｽ
	ANIM_TBL_START_ID,	// 開始位置
	ANIM_TBL_FRAME,		// ｺﾏ数
	ANIM_TBL_INV,		// ｱﾆﾒｰｼｮﾝ間隔
	ANIM_TBL_LOOP,		// ｱﾆﾒｰｼｮﾝのﾙｰﾌﾟするかどうが
	ANIM_TBL_MAX
};

enum DIR {
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_MAX
};

// ｵﾌﾞｼﾞｪｸﾄのﾀｲﾌﾟ
enum OBJ_TYPE {
	OBJ_PLAYER,
	OBJ_ENEMY,
	OBJ_BOMB,
	OBJ_EDIT_CUR,
	OBJ_MAX
};

class Obj
{
public:
	Obj();
	Obj(VECTOR2 drawOffset);
	bool Init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 pos);			// 画像呼び出し(座標付き)
	bool Init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt);						// なんの画像を何コマ
	virtual bool InitAnim(void) { return true; };											// 仮想関数Anim初期化
	virtual ~Obj();
	void UpData(weekListObj objList,const Game_ctr &controller);							// 情報更新
	virtual bool CheckDeth(void) { return false; };											// ﾎﾞﾑの状態管理関数
	virtual bool CheckObjType(OBJ_TYPE type) = 0;											// どのｵﾌﾞｼﾞｪｸﾄかﾁｪｯｸ関数
	virtual void Draw(void);													
	void Draw(unsigned int id);																// id情報付きDraw
	const VECTOR2 &GetPos(void);															// Pos情報取得
	bool AddAnim(std::string animName, int id_x, int id_y, int frame, int inv, bool loop);	// ｱﾆﾒｰｼｮﾝの設定
	bool SetAnim(std::string animName);														// ｱﾆﾒｰｼｮﾝｾｯﾄ
	std::string GetAnim(void);																// ｱﾆﾒｰｼｮﾝ受け取り
private:
	virtual void SetMove(weekListObj objList, const Game_ctr &controller) = 0;				// 純粋仮想関数SetMove

	std::string imageName;																	// 表示画像ﾌｧｲﾙ名を保存

	std::map<std::string, int[ANIM_TBL_MAX]> animTable;
	std::string animName;																	// 表示ｱﾆﾒｰｼｮﾝ名を保存

protected:
	void Setpos(VECTOR2 pos);

	VECTOR2 pos;						// 座標
	const VECTOR2 drawOffset;			// 描画ｵﾌｾｯﾄ
	unsigned int animCnt;				// ｱﾆﾒｰｼｮﾝｶｳﾝﾀの箱
	VECTOR2 divSize;					// 分割ｻｲｽﾞ
	VECTOR2 divCnt;						// 分割数
	bool animEndFlag;					// ｱﾆﾒｰｼｮﾝ最終ｺﾏ到達ﾌﾗｸﾞ
	DIR dir;							// 方向
	bool visible;						// 表示・非表示を管理
};