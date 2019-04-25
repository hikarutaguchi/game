#pragma once
#include <vector>
#include <array>
#include "VECTOR2.h"
#include "classObj.h"
#include "FIRE_DIR.h"
#include "MapID.h"

//炎が接触した時
enum class FIRE_ACT {
	NON,			// 延焼する
	STOP,			// 延焼しない
	STOP_BREAK,		// 延焼しない、そのﾏｽの地形を消す
	POP_ENEMY,		// 延焼し、かつ敵が出現
	ERR,			// ｴﾗｰ
	MAX
};


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
	void DrawFire(void);

	bool SetUp(const VECTOR2& size, const VECTOR2 & chipSize, const VECTOR2 drawOffset);	// ﾏｯﾌﾟのｾｯﾄｱｯﾌﾟ
	bool SetMapData(const VECTOR2& pos, MAP_ID id);											// ﾏｯﾌﾟﾃﾞｰﾀの書き込み
	bool SetFireMapData(const VECTOR2& pos, FIRE_DIR dir);									// ﾌｧｲｱﾏｯﾌﾟﾃﾞｰﾀの書き込み
	MAP_ID GetMapData(const VECTOR2& pos);													// 読み込み用関数
	unsigned int GetFireMapData(const VECTOR2& pos);										// 爆弾ﾏｯﾌﾟ書き込み

	bool MapSave(void);																		// ﾏｯﾌﾟｾｰﾌﾞ
	bool MapLoad(sharedListObj objList, bool editModeFlag);									// ﾏｯﾌﾟﾛｰﾄﾞ	
	bool SetUpGameObj(sharedListObj objList, bool editModeFlag);							// ｵﾌﾞｼﾞｪｸﾄのｾｯﾄ
	const VECTOR2& GetChipSize(void);														// ﾁｯﾌﾟｻｲｽﾞを受け取る
	const VECTOR2& GetMapSize(void);														// ﾏｯﾌﾟｻｲｽﾞを受け取る
private:
	MapCtl();
	~MapCtl();

	void InitTblData(void);		//ﾃｰﾌﾞﾙの初期化

	std::vector<MAP_ID>  mapDataBase;
	std::vector<MAP_ID*> mapData;
	std::vector<unsigned int>  fire_mapDataBase;
	std::vector<unsigned int*> fire_mapData;

	std::array<double, static_cast<unsigned int>(FIRE_DIR::MAX)> rotaPtnTbl;	//回転ﾊﾟﾀｰﾝﾃｰﾌﾞﾙ
	std::array<FIRE_ACT, static_cast<unsigned int>(MAP_ID::MAX)> fireActTbl;

	VECTOR2 mapSize;		//　ﾏｯﾌﾟｻｲｽﾞ
	VECTOR2 chipSize;		//　ﾁｯﾌﾟｻｲｽﾞ
	VECTOR2 drawOffset;		//　ｵﾌｾｯﾄ情報をGet


	int bgImage;			//	背景用のｸﾞﾗﾌｨｯｸﾊﾝｿﾙ

	template<typename mapType,typename idType>
	bool SetData(mapType maps,const VECTOR2& pos, idType id);								// ﾏｯﾌﾟﾃﾞｰﾀの書き込み

	template<typename mapType,typename idType>
	idType GetData(mapType maps, const VECTOR2& pos, idType defid);							// ﾏｯﾌﾟﾃﾞｰﾀ読み込み

};

