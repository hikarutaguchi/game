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
	ANIM_TBL_START_ID,			//�A�j���[�V�����J�n�ʒu
	ANIM_TBL_FLAME,				//�A�j���[�V�����R�}��
	ANIM_TBL_INV,				//�A�j���[�V���������T�C�Y(�Ԋu)
	ANIM_TBL_LOOP,				//���[�v���邩�ǂ���
	ANIM_TBL_MAX				//�ő�
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
	virtual ~Obj();						//���z�֐�
	//void UpDate(const GameCtr &Ctr, weakObjList objList);	//�������n�֐�
	virtual bool CheckDeth(void) { return false; };			//�{���������������ǂ��� false�@�������ĂȂ� true ��������
	virtual bool CheckObjType(OBJ_TYPE type) = 0;
	virtual void Draw(void);			//�`��n�֐�
	void Draw(unsigned int id);			//�Œ�ID�\��
	const VECTOR2 &GetPos(void);		//���W�󂯎�� read only
	bool AddAnim(std::string animName, int id_x, int id_y, int flame, int inv, bool loop);	//�A�j���`�揈���֐�
	bool SetAnim(std::string animName);	//�A�j���`��Z�b�g�֐�
	std::string GetAnim(void);			//�A�j���Đ��󂯓n��

private:
	//virtual void SetMove(const GameCtr &Ctr, weakObjList objList) = 0;
	std::string imageName;		//�\���摜�t�@�C����

protected:
	const VECTOR2 drawOffset;	//�`��I�t�Z�b�g
	VECTOR2 pos;				//���W
	void SetPos(VECTOR2 pos);
	VECTOR2 divSize;			//�A�j�������T�C�Y
	VECTOR2 divCnt;				//�A�j��������
	bool animEndFlag;			//�A�j���[�V�����ŏI�R�}���B�t���O

	std::map<std::string, int[ANIM_TBL_MAX]> animTable;	//2�����z��
	std::string animName;		//�\���摜�A�j���[�V������
	unsigned int animCnt;		//�A�j���[�V�����J�E���^�[
	DIR	  dir;			//�ړ�����
};

