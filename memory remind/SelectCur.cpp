#include "DxLib.h"
#include "SelectCur.h"
#include"ImageMng.h"


SelectCur::SelectCur()
{
	CharFlag = {
		false,		// P1
		false,		// P2
		false,		// P3
		false		// P4
	};

	CharID = {
		static_cast<Character>(Character::Slime),		// P1
		static_cast<Character>(Character::Slime),		// P2
		static_cast<Character>(Character::Slime),		// P3
		static_cast<Character>(Character::Slime)		// P4
	};

	posTBL = {
		pos = {170,360},		// P1
		pos = {270,360},		// P2
		pos = {170,360},		// P3
		pos = {170,360}			// P4
	};

	for (int p = 0; p < TYPE_MAX; p++)
	{
		for (int i = 0; i < P_MAX; i++)
		{
			GetCtr[i][p] = PAD_MAX;
		}
	}
}


SelectCur::~SelectCur()
{
	
}

int SelectCur::GetCharData(Cursor playerNum)
{
	if (CharFlag[playerNum])
	{
		return static_cast<int>(CharID[playerNum]);
	}
	return 0;
}

void SelectCur::Draw(void)
{
	ClsDrawScreen();

	for (int i = 0; i < P_MAX; i++)
	{
		//DrawBox(posTBL[P1].x, posTBL[P1].y + 50, posTBL[P1].x + 80, posTBL[P1].y + 120, 0xff00ff, false);

		if (!CharFlag[i])
		{
			DrawBox(posTBL[i].x, posTBL[i].y, posTBL[i].x + 80, posTBL[i].y + 120, 0x0000ff, false);
		}
	}

	DrawGraph(500, 50, lpImageMng.GetID("image/button_UI.png")[2], true);
	DrawGraph(850, 50, lpImageMng.GetID("image/button_UI.png")[4], true);

	DrawGraph(180, 370, lpImageMng.GetID("image/slimes.png", VECTOR2(64, 100), VECTOR2(4, 4))[1], true);
	DrawGraph(540, 370, lpImageMng.GetID("image/skeleton.png", VECTOR2(64, 100), VECTOR2(4, 4))[0], true);
	DrawGraph(900, 370, lpImageMng.GetID("image/Carbuncle.png", VECTOR2(64, 100), VECTOR2(4, 4))[0], true);

#ifdef _DEBUG
	DrawFormatString(0, 0, 0xff0000, "pos1,x = %d", posTBL[P1].x);
	DrawFormatString(0, 15, 0xff0000, "pos2,x = %d", posTBL[P2].x);
	DrawFormatString(0, 100, 0xff0000, "CharID[P1] = %d", static_cast<int>(CharID[P1]));
	DrawFormatString(0, 115, 0xff0000, "CharID[P2] = %d", static_cast<int>(CharID[P2]));
	DrawFormatString(0, 200, 0xff0000, "CharFlag1 = %d", static_cast<int>(CharFlag[P1]));
	DrawFormatString(0, 215, 0xff0000, "CharFlag2 = %d", static_cast<int>(CharFlag[P2]));
	DrawFormatString(0, 300, 0xff0000, "GetCharID1 = %d", static_cast<int>(GetCharData(P1)));
	DrawFormatString(0, 315, 0xff0000, "GetCharID2 = %d", static_cast<int>(GetCharData(P2)));
#endif
	ScreenFlip();
}

