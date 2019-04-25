#pragma once
#include <array>
#include "FIRE_DIR.h"
#include "Obj.h"

enum class FIRE_LENGTH {
	NOW,		//丂尰嵼偺挿偝
	LIM,		//丂尷奅偺挿偝
	MAX
};

class Bomb :
	public Obj
{
public:
	Bomb(VECTOR2 setupPos, unsigned int length , VECTOR2 drawOffset);
	~Bomb();
private:
	void SetMove(weekListObj objList, const Game_ctr &controller);		// 弮悎壖憐娭悢幚懱懁
	bool InitAnim(void);												// 夋憸屇傃弌偟
	bool CheckDeth(void);												// 冻菽联梡娭悢
	bool CheckObjType(OBJ_TYPE type);									// 堤藜蕺改啦踢联
																		// 无褌虜殧瓊獝L傃偰偄傞偐娗棟偡傞娭悢

	int count;															// 敋敪冻菽	

	unsigned int fireLength[static_cast<unsigned int>(FIRE_LENGTH::MAX)]; // 墛偺挿偝傪奿擺偡傞攝楍

	const std::array<VECTOR2,static_cast<unsigned int>(FIRE_DIR::MAX)> dirPos;
	std::array<bool, static_cast<unsigned int>(FIRE_DIR::MAX)> fireDirFlag;		// 墛偑怢傃偰偄偄偐套皋
};

