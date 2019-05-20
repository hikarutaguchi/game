#pragma once
#include <vector>
#include <array>
#include "VECTOR2.h"
#include "classObj.h"
#include "MapID.h"

#define lpMapCtl MapCtl::GetInstance()
#define PI 3.141592654
#define RAD(X) ( (X * PI) / 180.0)			// Xは度数

class MapCtl
{
public:
	// 静的なｼﾝｸﾞﾙﾄﾝ
	static MapCtl &GetInstance(void)
	{
		static MapCtl s_instance;
		return s_instance;
	}
	void Updata(void);

	void Draw(bool editModeFlag);															// ﾏｯﾌﾟ描画

	bool SetUp(const VECTOR2& size, const VECTOR2 & chipSize, const VECTOR2 drawOffset);	// ﾏｯﾌﾟのｾｯﾄｱｯﾌﾟ
	bool SetMapData(const VECTOR2& pos, MAP_ID id);											// ﾏｯﾌﾟﾃﾞｰﾀの書き込み
	MAP_ID GetMapData(const VECTOR2& pos);													// 読み込み用関数
	MAP_ID GetMapID(const VECTOR2& pos, MAP_ID id);

	bool MapSave(void);																		// ﾏｯﾌﾟｾｰﾌﾞ
	bool MapLoad(sharedListObj objList, bool editModeFlag);									// ﾏｯﾌﾟﾛｰﾄﾞ
	bool MapSaveBase(void);
	bool MapLoadBase(sharedListObj objList, bool editModeFlag);								// ﾏｯﾌﾟﾛｰﾄﾞ	
	bool SetUpGameObj(sharedListObj objList, bool editModeFlag);							// ｵﾌﾞｼﾞｪｸﾄのｾｯﾄ
	const VECTOR2& GetChipSize(void);														// ﾁｯﾌﾟｻｲｽﾞを受け取る
	const VECTOR2& GetMapSize(void);														// ﾏｯﾌﾟｻｲｽﾞを受け取る
private:
	MapCtl();
	~MapCtl();

	void InitTblData(void);		//ﾃｰﾌﾞﾙの初期化

	std::vector<MAP_ID>  mapDataBase;
	std::vector<MAP_ID*> mapData;

	VECTOR2 mapSize;		//　ﾏｯﾌﾟｻｲｽﾞ
	VECTOR2 chipSize;		//　ﾁｯﾌﾟｻｲｽﾞ
	VECTOR2 drawOffset;		//　ｵﾌｾｯﾄ情報をGet

	int bgImage;			//	背景用のｸﾞﾗﾌｨｯｸﾊﾝｿﾙ

	template<typename mapType,typename idType>
	bool SetData(mapType maps,const VECTOR2& pos, idType id);								// ﾏｯﾌﾟﾃﾞｰﾀの書き込み

	template<typename mapType,typename idType>
	idType GetData(mapType maps, const VECTOR2& pos, idType defid);							// ﾏｯﾌﾟﾃﾞｰﾀ読み込み

	template<typename mapType, typename idType>
	idType GetDataID(mapType maps, const VECTOR2 pos, idType ID);
};

