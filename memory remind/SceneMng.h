#pragma once
#include <mutex>
#include <list>
#include <memory>
#include "BaseScene.h"
#include "VECTOR2.h"

class Obj;
class Game_ctr;

#define lpSceneMng SceneMng::GetInstance()

int		DrawLine(VECTOR2 vec1, VECTOR2 vec2, unsigned int Color, int   Thickness = 1);			// ü‚ğ•`‰æ‚·‚é
class SceneMng
{
public:
	static SceneMng &GetInstance(void)
	{
		static SceneMng s_Instance;
		return s_Instance;
	}
	void Run(void);
	VECTOR2 GetScreenSize(void);						// ½¸Ø°İ»²½Şæ“¾
	VECTOR2 GetGameSize(void);							// ¹Ş°Ñ»²½Şæ“¾
	bool SetDrawOffset(VECTOR2 vec);					// µÌ¾¯Ä¾¯Ä
	const VECTOR2 &GetDrawOffset(void);					// µÌ¾¯Äî•ñ‚ğó‚¯æ‚é
	bool DeleteObjList(std::list<Obj*>::iterator itr);	// Ø½Ä‚Ìdelete
private:
	SceneMng();
	~SceneMng();  
	bool (SceneMng::*SmngPtr) (void);
	VECTOR2 drawOffset;
	std::list<std::unique_ptr<Obj>> objList;			 // ²İ½Àİ½‚µ‚½î•ñ‚ğ“o˜^
	std::unique_ptr<Game_ctr> gameCtr;					 // ÕÆ°¸Îß²İÀ

	bool SysInit(void);									 // ¼½ÃÑŒn‰Šú‰»
	unique_Base activeScene;							 // Œ»İ‚Ì¼°İ
};