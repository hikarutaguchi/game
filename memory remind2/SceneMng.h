#pragma once
#include <mutex>
#include <list>
#include <memory>
#include "VECTOR2.h"
#include "BaseScene.h"
#include "Obj.h"

#define lpSceneMng SceneMng::GetInstance()

int DrawLine(VECTOR2 vec1, VECTOR2 vec2, unsigned int Color, int Thickness = 1);
class SceneMng
{
public:
	static SceneMng &GetInstance(void)					//	ローカル変数のstaticにすることによってcall_onceのような扱いをする
	{
		static SceneMng s_Instance;						//	実体で呼ぶ								//std::call_once(initFlag, Create); //Create関数を一回だけ呼ぶ
		return s_Instance;							    //	s_Instanceのポインタを返す
	}

	void Run(void);										//	一度だけ処理

	VECTOR2 GetScreenSize(void);						//	ゲームスクリーンサイズをセットする関数
	bool SetDrawOffset(VECTOR2 vec);					//	ゲーム画面オフセット関数
	const VECTOR2 &GetDrawOffset(void);


private:
	SceneMng();
	~SceneMng();

	VECTOR2 drawOffset;									//	ゲーム画面オフセット
	//std::unique_ptr<GameCtr>gameCtr;					//	スマートポインタ 型
	bool SysInit(void);									//	コンストラクタ
	unique_Base activeScene;							//	現在のシーン
};