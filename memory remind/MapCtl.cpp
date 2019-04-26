#include <type_traits>
#include <memory>
#include "DxLib.h"
#include "ImageMng.h"
#include "SceneMng.h"
#include "MapCtl.h"
#include "EditScene.h"
#include "Player.h"

struct DataHeader {
	char fileID[13];					// �t�@�C����ID���
	char verID;							// �o�[�W�����ԍ�
	char reserve1[2];					// 2�޲Ă���а,�\��̈�
	int sizeX;							// �}�b�v��Ͻ�ڐ�X
	int sizeY;							// �}�b�v��Ͻ�ڐ�Y
	char reserve2[3];					// 3�޲Ă���а,�\��̈�
	char sum;							// sum�l

};

#define BOMBERMAN_FILE_ID "BBM_MAP_DATA"
#define BOMBERMAN_VER_ID 0x01			// ̧���ް�ޮݔԍ�
#define lpSceneMng SceneMng::GetInstance()

// ���̱�Ұ���
#define FIRE_ANIM_FRAME 7										// 1�ϓ�������ڰѐ�
#define FIRE_ANIM_CNT	7										// ���ϐ�
#define FIRE_ANIM_TOP	(FIRE_ANIM_CNT / 2)						// ��Ұ��ݐ܂�Ԃ��ψʒu
#define FIRE_ANIM_TOTAL_FRAME (FIRE_ANIM_FRAME * FIRE_ANIM_CNT)	// ���ڰѐ�
#define FIRE_ANIM_PTN_X 3										// ���̎��(�N���X�A���_�A�K��)


void MapCtl::Updata(void)
{
}

void MapCtl::Draw(bool editModeFlag)
{
	if (!editModeFlag)
	{
		DrawGraph(0, 0, bgImage, false);
		int AnimCnt = 0;
		for (int y = 0; y < mapSize.y; y++)
		{
			AnimCnt = y % 2;
			for (int x = 0; x < mapSize.x; x++)
			{
				{
					DrawGraph(drawOffset.x + x * chipSize.x, drawOffset.y + y * chipSize.y, lpImageMng.GetID("image/.png")[0], true);
					AnimCnt++;
				}
			}
		}
	}
	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			MAP_ID id = mapData[y][x];
			switch (id)
			{
			case (MAP_ID::NON):		//��ɕ\�����Ȃ�
				break;
			case (MAP_ID::BOMB):
				//if (lpSceneMng.CheckEditMode())
				//{
				//	DrawGraph(drawOffset.x + x * chipSize.x, drawOffset.y + y * chipSize.y, lpImageMng.GetID("image/map.png")[MAP_ID_CUR], true);
				//}
				//���ł��ǂ������̂ق����ǂ�
				if (!editModeFlag)
				{
					break;		//��ި��Ӱ�ގ��͕`�悷��̂ŁA���̂܂܉��ɏ����𗬂�
				}

			case  (MAP_ID::WALL1):
			case  (MAP_ID::WALL2):
			case  (MAP_ID::BLOCK):
			case  (MAP_ID::ITEM_FIRE):
			case  (MAP_ID::ITEM_BOMB):
			//case  (MAP_ID::ITEM_CTL):
			//case  (MAP_ID::ITEM_SPEED) :
				DrawGraph(drawOffset.x + x * chipSize.x, drawOffset.y + y * chipSize.y, lpImageMng.GetID("image/map.png")[static_cast<int>(id)], true);
				break;
			case  (MAP_ID::CUR) :
			case  (MAP_ID::FLOOR1):
			case  (MAP_ID::FLOOR2):
			default:
				// �װ
#ifdef _DEBUG
				DrawGraph(drawOffset.x + x * chipSize.x, drawOffset.y + y * chipSize.y, lpImageMng.GetID("image/map.png")[static_cast<int>(MAP_ID::CUR)], true);
#endif
				break;
			}
		}
	}
}

