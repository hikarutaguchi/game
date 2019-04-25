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
	//数字が入っていたら減算処理を行う。
	for (auto& data : fire_mapDataBase)		// 取り出したﾃﾞｰﾀを変更しないとなので参照する。場所に対してｱｸｾｽして取り出す感じ。
	{
		if (data)//ﾃﾞｰﾀを4方向-1していく。
		{
			for (auto dir : FIRE_DIR())
			{
				//if (data & (0xff << (static_cast<int>(dir) * 8)))	// 該当ﾃﾞｰﾀに数字があるかﾁｪｯｸ
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
	DrawFire();
}

void MapCtl::DrawFire(void)
{
	
	//爆弾の縦ｱﾆﾒｰｼｮﾝの選択計算
	auto revNum = [](int cnt) 
	{
		return ((FIRE_ANIM_TOP - abs( FIRE_ANIM_TOP - (FIRE_ANIM_TOTAL_FRAME - cnt) / FIRE_ANIM_FRAME )) * FIRE_ANIM_PTN_X);
	};


	//ここでﾌﾞﾚﾝﾄﾞﾓｰﾄﾞなどを使って、透明感などを出しても良い
	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			if ((fire_mapData[y][x] & 0xffff0000) && (fire_mapData[y][x] & 0x0000ffff))			//上下と左右の炎ﾃﾞｰﾀを確定して取る
			{
				//炎がクロスしている場合
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
				//炎がクロスしていないか、炎がない場合
				for (auto fire_dir : FIRE_DIR())
				{
					//該当場所に炎があるかﾁｪｯｸ
					auto cnt = (fire_mapData[y][x] >> ( (static_cast<unsigned int>(fire_dir) * 8) ) & 0xff);	//該当場所のﾃﾞｰﾀを一番下位のﾊﾞｲﾄに残す、0xffはﾏｽｸﾃﾞｰﾀという。
					if (cnt)
					{
						//尻尾にするかしないか処理
						auto endFlag = [=]() 
						{
							//自分が今進行している方向+1ﾏｽに炎があるかどうか
							VECTOR2 addPos {x,y};	//ﾏｽ目
							if (fire_dir < FIRE_DIR::UP)		//左右
							{
								addPos.x += ((static_cast<unsigned int>(fire_dir) * 2) - 1);
							}
							else
							{	//上下
								addPos.y += (((static_cast<unsigned int>(fire_dir) - 2) * 2) - 1);
							}
							if (addPos >= VECTOR2(0,0) && (addPos < mapSize))	//範囲ﾁｪｯｸをする	addPosがmapSize
							{
								// ﾃﾞｰﾀを下位ﾊﾞｲﾄまで降ろして0xffとｱﾝﾄﾞをとるか,ﾏｽｸﾃﾞｰﾀとｱﾝﾄﾞを取る
								return (1 - ((fire_mapData[addPos.y][addPos.x] >> (static_cast<unsigned int>(fire_dir) * 8) & 0xff) > 0));
							}
							return 1;		//範囲外なら1を返す
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
	createMap(fire_mapDataBase, fire_mapData, 0);

	//炎の画像の空読み
	lpImageMng.GetID("image/fire.png", { 20,20 }, { 3,4 });

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

bool MapCtl::SetFireMapData(const VECTOR2 & pos, FIRE_DIR dir)
{
	auto actType = fireActTbl[static_cast<unsigned int>(GetMapData(pos))];
	//ストップかBREAKの場合はreturnfalse
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
		unsigned int rtnID = GetFireMapData(pos);	//現在のビット
		rtnID &=  (~(0xff << (static_cast<unsigned int>(dir)) * 8));	// 今のビットを落とす
		rtnID |= (FIRE_ANIM_TOTAL_FRAME << (static_cast<unsigned int>(dir) * 8));			// 新しく書き込むデータ	

		return rtnID;
	};

	return SetData(fire_mapData, pos, fire());
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

unsigned int MapCtl::GetFireMapData(const VECTOR2 & pos)
{
	return GetData(fire_mapData, pos, 0);
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
	rotaPtnTbl = {
		180.0,		//左
		0.0,		//右
		270.0,		//上
		90.0		//下
	};

	fireActTbl = {
		FIRE_ACT::ERR,				//CUR,				// ｶｰｿﾙ
		FIRE_ACT::ERR,				//FLOOR1,
		FIRE_ACT::ERR,				//FLOOR2,
		FIRE_ACT::NON,				//BOMB,
		FIRE_ACT::NON,				//NON,
		FIRE_ACT::STOP,				//WALL1,
		FIRE_ACT::STOP,				//WALL2,
		FIRE_ACT::STOP_BREAK,		//BLOCK,			// 壊せるやつ	
		FIRE_ACT::POP_ENEMY,		//ITEM_FIRE,
		FIRE_ACT::POP_ENEMY,		//ITEM_BOMB,
		FIRE_ACT::POP_ENEMY,		//ITEM_CTL,		// 起爆ｺﾝﾄﾛｰﾙ
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
			case (MAP_ID::BOMB):		//ﾌﾟﾚｲﾔｰｷｬﾗをｲﾝｽﾀﾝｽ
				if (makeflag)
				{
					break;
				}
				{
					obj = AddObjList()(objList, std::make_unique<Player>(VECTOR2(x * chipSize.x, y * chipSize.y),drawOffset + VECTOR2(0, -20)));	//ｲﾝｽﾀﾝｽ
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