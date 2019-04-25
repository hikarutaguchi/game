#pragma once
#include <string>
#include <map>
#include "classObj.h"
#include "VECTOR2.h"

class Game_ctr;

enum ANIM_TBL {			// AddAnim�𷰂ű���
	ANIM_TBL_START_ID,	// �J�n�ʒu
	ANIM_TBL_FRAME,		// �ϐ�
	ANIM_TBL_INV,		// ��Ұ��݊Ԋu
	ANIM_TBL_LOOP,		// ��Ұ��݂�ٰ�߂��邩�ǂ���
	ANIM_TBL_MAX
};

enum DIR {
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_MAX
};

// ��޼ު�Ă�����
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
	bool Init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 pos);			// �摜�Ăяo��(���W�t��)
	bool Init(std::string fileName, VECTOR2 divSize, VECTOR2 divCnt);						// �Ȃ�̉摜�����R�}
	virtual bool InitAnim(void) { return true; };											// ���z�֐�Anim������
	virtual ~Obj();
	void UpData(weekListObj objList,const Game_ctr &controller);							// ���X�V
	virtual bool CheckDeth(void) { return false; };											// ��т̏�ԊǗ��֐�
	virtual bool CheckObjType(OBJ_TYPE type) = 0;											// �ǂ̵�޼ު�Ă������֐�
	virtual void Draw(void);													
	void Draw(unsigned int id);																// id���t��Draw
	const VECTOR2 &GetPos(void);															// Pos���擾
	bool AddAnim(std::string animName, int id_x, int id_y, int frame, int inv, bool loop);	// ��Ұ��݂̐ݒ�
	bool SetAnim(std::string animName);														// ��Ұ��ݾ��
	std::string GetAnim(void);																// ��Ұ��ݎ󂯎��
private:
	virtual void SetMove(weekListObj objList, const Game_ctr &controller) = 0;				// �������z�֐�SetMove

	std::string imageName;																	// �\���摜̧�ٖ���ۑ�

	std::map<std::string, int[ANIM_TBL_MAX]> animTable;
	std::string animName;																	// �\����Ұ��ݖ���ۑ�

protected:
	void Setpos(VECTOR2 pos);

	VECTOR2 pos;						// ���W
	const VECTOR2 drawOffset;			// �`��̾��
	unsigned int animCnt;				// ��Ұ��ݶ����̔�
	VECTOR2 divSize;					// ��������
	VECTOR2 divCnt;						// ������
	bool animEndFlag;					// ��Ұ��ݍŏI�ϓ��B�׸�
	DIR dir;							// ����
	bool visible;						// �\���E��\�����Ǘ�
};