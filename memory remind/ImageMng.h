#pragma once
#include <vector>
#include <map>
#include <mutex>
#include "VECTOR2.h"

//using namespace std;
using VEC_INT = std::vector<int>;
#define lpImageMng ImageMng::GetInstance()
#define IMAGE_ID(X) (ImageMng::GetInstance().GetID(X))

class ImageMng
{
public:
	static ImageMng &GetInstance(void)											// Ã“I‚È¼İ¸ŞÙÄİ
	{
		static ImageMng s_instance;
		return s_instance;
	}

	const VEC_INT& GetID(std::string f_name);									// ‰æ‘œî•ñæ“¾
	const VEC_INT& GetID(std::string f_name, VECTOR2 divSize, VECTOR2 divCnt);	// ‰æ‘œî•ñæ“¾(–¼‘O,»²½Ş,ºÏ”)
private:
	ImageMng();
	~ImageMng();
	std::map<std::string, VEC_INT> imgMap;
};

