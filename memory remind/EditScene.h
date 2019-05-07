#pragma once
#include <list>
#include "Obj.h"
#include "BaseScene.h"
#include "classObj.h"


class EditScene :
	public BaseScene
{
public:
	EditScene();
	~EditScene();
	virtual unique_Base Updata(unique_Base own, const Game_ctr &controller);

private:
	sharedListObj objList;			// ²İ½Àİ½‚µ‚½î•ñ‚ğ“o˜^
	int Init(void);					// ŒÄ‚Ño‚µ
	void Text();					// •¶š•\¦ŠÖ”
	bool EditDraw();				// ´ÃŞ¨¯Ä•\¦
	VECTOR2 Drawpos;
	int Pad[4];
	bool padFlag;
};
