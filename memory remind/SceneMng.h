#pragma once
#include <mutex>
#include <list>
#include <memory>
#include "BaseScene.h"
#include "VECTOR2.h"

class Obj;
class Game_ctr;

#define lpSceneMng SceneMng::GetInstance()

int		DrawLine(VECTOR2 vec1, VECTOR2 vec2, unsigned int Color, int   Thickness = 1);			// 線を描画する
class SceneMng
{
public:
	static SceneMng &GetInstance(void)
	{
		static SceneMng s_Instance;
		return s_Instance;
	}
	void Run(void);
	VECTOR2 GetScreenSize(void);						// ｽｸﾘｰﾝｻｲｽﾞ取得
	VECTOR2 GetGameSize(void);							// ｹﾞｰﾑｻｲｽﾞ取得
	bool SetDrawOffset(VECTOR2 vec);					// ｵﾌｾｯﾄｾｯﾄ
	const VECTOR2 &GetDrawOffset(void);					// ｵﾌｾｯﾄ情報を受け取る
	bool DeleteObjList(std::list<Obj*>::iterator itr);	// ﾘｽﾄのdelete
private:
	SceneMng();
	~SceneMng();  
	bool (SceneMng::*SmngPtr) (void);
	VECTOR2 drawOffset;
	std::list<std::unique_ptr<Obj>> objList;			 // ｲﾝｽﾀﾝｽした情報を登録
	std::unique_ptr<Game_ctr> gameCtr;					 // ﾕﾆｰｸﾎﾟｲﾝﾀ

	bool SysInit(void);									 // ｼｽﾃﾑ系初期化
	unique_Base activeScene;							 // 現在のｼｰﾝ
};