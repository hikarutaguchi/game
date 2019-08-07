//#include <type_traits>
//#include <memory>
#include "DxLib.h"
#include "ImageMng.h"
#include "SceneMng.h"
#include "MapCtl.h"
#include "Game_ctr.h"
#include "SelectCur.h"
#include "Slime.h"
#include "Skelton.h"
#include "Carbuncle.h"
//#include "EditScene.h"
//#include "Player.h"

struct DataHeader {
	char fileID[13];					// ファイルのID情報
	char verID;							// バージョン番号
	char reserve1[2];					// 2ﾊﾞｲﾄのﾀﾞﾐｰ,予約領域
	int sizeX;							// マップのﾏｽ目数X
	int sizeY;							// マップのﾏｽ目数Y
	char reserve2[3];					// 3ﾊﾞｲﾄのﾀﾞﾐｰ,予約領域
	char sum;							// sum値
};

struct DataHeaderBase {
	char fileID[14];					// ファイルのID情報
	char verID;							// バージョン番号
	char reserve1[2];					// 2ﾊﾞｲﾄのﾀﾞﾐｰ,予約領域
	int sizeX;							// マップのﾏｽ目数X
	int sizeY;							// マップのﾏｽ目数Y
	char reserve2[3];					// 3ﾊﾞｲﾄのﾀﾞﾐｰ,予約領域
	char sum;							// sum値
};

#define MAP_FILE_ID "BBM_MAP_DATA"
#define MAP_FILE_BASE_ID  "MAP_DATA_BASE"
#define MAP_FILE_VER_ID 0x01			// ﾌｧｲﾙﾊﾞｰｼﾞｮﾝ番号
#define MAP_FILE_BASE_VER_ID 0x01

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
	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			MAP_ID id = mapData[y][x];
			switch (id)
			{
			case (MAP_ID::HOLE):
				if (editModeFlag == false)
				{
					DrawGraph(drawOffset.x + x * chipSize.x, drawOffset.y + y * chipSize.y, lpImageMng.GetID("image/yukas.png")[static_cast<int>(MAP_ID::YUKA)], true);
					break;
				}
			case (MAP_ID::YUKA):
			case (MAP_ID::IWA):
			case (MAP_ID::UNTI):
			case (MAP_ID::EKI):
			case (MAP_ID::NULLL):
			case (MAP_ID::WIND):
			case (MAP_ID::MAGIC):
			case (MAP_ID::MAGIC1):
			case (MAP_ID::BORN):
			case (MAP_ID::ESA):
			case (MAP_ID::TOOL):
			case (MAP_ID::GOAL):
			case (MAP_ID::NON1):
			case (MAP_ID::NON2):
			case (MAP_ID::NON3):
				DrawGraph(drawOffset.x + x * chipSize.x, drawOffset.y + y * chipSize.y, lpImageMng.GetID("image/yukas.png")[static_cast<int>(id)], true);
				break;
				// ｴﾗｰ
#ifdef _DEBUG
				DrawGraph(drawOffset.x + x * chipSize.x, drawOffset.y + y * chipSize.y, lpImageMng.GetID("image/yukas.png")[static_cast<int>(MAP_ID::UNTI)], true);
#endif
				break;
			}
		}
	}
}

