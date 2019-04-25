#include <type_traits>
#include <memory>
#include "DxLib.h"
#include "ImageMng.h"
#include "SceneMng.h"
#include "MapCtl.h"
#include "EditScene.h"
#include "Player.h"
#include "FIRE_DIR.h"

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
	//�����������Ă����猸�Z�������s���B
	for (auto& data : fire_mapDataBase)		// ���o�����ް���ύX���Ȃ��ƂȂ̂ŎQ�Ƃ���B�ꏊ�ɑ΂��ı������Ď��o�������B
	{
		if (data)//�ް���4����-1���Ă����B
		{
			for (auto dir : FIRE_DIR())
			{
				//if (data & (0xff << (static_cast<int>(dir) * 8)))	// �Y���ް��ɐ��������邩����
				//{
				//	data -= (1 << (static_cast<int>(dir) * 8));
				//}
				data -= (( (data & (0xff << (static_cast<int>(dir) * 8)) ) > 0) << (static_cast<int>(dir) * 8));
					_RPTN(_CRT_WARN, "fire:%d\n", (data >> (static_cast<int>(dir) * 8)) & 0xff);
			}
			
		}
	}
}

void MapCtl::Draw(bool editModeFlag)
{
	if (!editModeFlag)
	{
		DrawGraph(0, 0, bgImage, false);
		//int AnimCnt = 0;
		//for (int y = 0; y < mapSize.y; y++)
		//{
		//	AnimCnt = y % 2;
		//	for (int x = 0; x < mapSize.x; x++)
		//	{
		//		{
		//			DrawGraph(drawOffset.x + x * chipSize.x, drawOffset.y + y * chipSize.y, lpImageMng.GetID("image/map.png")[(AnimCnt % 2) + 1], true);
		//			AnimCnt++;
		//		}
		//	}
		//}
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
	DrawFire();
}

void MapCtl::DrawFire(void)
{
	
	//���e�̏c��Ұ��݂̑I���v�Z
	auto revNum = [](int cnt) 
	{
		return ((FIRE_ANIM_TOP - abs( FIRE_ANIM_TOP - (FIRE_ANIM_TOTAL_FRAME - cnt) / FIRE_ANIM_FRAME )) * FIRE_ANIM_PTN_X);
	};


	//������������Ӱ�ނȂǂ��g���āA�������Ȃǂ��o���Ă��ǂ�
	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			if ((fire_mapData[y][x] & 0xffff0000) && (fire_mapData[y][x] & 0x0000ffff))			//�㉺�ƍ��E�̉��ް����m�肵�Ď��
			{
				//�����N���X���Ă���ꍇ
				auto cnt = 0;

				auto numCmp = [=](auto num) {return num > cnt ? num : cnt;};
				for (auto fire_dir : FIRE_DIR())
				{
					cnt = numCmp(fire_mapData[y][x] >> ((static_cast<unsigned int>(fire_dir) * 8)) & 0xff);
				}

				DrawGraph(drawOffset.x + x * chipSize.x, drawOffset.y + y * chipSize.y, lpImageMng.GetID("image/fire.png")[revNum(cnt)],true);
			}
			else
			{
				//�����N���X���Ă��Ȃ����A�����Ȃ��ꍇ
				for (auto fire_dir : FIRE_DIR())
				{
					//�Y���ꏊ�ɉ������邩����
					auto cnt = (fire_mapData[y][x] >> ( (static_cast<unsigned int>(fire_dir) * 8) ) & 0xff);	//�Y���ꏊ���ް�����ԉ��ʂ��޲ĂɎc���A0xff��Ͻ��ް��Ƃ����B
					if (cnt)
					{
						//�K���ɂ��邩���Ȃ�������
						auto endFlag = [=]() 
						{
							//���������i�s���Ă������+1Ͻ�ɉ������邩�ǂ���
							VECTOR2 addPos {x,y};	//Ͻ��
							if (fire_dir < FIRE_DIR::UP)		//���E
							{
								addPos.x += ((static_cast<unsigned int>(fire_dir) * 2) - 1);
							}
							else
							{	//�㉺
								addPos.y += (((static_cast<unsigned int>(fire_dir) - 2) * 2) - 1);
							}
							if (addPos >= VECTOR2(0,0) && (addPos < mapSize))	//�͈�����������	addPos��mapSize
							{
								// �ް��������޲Ă܂ō~�낵��0xff�Ʊ��ނ��Ƃ邩,Ͻ��ް��Ʊ��ނ����
								return (1 - ((fire_mapData[addPos.y][addPos.x] >> (static_cast<unsigned int>(fire_dir) * 8) & 0xff) > 0));
							}
							return 1;		//�͈͊O�Ȃ�1��Ԃ�
						};
						//DrawGraph(drawOffset.x + x * chipSize.x, drawOffset.y + y * chipSize.y,lpImageMng.GetID("image/fire.png")[0],true);
						DrawRotaGraph(drawOffset.x + x * chipSize.x + chipSize.x / 2, drawOffset.y + y * chipSize.y + chipSize.y / 2,
										1.0, RAD(rotaPtnTbl[static_cast<unsigned int>(fire_dir)]), lpImageMng.GetID("image/fire.png")[revNum(cnt) + 1], true);
					}
				}

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
	createMap(fire_mapDataBase, fire_mapData, 0);

	//���̉摜�̋�ǂ�
	lpImageMng.GetID("image/fire.png", { 20,20 }, { 3,4 });

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
					DrawGraph(drawOffset.x + x * chipSize.x, drawOffset.y + y * chipSize.y, lpImageMng.GetID("image/map.png")[(AnimCnt % 2) + 1], true);
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

bool MapCtl::SetFireMapData(const VECTOR2 & pos, FIRE_DIR dir)
{
	auto actType = fireActTbl[static_cast<unsigned int>(GetMapData(pos))];
	//�X�g�b�v��BREAK�̏ꍇ��returnfalse
	if (actType == FIRE_ACT::STOP || actType == FIRE_ACT::STOP_BREAK)
	{
		return false;
	}
	if (actType == FIRE_ACT::ERR)
	{
		_RPTN(_CRT_WARN, "FIRE_ACT_ERR:%d\n", fireActTbl[static_cast<unsigned int>(GetMapData(pos))]);
		return false;
	}

	auto fire = [=]() {
		unsigned int rtnID = GetFireMapData(pos);	//���݂̃r�b�g
		rtnID &=  (~(0xff << (static_cast<unsigned int>(dir)) * 8));	// ���̃r�b�g�𗎂Ƃ�
		rtnID |= (FIRE_ANIM_TOTAL_FRAME << (static_cast<unsigned int>(dir) * 8));			// �V�����������ރf�[�^	

		return rtnID;
	};

	return SetData(fire_mapData, pos, fire());
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

unsigned int MapCtl::GetFireMapData(const VECTOR2 & pos)
{
	return GetData(fire_mapData, pos, 0);
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
	rotaPtnTbl = {
		180.0,		//��
		0.0,		//�E
		270.0,		//��
		90.0		//��
	};

	fireActTbl = {
		FIRE_ACT::ERR,				//CUR,				// ����
		FIRE_ACT::ERR,				//FLOOR1,
		FIRE_ACT::ERR,				//FLOOR2,
		FIRE_ACT::NON,				//BOMB,
		FIRE_ACT::NON,				//NON,
		FIRE_ACT::STOP,				//WALL1,
		FIRE_ACT::STOP,				//WALL2,
		FIRE_ACT::STOP_BREAK,		//BLOCK,			// �󂹂���	
		FIRE_ACT::POP_ENEMY,		//ITEM_FIRE,
		FIRE_ACT::POP_ENEMY,		//ITEM_BOMB,
		FIRE_ACT::POP_ENEMY,		//ITEM_CTL,		// �N�����۰�
		FIRE_ACT::POP_ENEMY,		//ITEM_SPEED,
	};

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
					obj = AddObjList()(objList, std::make_unique<Player>(VECTOR2(x * chipSize.x, y * chipSize.y),drawOffset + VECTOR2(0, -20)));	//�ݽ�ݽ
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
		}
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