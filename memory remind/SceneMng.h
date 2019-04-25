#pragma once
#include <mutex>
#include <list>
#include <memory>
#include "BaseScene.h"
#include "VECTOR2.h"

class Obj;
class Game_ctr;

#define lpSceneMng SceneMng::GetInstance()

int		DrawLine(VECTOR2 vec1, VECTOR2 vec2, unsigned int Color, int   Thickness = 1);			// ����`�悷��
class SceneMng
{
public:
	static SceneMng &GetInstance(void)
	{
		static SceneMng s_Instance;
		return s_Instance;
	}
	void Run(void);
	VECTOR2 GetScreenSize(void);						// ��ذݻ��ގ擾
	VECTOR2 GetGameSize(void);							// �ްѻ��ގ擾
	bool SetDrawOffset(VECTOR2 vec);					// �̾�ľ��
	const VECTOR2 &GetDrawOffset(void);					// �̾�ď����󂯎��
	bool DeleteObjList(std::list<Obj*>::iterator itr);	// ؽĂ�delete
private:
	SceneMng();
	~SceneMng();  
	bool (SceneMng::*SmngPtr) (void);
	VECTOR2 drawOffset;
	std::list<std::unique_ptr<Obj>> objList;			 // �ݽ�ݽ��������o�^
	std::unique_ptr<Game_ctr> gameCtr;					 // �ư��߲��

	bool SysInit(void);									 // ���ьn������
	unique_Base activeScene;							 // ���݂̼��
};