bool MapCtl::SetUp(const VECTOR2 & size, const VECTOR2 & chipSize, const VECTOR2 drawOffset)
{
	lpImageMng.GetID("image/yukas.png", VECTOR2(64, 64), VECTOR2(4, 4));	//ﾏｯﾌﾟをよんでいたらｽﾙｰ

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

	createMap(mapDataBase, mapData, MAP_ID::YUKA);

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
	bool operator ()(const VECTOR2 &selPos, const VECTOR2 &mapSize) {
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

	if ((maps[selPos.y][selPos.x]) == MAP_ID::IWA || (maps[selPos.y][selPos.x]) == MAP_ID::GOAL)
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

MAP_ID MapCtl::GetMapID(const VECTOR2 & pos, MAP_ID id)
{
	return GetDataID(mapData, pos, id);
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

template<typename mapType, typename idType>
idType MapCtl::GetDataID(mapType maps, const VECTOR2 pos, idType ID)
{
	VECTOR2 selPos;
	selPos.x = (pos.x + 32) / chipSize.x;
	selPos.y = (pos.y + 50) / chipSize.y;

	//CheckSize checkSize;			// 一回実体を作ってやって、関数を呼び出すみたいにするやつ
	//if ((!checkSize(selPos, mapSize)))
	//{
	//	return defid;
	//}
	ID = maps[selPos.y][selPos.x];

	_RPTN(_CRT_WARN, "wroad[%d]\n", ID);
	return ID;
}

bool MapCtl::MapSave(void)
{
	DataHeader exportData = {
		MAP_FILE_ID,
		MAP_FILE_VER_ID,
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

bool MapCtl::MapLoad(sharedListObj objList,  bool editModeFlag)//
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

	if ((std::string)exportData.fileID != MAP_FILE_ID)
	{
		flag = false;
	}
	if (exportData.verID != MAP_FILE_VER_ID)
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
			mapDataBase[j] = (MAP_ID::YUKA);
		}
		for (auto &data : mapDataBase)			//　参照にしてあげることで書き換えができるようになる
		{
			data = MAP_ID::YUKA;
		}
	}
	if (flag == true)
	{
		SetUpGameObj(objList,editModeFlag);
	}
	return flag;
}

bool MapCtl::MapSaveBase(void)
{
	DataHeaderBase exportData = {
		MAP_FILE_BASE_ID,
		MAP_FILE_BASE_VER_ID,
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
	fopen_s(&file, "data/mapdatabase.map", "wb");								// ファイルを開く
	fwrite(&exportData, sizeof(exportData), 1, file);						// 書き込む
	fwrite(mapDataBase.data(), sizeof(MAP_ID), mapDataBase.size(), file);
	fclose(file);															// ファイルを閉じる

	return true;
}

bool MapCtl::MapLoadBase(sharedListObj objList, bool editModeFlag)
{
	FILE *file;													// ファイルポインタ
	DataHeaderBase exportData;
	fopen_s(&file, "data/mapdatabase.map", "rb");					// ファイルを開く
	fread(&exportData, sizeof(exportData), 1, file);			// 読み出し先のｱﾄﾞﾚｽ,何個読むか
																// ﾍｯﾀﾞのｻｲｽﾞ情報をもとにmapDataBaseをresizeする。
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
			mapDataBase[j] = (MAP_ID::YUKA);
		}
		for (auto &data : mapDataBase)			//　参照にしてあげることで書き換えができるようになる
		{
			data = MAP_ID::YUKA;
		}
	}
	if (flag == true)
	{
		SetUpGameObj(objList,editModeFlag);
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
	postbl = {
		VECTOR2{64,64},
		VECTOR2{64,128},
		VECTOR2{64,192},
		VECTOR2{64,256}
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
				case (MAP_ID::YUKA):		
					if (makeflag)
					{
						break;
					}
					else
					{
						//obj = AddObjList()(objList, std::make_unique<Player>(VECTOR2(x * chipSize.x, y * chipSize.y),drawOffset + VECTOR2(0, -20)));	//ｲﾝｽﾀﾝｽ
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
		}
		ListObj_itr obj;
		// GetCharDataでもらった各プレイヤーのキャラIDでキャラクターをインスタンス
		for (int i = 0; i < 3; i++)
		{
			if (lpSelCur.GetCharFlag(P_TYPE(i)))
			{
				if (lpSelCur.GetPlayerFlag(P_TYPE(i)))
				{
					if (lpSelCur.GetCharData(P_TYPE(i)) == 1)
					{
						obj = AddObjList()(objList, std::make_unique<Slime>(drawOffset + VECTOR2(0, -30)));	//ｲﾝｽﾀﾝｽ
					}
					if (lpSelCur.GetCharData(P_TYPE(i)) == 2)
					{
						obj = AddObjList()(objList, std::make_unique<Skelton>(drawOffset + VECTOR2(0, -30)));	//ｲﾝｽﾀﾝｽ
					}
					if (lpSelCur.GetCharData(P_TYPE(i)) == 3)
					{
						obj = AddObjList()(objList, std::make_unique<Carbuncle>(drawOffset + VECTOR2(0, -30)));	//ｲﾝｽﾀﾝｽ
					}
				}
				//obj = AddObjList()(objList, std::make_unique<Carbuncle>((VECTOR2(postbl[CONTROLLER_P1])), drawOffset + VECTOR2(0, -30)));	//ｲﾝｽﾀﾝｽ
				//objList->pop_back();
			}
		}
			//obj = AddObjList()(objList, std::make_unique<Carbuncle>((VECTOR2(postbl[CONTROLLER_P1])), drawOffset + VECTOR2(0, -30)));	//ｲﾝｽﾀﾝｽ
			//objList->pop_back();
			//if (lpSelCur.GetCharFlag(CONTROLLER_P2))
			//{
			//	if (lpSelCur.GetPlayerFlag(CONTROLLER_P2))
			//	{

			//		if (lpSelCur.GetCharData(CONTROLLER_P2) == 1)
			//		{
			//			obj = AddObjList()(objList, std::make_unique<Slime>(drawOffset + VECTOR2(0, -30)));	//ｲﾝｽﾀﾝｽ
			//		}
			//		if (lpSelCur.GetCharData(CONTROLLER_P2) == 2)
			//		{
			//			obj = AddObjList()(objList, std::make_unique<Skelton>((VECTOR2(postbl[CONTROLLER_P2])), drawOffset + VECTOR2(0, -30)));	//ｲﾝｽﾀﾝｽ
			//		}
			//		if (lpSelCur.GetCharData(CONTROLLER_P2) == 3)
			//		{
			//			obj = AddObjList()(objList, std::make_unique<Carbuncle>((VECTOR2(postbl[CONTROLLER_P2])), drawOffset + VECTOR2(0, -30)));	//ｲﾝｽﾀﾝｽ
			//		}
			//		//objList->pop_front();
			//	}
			//}
			//obj2 = AddObjList2()(objList2, std::make_unique<Carbuncle>((VECTOR2(postbl[CONTROLLER_P2])), drawOffset + VECTOR2(0, -30)));	//ｲﾝｽﾀﾝｽ
			//objList2->pop_back();
		//for (int i = 0; i < CONTROLLER_MAX; i++)
		//{
		//	if (lpSelCur.GetCharFlag((P_TYPE)i))
		//	{
		//		if (lpSelCur.GetPlayerFlag((P_TYPE)i))
		//		{
		//			obj[i] = AddObjList()(objList, std::make_unique<Player>(postbl[i], drawOffset + VECTOR2(0, -20)));	//ｲﾝｽﾀﾝｽ
		//		}
		//	}
		//}
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