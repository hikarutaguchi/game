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
	static ImageMng &GetInstance(void)											// �ÓI�ȼݸ����
	{
		static ImageMng s_instance;
		return s_instance;
	}

	const VEC_INT& GetID(std::string f_name);									// �摜���擾
	const VEC_INT& GetID(std::string f_name, VECTOR2 divSize, VECTOR2 divCnt);	// �摜���擾(���O,����,�ϐ�)
private:
	ImageMng();
	~ImageMng();
	std::map<std::string, VEC_INT> imgMap;
};