void SelectCur::MoveCur(Game_ctr & controller)
{
	VECTOR2 tmpPos1(posTBL[P1]);		//‰¼ˆÚ“®•Ï”	
	VECTOR2 tmpPos2(posTBL[P2]);

	switch (ctrType[P_1])
	{
	case SELECT:
		/*CharFlag[P1] = true;*/
		ctrType[P_1] = TYPE_MAX;
		break;
	case CANSELL:
		CharFlag[P1] = false;
		ctrType[P_1] = TYPE_MAX;
		break;
	case LEFT:
		tmpPos1.x -= 360;

		// CharID‚ðŽæ“¾
		if (tmpPos1.x > 0)
		{
			CharID[P1] = (Character)(CharID[P1] - 1);
		}
		ctrType[P_1] = TYPE_MAX;
		break;
	case RIGHT:
		tmpPos1.x += 360;

		// CharID‚ðŽæ“¾
		if (tmpPos1.x < 1200)
		{
			CharID[P1] = (Character)(CharID[P1] + 1);
		}
		ctrType[P_1] = TYPE_MAX;
		break;
	case TYPE_MAX:
		break;
	default:
		break;

	}

	if (!CharFlag[P1])
	{
		if (GetCtr[P_1][SELECT] == PAD_FREE)
		{
			if (controller.GetCtr(CONTROLLER_1P_INPUT_BUTTON_B, P_1) == PAD_PUSH)
			{
				ctrType[P_1] = SELECT;
			}
		}
		if (GetCtr[P1][RIGHT] == PAD_FREE)
		{
			if (controller.GetCtr(CONTROLLER_1P_INPUT_RIGHT, P_1) == PAD_PUSH)
			{
				ctrType[P_1] = RIGHT;
			}
		}
		if (GetCtr[P1][LEFT] == PAD_FREE)
		{
			if (controller.GetCtr(CONTROLLER_1P_INPUT_LEFT, P_1) == PAD_PUSH)
			{
				ctrType[P_1] = LEFT;
			}
		}
	}
	else
	{
		if (GetCtr[P1][CANSELL] == PAD_FREE)
		{
			if (controller.GetCtr(CONTROLLER_1P_INPUT_BUTTON_Y, P_1) == PAD_PUSH)
			{
				ctrType[P_1] = CANSELL;
			}
		}
	}

	GetCtr[P_1][SELECT] = controller.GetCtr(CONTROLLER_2P_INPUT_BUTTON_B, P_1);
	GetCtr[P_1][RIGHT] = controller.GetCtr(CONTROLLER_2P_INPUT_RIGHT, P_1);
	GetCtr[P_1][LEFT] = controller.GetCtr(CONTROLLER_2P_INPUT_LEFT, P_1);
	GetCtr[P_1][CANSELL] = controller.GetCtr(CONTROLLER_2P_INPUT_BUTTON_Y, P_1);

		switch (ctrType[P_2])
		{
		case SELECT:
			/*CharFlag[P2] = true;*/
			ctrType[P_2] = TYPE_MAX;
			break;
		case CANSELL:
			CharFlag[P2] = false;
			ctrType[P_2] = TYPE_MAX;
			break;
		case LEFT:
			tmpPos2.x -= 360;

			// CharID‚ðŽæ“¾
			if (tmpPos2.x > 0)
			{
				CharID[P2] = (Character)(CharID[P2] - 1);
			}
			ctrType[P_2] = TYPE_MAX;
			break;
		case RIGHT:
			tmpPos2.x += 360;

			// CharID‚ðŽæ“¾
			if (tmpPos2.x < 1200)
			{
				CharID[P2] = (Character)(CharID[P2] + 1);
			}
			ctrType[P_2] = TYPE_MAX;
			break;
		case TYPE_MAX:
			break;
		default:
			break;

		}

	if (!CharFlag[P2])
	{
		if (GetCtr[P_2][SELECT] == PAD_FREE)
		{
			if (controller.GetCtr(CONTROLLER_2P_INPUT_BUTTON_B, P_2) == PAD_PUSH)
			{
				ctrType[P_2] = SELECT;
			}
		}
		if (GetCtr[P_2][RIGHT] == PAD_FREE)
		{
			if (controller.GetCtr(CONTROLLER_2P_INPUT_RIGHT, P_2) == PAD_PUSH)
			{
				ctrType[P_2] = RIGHT;
			}
		}
		if (GetCtr[P_2][LEFT] == PAD_FREE)
		{
			if (controller.GetCtr(CONTROLLER_2P_INPUT_LEFT, P_2) == PAD_PUSH)
			{
				ctrType[P_2] = LEFT;
			}
		}
	}
	else
	{
		if (GetCtr[P_2][CANSELL] == PAD_FREE)
		{
			if (controller.GetCtr(CONTROLLER_2P_INPUT_BUTTON_Y,P_2) == PAD_PUSH)
			{
				ctrType[P_2] = CANSELL;
			}
		}
	}

	GetCtr[P_2][SELECT] = controller.GetCtr(CONTROLLER_2P_INPUT_BUTTON_B, P_2);
	GetCtr[P_2][RIGHT] = controller.GetCtr(CONTROLLER_2P_INPUT_RIGHT, P_2);
	GetCtr[P_2][LEFT] = controller.GetCtr(CONTROLLER_2P_INPUT_LEFT, P_2);
	GetCtr[P_2][CANSELL] = controller.GetCtr(CONTROLLER_2P_INPUT_BUTTON_Y, P_2);



	// ‰¼ˆÚ“®‚©‚çŽÀˆÚ“®
	if (0 < tmpPos1.x && tmpPos1.x < 1200)
	{
		posTBL[P1] = tmpPos1;
	}

	// ‰¼ˆÚ“®‚©‚çŽÀˆÚ“®
	if (0 < tmpPos2.x && tmpPos2.x < 1200)
	{
		posTBL[P2] = tmpPos2;
	}

	Draw();
}

bool SelectCur::GetCharFlag(void)
{
	return CharFlag[P1];
}

bool SelectCur::GetCharFlag2(void)
{
	return CharFlag[P2];
}
