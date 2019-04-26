#pragma once
#include <array>
#include "Obj.h"

enum class FIRE_LENGTH {
	NOW,		//�@���݂̒���
	LIM,		//�@���E�̒���
	MAX
};

class Bomb :
	public Obj
{
public:
	Bomb(VECTOR2 setupPos, unsigned int length , VECTOR2 drawOffset);
	~Bomb();
private:
	void SetMove(weekListObj objList, const Game_ctr &controller);		// �������z�֐����̑�
	bool InitAnim(void);												// �摜�Ăяo��
	bool CheckDeth(void);												// ���������p�֐�
	bool CheckObjType(OBJ_TYPE type);									// ��޼ު����������
																		// ��т̔������L�тĂ��邩�Ǘ�����֐�

	int count;															// ��������	

};

