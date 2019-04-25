#pragma once
#include <vector>
#include <array>
#include "VECTOR2.h"
#include "classObj.h"
#include "FIRE_DIR.h"
#include "MapID.h"

//�����ڐG������
enum class FIRE_ACT {
	NON,			// ���Ă���
	STOP,			// ���Ă��Ȃ�
	STOP_BREAK,		// ���Ă��Ȃ��A����Ͻ�̒n�`������
	POP_ENEMY,		// ���Ă��A���G���o��
	ERR,			// �װ
	MAX
};


#define lpMapCtl MapCtl::GetInstance()
#define PI 3.141592654
#define RAD(X) ( (X * PI) / 180.0)			// X�͓x��

class MapCtl
{
public:
	// �ÓI�ȼݸ����
	static MapCtl &GetInstance(void)
	{
		static MapCtl s_instance;
		return s_instance;
	}
	void Updata(void);

	void Draw(bool editModeFlag);															// ϯ�ߕ`��
	void DrawFire(void);

	bool SetUp(const VECTOR2& size, const VECTOR2 & chipSize, const VECTOR2 drawOffset);	// ϯ�߂̾�ı���
	bool SetMapData(const VECTOR2& pos, MAP_ID id);											// ϯ���ް��̏�������
	bool SetFireMapData(const VECTOR2& pos, FIRE_DIR dir);									// ̧��ϯ���ް��̏�������
	MAP_ID GetMapData(const VECTOR2& pos);													// �ǂݍ��ݗp�֐�
	unsigned int GetFireMapData(const VECTOR2& pos);										// ���eϯ�ߏ�������

	bool MapSave(void);																		// ϯ�߾���
	bool MapLoad(sharedListObj objList, bool editModeFlag);									// ϯ��۰��	
	bool SetUpGameObj(sharedListObj objList, bool editModeFlag);							// ��޼ު�Ă̾��
	const VECTOR2& GetChipSize(void);														// ���߻��ނ��󂯎��
	const VECTOR2& GetMapSize(void);														// ϯ�߻��ނ��󂯎��
private:
	MapCtl();
	~MapCtl();

	void InitTblData(void);		//ð��ق̏�����

	std::vector<MAP_ID>  mapDataBase;
	std::vector<MAP_ID*> mapData;
	std::vector<unsigned int>  fire_mapDataBase;
	std::vector<unsigned int*> fire_mapData;

	std::array<double, static_cast<unsigned int>(FIRE_DIR::MAX)> rotaPtnTbl;	//��]�����ð���
	std::array<FIRE_ACT, static_cast<unsigned int>(MAP_ID::MAX)> fireActTbl;

	VECTOR2 mapSize;		//�@ϯ�߻���
	VECTOR2 chipSize;		//�@���߻���
	VECTOR2 drawOffset;		//�@�̾�ď���Get


	int bgImage;			//	�w�i�p�̸��̨���ݿ�

	template<typename mapType,typename idType>
	bool SetData(mapType maps,const VECTOR2& pos, idType id);								// ϯ���ް��̏�������

	template<typename mapType,typename idType>
	idType GetData(mapType maps, const VECTOR2& pos, idType defid);							// ϯ���ް��ǂݍ���

};

