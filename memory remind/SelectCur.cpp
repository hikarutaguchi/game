#include "DxLib.h"
#include "SelectCur.h"
#include "ImageMng.h"
#include "Fader.h"



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
		pos = {170,360},		// P2
		pos = {170,360},		// P3
		pos = {170,360}			// P4
	};

	for (int p = 0; p < TYPE_MAX; p++)
	{
		for (int i = 0; i < CONTROLLER_MAX; i++)
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

	for (int i = 0; i < CONTROLLER_MAX; i++)
	{
		if (!CharFlag[i])
		{
			DrawBox(posTBL[P1].x, posTBL[P1].y, posTBL[P1].x + 80, posTBL[P1].y + 120, 0xff0000, false);
			DrawBox(posTBL[P2].x, posTBL[P2].y, posTBL[P2].x + 80, posTBL[P2].y + 120, 0x0000ff, false);
			DrawBox(posTBL[P3].x, posTBL[P3].y, posTBL[P3].x + 80, posTBL[P3].y + 120, 0x00ff00, false);
			DrawBox(posTBL[P4].x, posTBL[P4].y, posTBL[P4].x + 80, posTBL[P4].y + 120, 0xffff00, false);

			DrawFormatString(posTBL[i].x + 5, posTBL[i].y - 20, 0xffffff, "PLAYER_%d",i);
		}
		else
		{
			DrawBox(posTBL[i].x + 10, posTBL[i].y + 10, posTBL[i].x + 70, posTBL[i].y + 110, 0xffffff, true);
		}
	}

	DrawGraph(500, 800, lpImageMng.GetID("image/button_UI.png")[2], true);
	DrawGraph(850, 800, lpImageMng.GetID("image/button_UI.png")[4], true);

	DrawGraph(0, 0, lpImageMng.GetID("image/erandene.png")[0], true);

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
	lpFader.Draw();
#endif
	ScreenFlip();
}

void SelectCur::MoveCur(Game_ctr & controller)
{
	VECTOR2 tmpPos1(posTBL[P1]);		//‰¼ˆÚ“®•Ï”	
	VECTOR2 tmpPos2(posTBL[P2]);

	switch (ctrType[CONTROLLER_P1])
	{
	case SELECT:
		CharFlag[P1] = true;
		ctrType[CONTROLLER_P1] = TYPE_MAX;
		break;
	case CANSELL:
		CharFlag[P1] = false;
		ctrType[CONTROLLER_P1] = TYPE_MAX;
		break;
	case LEFT:
		tmpPos1.x -= 360;

		// CharID‚ðŽæ“¾
		if (tmpPos1.x > 0)
		{
			CharID[P1] = (Character)(CharID[P1] - 1);
		}
		ctrType[CONTROLLER_P1] = TYPE_MAX;
		break;
	case RIGHT:
		tmpPos1.x += 360;

		// CharID‚ðŽæ“¾
		if (tmpPos1.x < 1200)
		{
			CharID[P1] = (Character)(CharID[P1] + 1);
		}
		ctrType[CONTROLLER_P1] = TYPE_MAX;
		break;
	case TYPE_MAX:
		break;
	default:
		break;

	}

	if (!CharFlag[P1])
	{
		if (GetCtr[CONTROLLER_P1][SELECT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_BUTTON_B, CONTROLLER_P1) == PAD_PUSH)
			{
				ctrType[CONTROLLER_P1] = SELECT;
			}
		}
		if (GetCtr[P1][RIGHT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_RIGHT, CONTROLLER_P1) == PAD_PUSH)
			{
				ctrType[CONTROLLER_P1] = RIGHT;
			}
		}
		if (GetCtr[P1][LEFT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_LEFT, CONTROLLER_P1) == PAD_PUSH)
			{
				ctrType[CONTROLLER_P1] = LEFT;
			}
		}
	}
	else
	{
		if (GetCtr[P1][CANSELL] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_BUTTON_Y, CONTROLLER_P1) == PAD_PUSH)
			{
				ctrType[CONTROLLER_P1] = CANSELL;
			}
		}
	}

	GetCtr[CONTROLLER_P1][SELECT] = controller.GetCtr(INPUT_BUTTON_B, CONTROLLER_P1);
	GetCtr[CONTROLLER_P1][RIGHT] = controller.GetCtr(INPUT_RIGHT, CONTROLLER_P1);
	GetCtr[CONTROLLER_P1][LEFT] = controller.GetCtr(INPUT_LEFT, CONTROLLER_P1);
	GetCtr[CONTROLLER_P1][CANSELL] = controller.GetCtr(INPUT_BUTTON_Y, CONTROLLER_P1);

		switch (ctrType[CONTROLLER_P2])
		{
		case SELECT:
			CharFlag[P2] = true;
			ctrType[CONTROLLER_P2] = TYPE_MAX;
			break;
		case CANSELL:
			CharFlag[P2] = false;
			ctrType[CONTROLLER_P2] = TYPE_MAX;
			break;
		case LEFT:
			tmpPos2.x -= 360;

			// CharID‚ðŽæ“¾
			if (tmpPos2.x > 0)
			{
				CharID[P2] = (Character)(CharID[P2] - 1);
			}
			ctrType[CONTROLLER_P2] = TYPE_MAX;
			break;
		case RIGHT:
			tmpPos2.x += 360;

			// CharID‚ðŽæ“¾
			if (tmpPos2.x < 1200)
			{
				CharID[P2] = (Character)(CharID[P2] + 1);
			}
			ctrType[CONTROLLER_P2] = TYPE_MAX;
			break;
		case TYPE_MAX:
			break;
		default:
			break;

		}

	if (!CharFlag[P2])
	{
		if (GetCtr[CONTROLLER_P2][SELECT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_BUTTON_B, CONTROLLER_P2) == PAD_PUSH)
			{
				ctrType[CONTROLLER_P2] = SELECT;
			}
		}
		if (GetCtr[CONTROLLER_P2][RIGHT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_RIGHT, CONTROLLER_P2) == PAD_PUSH)
			{
				ctrType[CONTROLLER_P2] = RIGHT;
			}
		}
		if (GetCtr[CONTROLLER_P2][LEFT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_LEFT, CONTROLLER_P2) == PAD_PUSH)
			{
				ctrType[CONTROLLER_P2] = LEFT;
			}
		}
	}
	else
	{
		if (GetCtr[CONTROLLER_P2][CANSELL] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_BUTTON_Y, CONTROLLER_P2) == PAD_PUSH)
			{
				ctrType[CONTROLLER_P2] = CANSELL;
			}
		}
	}

	GetCtr[CONTROLLER_P2][SELECT] = controller.GetCtr(INPUT_BUTTON_B, CONTROLLER_P2);
	GetCtr[CONTROLLER_P2][RIGHT] = controller.GetCtr(INPUT_RIGHT, CONTROLLER_P2);
	GetCtr[CONTROLLER_P2][LEFT] = controller.GetCtr(INPUT_LEFT, CONTROLLER_P2);
	GetCtr[CONTROLLER_P2][CANSELL] = controller.GetCtr(INPUT_BUTTON_Y, CONTROLLER_P2);



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

