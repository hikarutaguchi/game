#include "DxLib.h"
#include "ImageMng.h"

//ImageMng* ImageMng::s_instance = nullptr;
//std::once_flag ImageMng::InitFlag;

const VEC_INT& ImageMng::GetID(std::string f_name)
{
	//存在しているか問い合わせる ｸﾗｽのﾒﾝﾊﾞにｱｸｾｽはﾄﾞｯﾄ	見つかったらそのﾎﾟｲﾝﾀが返ってくる　なかったら終端(end)のｱﾄﾞﾚｽが返ってくる
	if (imgMap.find(f_name) == imgMap.end())
	{
		imgMap[f_name].resize(1);
		imgMap[f_name][0] = LoadGraph(f_name.c_str());
	}
	return imgMap[f_name];
}

const VEC_INT & ImageMng::GetID(std::string f_name, VECTOR2 divSize, VECTOR2 divCnt)
{
	if (imgMap.find(f_name) == imgMap.end())
	{
		imgMap[f_name].resize(divCnt.x*divCnt.y);
		LoadDivGraph(f_name.c_str(), divCnt.x*divCnt.y, divCnt.x, divCnt.y,
			divSize.x, divSize.y, &imgMap[f_name][0], true);
	}
	return imgMap[f_name];
}





ImageMng::ImageMng()
{

}


ImageMng::~ImageMng()
{

}


