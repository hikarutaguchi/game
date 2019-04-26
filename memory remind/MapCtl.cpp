#include <type_traits>
#include <memory>
#include "DxLib.h"
#include "ImageMng.h"
#include "SceneMng.h"
#include "MapCtl.h"
#include "EditScene.h"
#include "Player.h"

struct DataHeader {
	char fileID[13];					// ファイルのID情報
	char verID;							// バージョン番号
	char reserve1[2];					// 2ﾊﾞｲﾄのﾀﾞﾐｰ,予約領域
	int sizeX;							// マップのﾏｽ目数X
	int sizeY;							// マップのﾏｽ目数Y
	char reserve2[3];					// 3ﾊﾞｲﾄのﾀﾞﾐｰ,予約領域
	char sum;							// sum値

};

#define BOMBERMAN_FILE_ID "BBM_MAP_DATA"
#define BOMBERMAN_VER_ID 0x01			// ﾌｧｲﾙﾊﾞｰｼﾞｮﾝ番号
#define lpSceneMng SceneMng::GetInstance()

// 炎のｱﾆﾒｰｼｮﾝ
#define FIRE_ANIM_FRAME 7										// 1ｺﾏ当たりのﾌﾚｰﾑ数
#define FIRE_ANIM_CNT	7										// 総ｺﾏ数
#define FIRE_ANIM_TOP	(FIRE_ANIM_CNT / 2)						// ｱﾆﾒｰｼｮﾝ折り返しｺﾏ位置
#define FIRE_ANIM_TOTAL_FRAME (FIRE_ANIM_FRAME * FIRE_ANIM_CNT)	// 総ﾌﾚｰﾑ数
#define FIRE_ANIM_PTN_X 3										// 炎の種類(クロス、横棒、尻尾)


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
			case (MAP_ID::NON):		//常に表示しない
				break;
			case (MAP_ID::BOMB):
				//if (lpSceneMng.CheckEditMode())
				//{
				//	DrawGraph(drawOffset.x + x * chipSize.x, drawOffset.y + y * chipSize.y, lpImageMng.GetID("image/map.png")[MAP_ID_CUR], true);
				//}
				//↑でも良いが↓のほうが良き
				if (!editModeFlag)
				{
					break;		//ｴﾃﾞｨｯﾄﾓｰﾄﾞ時は描画するので、そのまま下に処理を流す
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
				// ｴﾗｰ
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
	lpImageMng.GetID("image/map.png", VECTOR2(20, 20), VECTOR2(4, 3));	//ﾏｯﾌﾟをよんでいたらｽﾙｰ

	//画面解像度とﾁｯﾌﾟｻｲｽﾞを受け取った
	mapSize = VECTOR2(size.x / chipSize.x, size.y / chipSize.y);
	MapCtl::chipSize = chipSize;
	MapCtl::drawOffset = drawOffset;		//ｵﾌｾｯﾄ情報をGet

	auto createMap = [=](auto& base, auto& front, auto initNum) {

		base.resize(mapSize.x * mapSize.y);	//要素として全体のｻｲｽﾞを確保
		front.resize(mapSize.y);			//縦に何個いれるか
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

	if (bgImage <= 0)	//	背景が作られてなかったら入る
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
		if ((selPos.x < 0) || (selPos.y < 0) || (mapSize.x <= selPos.x) || (mapSize.y <= selPos.y))		//範囲ﾁｪｯｸ
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
bool MapCtl::SetData(mapType maps, const VECTOR2 & pos, idType id)		//inlineは使用するプログラムにそのまま展開
{
	VECTOR2 selPos;
	selPos.x = pos.x / chipSize.x;
	selPos.y = pos.y / chipSize.y;
	CheckSize checkSize;			//一回実体を作ってやって、関数を呼び出すみたいにするやつ
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
	//posは座標
	VECTOR2 selPos;
	selPos.x = pos.x / chipSize.x;
	selPos.y = pos.y / chipSize.y;

	CheckSize checkSize;			// 一回実体を作ってやって、関数を呼び出すみたいにするやつ
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
		{ 0,0 },			// 配列を明示的にする
		mapSize.x,
		mapSize.y,
		{ 0,0,0 },			// 配列を明示的にする
		(char)0xff
	};

	int sum = 0;				// sum値の計算
	for (unsigned int j = 0; j < mapDataBase.size(); j++)
	{
		sum += (int)mapDataBase[j];
	}

	exportData.sum = (char)sum;

	FILE *file;																// ファイルポインタ
	fopen_s(&file, "data/mapdata.map", "wb");								// ファイルを開く
	fwrite(&exportData, sizeof(exportData), 1, file);						// 書き込む
	fwrite(mapDataBase.data(), sizeof(MAP_ID), mapDataBase.size(), file);
	fclose(file);															// ファイルを閉じる

	return true;
}

bool MapCtl::MapLoad(sharedListObj objList, bool editModeFlag)//
{

	FILE *file;													// ファイルポインタ
	DataHeader exportData;
	fopen_s(&file, "data/mapdata.map", "rb");					// ファイルを開く
	fread(&exportData, sizeof(exportData), 1, file);			// 読み出し先のｱﾄﾞﾚｽ,何個読むか
																// ﾍｯﾀﾞのｻｲｽﾞ情報をもとにmapDataBaseをresizeする。
	mapDataBase.resize(exportData.sizeX * exportData.sizeY);
	fread(mapDataBase.data(), sizeof(MAP_ID), mapDataBase.size(), file);
	fclose(file);
	bool flag = true;
	//int sum = 0;				//sum値の計算
	//for (int j = 0; j < mapDataBase.size(); j++)
	//{
	//	sum += (int)mapDataBase[j];
	//}
	//ﾍｯﾀﾞのﾌｧｲﾙＩＤ情報と内部で持っているＩＤと比べる
	//ﾍｯﾀﾞのﾊﾞｰｼﾞｮﾝ番号と内部で持っているＩＤを比べる
	if ((std::string)exportData.fileID != BOMBERMAN_FILE_ID)
	{
		flag = false;
	}
	if (exportData.verID != BOMBERMAN_VER_ID)
	{
		flag = false;
	}
	//sum値を計算して、ﾍｯﾀﾞｰのsum値と違っていたら、ﾃﾞｰﾀをｸﾘｱ
	int sum = 0;				//sum値の計算
	for (unsigned int j = 0; j < mapDataBase.size(); j++)
	{
		sum += (int)mapDataBase[j];			//今はint
	}
	if (exportData.sum != (char)sum)		//charで明示的にｷｬｽﾄしないと4byteから1byteは大きいものは切り捨てられる
	{
		flag = false;
	}
	//ﾃﾞｰﾀのｸﾘｱ
	if (flag == false)
	{
		for (unsigned int j = 0; j < mapDataBase.size(); j++)
		{
			mapDataBase[j] = (MAP_ID::NON);
		}
		//for (auto &data : mapDataBase)			//　参照にしてあげることで書き換えができるようになる
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
			case (MAP_ID::BOMB):		//ﾌﾟﾚｲﾔｰｷｬﾗをｲﾝｽﾀﾝｽ
				if (makeflag)
				{
					break;
				}
				{
					//obj = AddObjList()(objList, std::make_unique<Player>(VECTOR2(x * chipSize.x, y * chipSize.y),drawOffset + VECTOR2(0, -20)));	//ｲﾝｽﾀﾝｽ
					makeflag = true;
				}
				break;
			case (MAP_ID::NON) :		//常に表示しない
			case (MAP_ID::WALL1) :
			case (MAP_ID::WALL2) :
			case (MAP_ID::BLOCK) :
			case (MAP_ID::ITEM_FIRE) :
			case (MAP_ID::ITEM_BOMB) :
			//case (MAP_ID::ITEM_CTL) :
			//case (MAP_ID::ITEM_SPEED) :
				break;				//何もしない
			case (MAP_ID::CUR) :
			case (MAP_ID::FLOOR1) :
			case (MAP_ID::FLOOR2) :
			default:
				// ｴﾗｰ
				break;
			}
			//obj = AddObjList()(objList, std::make_unique<Player>(VECTOR2(x * chipSize.x, y * chipSize.y), drawOffset + VECTOR2(0, -20)));	//ｲﾝｽﾀﾝｽ
		}
		ListObj_itr obj;
		obj = AddObjList()(objList, std::make_unique<Player>(VECTOR2(200,200), drawOffset + VECTOR2(0, -20)));	//ｲﾝｽﾀﾝｽ
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