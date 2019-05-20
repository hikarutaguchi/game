#pragma once
#include <vector>
#include <array>
#include "VECTOR2.h"
#include "classObj.h"
#include "MapID.h"

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

	bool SetUp(const VECTOR2& size, const VECTOR2 & chipSize, const VECTOR2 drawOffset);	// ϯ�߂̾�ı���
	bool SetMapData(const VECTOR2& pos, MAP_ID id);											// ϯ���ް��̏�������
	MAP_ID GetMapData(const VECTOR2& pos);													// �ǂݍ��ݗp�֐�
	MAP_ID GetMapID(const VECTOR2& pos, MAP_ID id);

	bool MapSave(void);																		// ϯ�߾���
	bool MapLoad(sharedListObj objList, bool editModeFlag);									// ϯ��۰��
	bool MapSaveBase(void);
	bool MapLoadBase(sharedListObj objList, bool editModeFlag);								// ϯ��۰��	
	bool SetUpGameObj(sharedListObj objList, bool editModeFlag);							// ��޼ު�Ă̾��
	const VECTOR2& GetChipSize(void);														// ���߻��ނ��󂯎��
	const VECTOR2& GetMapSize(void);														// ϯ�߻��ނ��󂯎��
private:
	MapCtl();
	~MapCtl();

	void InitTblData(void);		//ð��ق̏�����

	std::vector<MAP_ID>  mapDataBase;
	std::vector<MAP_ID*> mapData;

	VECTOR2 mapSize;		//�@ϯ�߻���
	VECTOR2 chipSize;		//�@���߻���
	VECTOR2 drawOffset;		//�@�̾�ď���Get

	int bgImage;			//	�w�i�p�̸��̨���ݿ�

	template<typename mapType,typename idType>
	bool SetData(mapType maps,const VECTOR2& pos, idType id);								// ϯ���ް��̏�������

	template<typename mapType,typename idType>
	idType GetData(mapType maps, const VECTOR2& pos, idType defid);							// ϯ���ް��ǂݍ���

	template<typename mapType, typename idType>
	idType GetDataID(mapType maps, const VECTOR2 pos, idType ID);
};

