#include "DxLib.h"
#include "ImageMng.h"

//ImageMng* ImageMng::s_instance = nullptr;
//std::once_flag ImageMng::InitFlag;

const VEC_INT& ImageMng::GetID(std::string f_name)
{
	//‘¶İ‚µ‚Ä‚¢‚é‚©–â‚¢‡‚í‚¹‚é ¸×½‚ÌÒİÊŞ‚É±¸¾½‚ÍÄŞ¯Ä	Œ©‚Â‚©‚Á‚½‚ç‚»‚ÌÎß²İÀ‚ª•Ô‚Á‚Ä‚­‚é@‚È‚©‚Á‚½‚çI’[(end)‚Ì±ÄŞÚ½‚ª•Ô‚Á‚Ä‚­‚é
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


