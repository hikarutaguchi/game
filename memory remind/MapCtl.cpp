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

struct DataHeaderBase {
	char fileID[14];					// �t�@�C����ID���
	char verID;							// �o�[�W�����ԍ�
	char reserve1[2];					// 2�޲Ă���а,�\��̈�
	int sizeX;							// �}�b�v��Ͻ�ڐ�X
	int sizeY;							// �}�b�v��Ͻ�ڐ�Y
	char reserve2[3];					// 3�޲Ă���а,�\��̈�
	char sum;							// sum�l
};

#define MAP_FILE_ID "BBM_MAP_DATA"
#define MAP_FILE_BASE_ID  "MAP_DATA_BASE"
#define MAP_FILE_VER_ID 0x01			// ̧���ް�ޮݔԍ�
#define MAP_FILE_BASE_VER_ID 0x01

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
	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			MAP_ID id = mapData[y][x];
			switch (id)
			{
			case (MAP_ID::YUKA):
			case (MAP_ID::IWA):
			case (MAP_ID::HOLE):
			case (MAP_ID::UNTI):
			case (MAP_ID::EKI):
			case (MAP_ID::NULLL):
			case (MAP_ID::WIND):
			case (MAP_ID::MAGIC):
			case (MAP_ID::MAGIC1):
			case (MAP_ID::BORN):
			case (MAP_ID::ESA):
			case (MAP_ID::TOOL):
				DrawGraph(drawOffset.x + x * chipSize.x, drawOffset.y + y * chipSize.y, lpImageMng.GetID("image/yuka.png")[static_cast<int>(id)], true);
				break;
				// �װ
#ifdef _DEBUG
				DrawGraph(drawOffset.x + x * chipSize.x, drawOffset.y + y * chipSize.y, lpImageMng.GetID("image/yuka.png")[static_cast<int>(MAP_ID::UNTI)], true);
#endif
				break;
			}
		}
	}
}

bool MapCtl::SetUp(const VECTOR2 & size, const VECTOR2 & chipSize, const VECTOR2 drawOffset)
{
	lpImageMng.GetID("image/yuka.png", VECTOR2(64, 64), VECTOR2(4, 3));	//ϯ�߂����ł�����ٰ

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

	createMap(mapDataBase, mapData, MAP_ID::YUKA);

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
	bool operator ()(const VECTOR2 &selPos, const VECTOR2 &mapSize) {
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
	if ((maps[selPos.y][selPos.x]) == MAP_ID::IWA)
	{
		return false;
	}

	maps[selPos.y][selPos.x] = id;

	_RPTN(_CRT_WARN, "write[%d,%d]%d\n", pos.x, pos.y, id);
	return true;
}

MAP_ID MapCtl::GetMapData(const VECTOR2 & pos)
{
	return GetData(mapData, pos, MAP_ID::UNTI);
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
		MAP_FILE_ID,
		MAP_FILE_VER_ID,
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

	if ((std::string)exportData.fileID != MAP_FILE_ID)
	{
		flag = false;
	}
	if (exportData.verID != MAP_FILE_VER_ID)
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
			mapDataBase[j] = (MAP_ID::YUKA);
		}
		for (auto &data : mapDataBase)			//�@�Q�Ƃɂ��Ă����邱�Ƃŏ����������ł���悤�ɂȂ�
		{
			data = MAP_ID::YUKA;
		}
	}
	if (flag == true)
	{
		SetUpGameObj(objList, editModeFlag);
	}
	return flag;
}

bool MapCtl::MapSaveBase(void)
{
	DataHeaderBase exportData = {
		MAP_FILE_BASE_ID,
		MAP_FILE_BASE_VER_ID,
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
	fopen_s(&file, "data/mapdatabase.map", "wb");								// �t�@�C�����J��
	fwrite(&exportData, sizeof(exportData), 1, file);						// ��������
	fwrite(mapDataBase.data(), sizeof(MAP_ID), mapDataBase.size(), file);
	fclose(file);															// �t�@�C�������

	return true;
}

bool MapCtl::MapLoadBase(sharedListObj objList, bool editModeFlag)
{
	FILE *file;													// �t�@�C���|�C���^
	DataHeaderBase exportData;
	fopen_s(&file, "data/mapdatabase.map", "rb");					// �t�@�C�����J��
	fread(&exportData, sizeof(exportData), 1, file);			// �ǂݏo����̱��ڽ,���ǂނ�
																// ͯ�ނ̻��ޏ������Ƃ�mapDataBase��resize����B
	mapDataBase.resize(exportData.sizeX * exportData.sizeY);
	fread(mapDataBase.data(), sizeof(MAP_ID), mapDataBase.size(), file);
	fclose(file);
	bool flag = true;

	if ((std::string)exportData.fileID != MAP_FILE_BASE_ID)
	{
		flag = false;
	}
	if (exportData.verID != MAP_FILE_BASE_VER_ID)
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
			mapDataBase[j] = (MAP_ID::YUKA);
		}
		for (auto &data : mapDataBase)			//�@�Q�Ƃɂ��Ă����邱�Ƃŏ����������ł���悤�ɂȂ�
		{
			data = MAP_ID::YUKA;
		}
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
				case (MAP_ID::YUKA):		
					if (makeflag)
					{
						break;
					}
					else
					{
						//obj = AddObjList()(objList, std::make_unique<Player>(VECTOR2(x * chipSize.x, y * chipSize.y),drawOffset + VECTOR2(0, -20)));	//�ݽ�ݽ
						makeflag = true;
					}
				case (MAP_ID::IWA):
				case (MAP_ID::HOLE):
				case (MAP_ID::UNTI):
				case (MAP_ID::EKI):
				case (MAP_ID::NULLL):
				case (MAP_ID::WIND):
				case (MAP_ID::MAGIC):
				case (MAP_ID::MAGIC1):
				case (MAP_ID::BORN):
				case (MAP_ID::ESA):
				case (MAP_ID::TOOL):
				break;
			}
			//obj = AddObjList()(objList, std::make_unique<Player>(VECTOR2(x * chipSize.x, y * chipSize.y), drawOffset + VECTOR2(0, -20)));	//�ݽ�ݽ
		}
		ListObj_itr obj;
		obj = AddObjList()(objList, std::make_unique<Player>(VECTOR2(0, 0), drawOffset + VECTOR2(0, -30)));	//�ݽ�ݽ
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