bool MapCtl::SetUp(const VECTOR2 & size, const VECTOR2 & chipSize, const VECTOR2 drawOffset)
{
	lpImageMng.GetID("image/map.png", VECTOR2(20, 20), VECTOR2(4, 3));	//ϯ�߂����ł�����ٰ

	//��ʉ𑜓x�����߻��ނ��󂯎����
	mapSize = VECTOR2(size.x / chipSize.x, size.y / chipSize.y);
	MapCtl::chipSize = chipSize;
	MapCtl::drawOffset = drawOffset;		//�̾�ď���Get

	auto createMap = [=](auto& base, auto& front, auto initNum) {

		base.resize(mapSize.x * mapSize.y);	//�v�f�Ƃ��đS�̻̂��ނ��m��
		front.resize(mapSize.y);			//�c�ɉ�����邩
		for (unsigned int count = 0; count < front.size(); count++)
		{
			front[count] = &base[mapSize.x * count];
		}

		for (unsigned int j = 0; j < base.size(); j++)
		{
			base[j] = initNum;
		}
	};

	createMap(mapDataBase,		mapData,	  MAP_ID::NON);

	if (bgImage <= 0)	//	�w�i������ĂȂ����������
	{
		auto ScreenSize = lpSceneMng.GetScreenSize();
		bgImage = MakeScreen(ScreenSize.x, ScreenSize.y, false);
		SetDrawScreen(bgImage);


		int AnimCnt = 0;
		for (int y = 0; y < mapSize.y; y++)
		{
			AnimCnt = y % 2;
			for (int x = 0; x < mapSize.x; x++)
			{
				{
					DrawGraph(drawOffset.x + x * chipSize.x, drawOffset.y + y * chipSize.y, lpImageMng.GetID("image/yuka.png")[0], true);
					AnimCnt++;
				}
			}
		}
		SetDrawScreen(DX_SCREEN_BACK);
	}
	return false;
}

struct CheckSize 
{
	bool operator ()(const VECTOR2 &selPos,const VECTOR2 &mapSize) {
		if ((selPos.x < 0) || (selPos.y < 0) || (mapSize.x <= selPos.x) || (mapSize.y <= selPos.y))		//�͈�����
		{
			return false;
		}
		return true;
	}
};


bool MapCtl::SetMapData(const VECTOR2 & pos, MAP_ID id)
{
	return SetData(mapData, pos, id);
}

template<typename mapType, typename idType>
bool MapCtl::SetData(mapType maps, const VECTOR2 & pos, idType id)		//inline�͎g�p����v���O�����ɂ��̂܂ܓW�J
{
	VECTOR2 selPos;
	selPos.x = pos.x / chipSize.x;
	selPos.y = pos.y / chipSize.y;
	CheckSize checkSize;			//�����̂�����Ă���āA�֐����Ăяo���݂����ɂ�����
	if ((!checkSize(selPos, mapSize)))
	{
		return false;
	}
	maps[selPos.y][selPos.x] = id;
	_RPTN(_CRT_WARN, "write[%d,%d]%d\n", pos.x, pos.y, id);
	return true;
}

MAP_ID MapCtl::GetMapData(const VECTOR2 & pos)
{
	return GetData(mapData, pos, MAP_ID::WALL2);
}

template<typename mapType, typename idType>
idType MapCtl::GetData(mapType maps, const VECTOR2 & pos, idType defid)
{
	//pos�͍��W
	VECTOR2 selPos;
	selPos.x = pos.x / chipSize.x;
	selPos.y = pos.y / chipSize.y;

	CheckSize checkSize;			// �����̂�����Ă���āA�֐����Ăяo���݂����ɂ�����
	if ((!checkSize(selPos, mapSize)))
	{
		return defid;
	}
	return maps[selPos.y][selPos.x];
}

bool MapCtl::MapSave(void)
{
	DataHeader exportData = {
		BOMBERMAN_FILE_ID,
		BOMBERMAN_VER_ID,
		{ 0,0 },			// �z��𖾎��I�ɂ���
		mapSize.x,
		mapSize.y,
		{ 0,0,0 },			// �z��𖾎��I�ɂ���
		(char)0xff
	};

	int sum = 0;				// sum�l�̌v�Z
	for (unsigned int j = 0; j < mapDataBase.size(); j++)
	{
		sum += (int)mapDataBase[j];
	}

	exportData.sum = (char)sum;

	FILE *file;																// �t�@�C���|�C���^
	fopen_s(&file, "data/mapdata.map", "wb");								// �t�@�C�����J��
	fwrite(&exportData, sizeof(exportData), 1, file);						// ��������
	fwrite(mapDataBase.data(), sizeof(MAP_ID), mapDataBase.size(), file);
	fclose(file);															// �t�@�C�������

	return true;
}

