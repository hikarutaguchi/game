#pragma once
#include <vector>
#include <map>
#include "VECTOR2.h"

enum DIR {
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_MAX
};

enum ANIM_TBL {
	ANIM_TBL_START_ID,			//アニメーション開始位置
	ANIM_TBL_FLAME,				//アニメーションコマ数
	ANIM_TBL_INV,				//アニメーション分割サイズ(間隔)
	ANIM_TBL_LOOP,				//ループするかどうか
	ANIM_TBL_MAX				//最大
};

enum OBJ_TYPE {
	OBJ_PLAYER,
	OBJ_ENEMY,
	OBJ_BOMB,
	OBJ_EDIT_CUR,
	OBJ_MAX
};

class GameCtr;

class Obj
{
public:
	Obj(VECTOR2 drawOffset);
	Obj();
	bool init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt);
	bool init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 pos);
	virtual bool initAnim(void) { return true; };
	virtual ~Obj();						//仮想関数
	//void UpDate(const GameCtr &Ctr, weakObjList objList);	//初期化系関数
	virtual bool CheckDeth(void) { return false; };			//ボムが爆発したかどうか false　爆発してない true 爆発した
	virtual bool CheckObjType(OBJ_TYPE type) = 0;
	virtual void Draw(void);			//描画系関数
	void Draw(unsigned int id);			//固定ID表示
	const VECTOR2 &GetPos(void);		//座標受け取り read only
	bool AddAnim(std::string animName, int id_x, int id_y, int flame, int inv, bool loop);	//アニメ描画処理関数
	bool SetAnim(std::string animName);	//アニメ描画セット関数
	std::string GetAnim(void);			//アニメ再生受け渡し

private:
	//virtual void SetMove(const GameCtr &Ctr, weakObjList objList) = 0;
	std::string imageName;		//表示画像ファイル名

protected:
	const VECTOR2 drawOffset;	//描画オフセット
	VECTOR2 pos;				//座標
	void SetPos(VECTOR2 pos);
	VECTOR2 divSize;			//アニメ分割サイズ
	VECTOR2 divCnt;				//アニメ分割数
	bool animEndFlag;			//アニメーション最終コマ到達フラグ

	std::map<std::string, int[ANIM_TBL_MAX]> animTable;	//2次元配列
	std::string animName;		//表示画像アニメーション名
	unsigned int animCnt;		//アニメーションカウンター
	DIR	  dir;			//移動方向
};

