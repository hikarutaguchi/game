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
	static SceneMng &GetInstance(void)					//	���[�J���ϐ���static�ɂ��邱�Ƃɂ����call_once�̂悤�Ȉ���������
	{
		static SceneMng s_Instance;						//	���̂ŌĂ�								//std::call_once(initFlag, Create); //Create�֐�����񂾂��Ă�
		return s_Instance;							    //	s_Instance�̃|�C���^��Ԃ�
	}

	void Run(void);										//	��x��������

	VECTOR2 GetScreenSize(void);						//	�Q�[���X�N���[���T�C�Y���Z�b�g����֐�
	bool SetDrawOffset(VECTOR2 vec);					//	�Q�[����ʃI�t�Z�b�g�֐�
	const VECTOR2 &GetDrawOffset(void);


private:
	SceneMng();
	~SceneMng();

	VECTOR2 drawOffset;									//	�Q�[����ʃI�t�Z�b�g
	//std::unique_ptr<GameCtr>gameCtr;					//	�X�}�[�g�|�C���^ �^
	bool SysInit(void);									//	�R���X�g���N�^
	unique_Base activeScene;							//	���݂̃V�[��
};