bool MapCtl::MapLoad(sharedListObj objList, bool editModeFlag)//
{

	FILE *file;													// �t�@�C���|�C���^
	DataHeader exportData;
	fopen_s(&file, "data/mapdata.map", "rb");					// �t�@�C�����J��
	fread(&exportData, sizeof(exportData), 1, file);			// �ǂݏo����̱��ڽ,���ǂނ�
																// ͯ�ނ̻��ޏ������Ƃ�mapDataBase��resize����B
	mapDataBase.resize(exportData.sizeX * exportData.sizeY);
	fread(mapDataBase.data(), sizeof(MAP_ID), mapDataBase.size(), file);
	fclose(file);
	bool flag = true;
	//int sum = 0;				//sum�l�̌v�Z
	//for (int j = 0; j < mapDataBase.size(); j++)
	//{
	//	sum += (int)mapDataBase[j];
	//}
	//ͯ�ނ�̧�قh�c���Ɠ����Ŏ����Ă���h�c�Ɣ�ׂ�
	//ͯ�ނ��ް�ޮݔԍ��Ɠ����Ŏ����Ă���h�c���ׂ�
	if ((std::string)exportData.fileID != BOMBERMAN_FILE_ID)
	{
		flag = false;
	}
	if (exportData.verID != BOMBERMAN_VER_ID)
	{
		flag = false;
	}
	//sum�l���v�Z���āAͯ�ް��sum�l�ƈ���Ă�����A�ް���ر
	int sum = 0;				//sum�l�̌v�Z
	for (unsigned int j = 0; j < mapDataBase.size(); j++)
	{
		sum += (int)mapDataBase[j];			//����int
	}
	if (exportData.sum != (char)sum)		//char�Ŗ����I�ɷ��Ă��Ȃ���4byte����1byte�͑傫�����̂͐؂�̂Ă���
	{
		flag = false;
	}
	//�ް��̸ر
	if (flag == false)
	{
		for (unsigned int j = 0; j < mapDataBase.size(); j++)
		{
			mapDataBase[j] = (MAP_ID::NON);
		}
		//for (auto &data : mapDataBase)			//�@�Q�Ƃɂ��Ă����邱�Ƃŏ����������ł���悤�ɂȂ�
		//{
		//	data = MAP_ID_NON;
		//}
	}
	if (flag == true)
	{
		SetUpGameObj(objList, editModeFlag);
	}
	return flag;
}

MapCtl::MapCtl()
{
	bgImage = 0;
	InitTblData();
}


MapCtl::~MapCtl()
{

}

void MapCtl::InitTblData(void)
{
}

bool MapCtl::SetUpGameObj(sharedListObj objList, bool editModeFlag)//
{
	if (editModeFlag == true)
	{
		return false;
	}
	bool makeflag = false;
	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			MAP_ID id = mapData[y][x];
			ListObj_itr obj;
			switch (id)
			{
			case (MAP_ID::BOMB):		//��ڲ԰��ׂ�ݽ�ݽ
				if (makeflag)
				{
					break;
				}
				{
					//obj = AddObjList()(objList, std::make_unique<Player>(VECTOR2(x * chipSize.x, y * chipSize.y),drawOffset + VECTOR2(0, -20)));	//�ݽ�ݽ
					makeflag = true;
				}
				break;
			case (MAP_ID::NON) :		//��ɕ\�����Ȃ�
			case (MAP_ID::WALL1) :
			case (MAP_ID::WALL2) :
			case (MAP_ID::BLOCK) :
			case (MAP_ID::ITEM_FIRE) :
			case (MAP_ID::ITEM_BOMB) :
			//case (MAP_ID::ITEM_CTL) :
			//case (MAP_ID::ITEM_SPEED) :
				break;				//�������Ȃ�
			case (MAP_ID::CUR) :
			case (MAP_ID::FLOOR1) :
			case (MAP_ID::FLOOR2) :
			default:
				// �װ
				break;
			}
			//obj = AddObjList()(objList, std::make_unique<Player>(VECTOR2(x * chipSize.x, y * chipSize.y), drawOffset + VECTOR2(0, -20)));	//�ݽ�ݽ
		}
		ListObj_itr obj;
		obj = AddObjList()(objList, std::make_unique<Player>(VECTOR2(200,200), drawOffset + VECTOR2(0, -20)));	//�ݽ�ݽ
	}

	return true;
}

const VECTOR2 & MapCtl::GetChipSize(void)
{
	return chipSize;
}

const VECTOR2 & MapCtl::GetMapSize(void)
{
	return mapSize;
}