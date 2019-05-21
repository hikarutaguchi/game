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

	kettei = LoadSoundMem("sound/allScene/se_kettei.mp3");
	cansell = LoadSoundMem("sound/allScene/se_cansell.mp3");
	menu = LoadSoundMem("sound/selectScene/se_menu.mp3");
	choice = LoadSoundMem("sound/allScene/se_choice.mp3");
}


SelectCur::~SelectCur()
{
	
}

int SelectCur::GetCharData(P_TYPE playerNum)
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
			DrawBox(posTBL[i].x, posTBL[i].y, posTBL[i].x + 80, posTBL[i].y + 120,GetColor(255,128,64), false);
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
	for (int i = 0; i < CONTROLLER_MAX; i++)
	{
		DrawFormatString(0, 0 + (i * 15), 0xff0000, "pos%d,x = %d",i + 1,posTBL[i].x);
		DrawFormatString(0, 100 + (i * 15), 0xff0000, "CharID[%d] = %d",i + 1, static_cast<int>(CharID[i]));
		DrawFormatString(0, 200 + (i * 15), 0xff0000, "CharFlag%d = %d",i + 1, static_cast<int>(CharFlag[i]));
	}
	lpFader.Draw();
#endif
	ScreenFlip();
}

void SelectCur::MoveCur(Game_ctr & controller)
{
	VECTOR2 tmpPos1(posTBL[CONTROLLER_P1]);		//‰¼ˆÚ“®•Ï”	
	VECTOR2 tmpPos2(posTBL[CONTROLLER_P2]);		//‰¼ˆÚ“®•Ï”	
	VECTOR2 tmpPos3(posTBL[CONTROLLER_P3]);		//‰¼ˆÚ“®•Ï”	
	VECTOR2 tmpPos4(posTBL[CONTROLLER_P4]);		//‰¼ˆÚ“®•Ï”	

	switch (ctrType[CONTROLLER_P1])
	{
	case SELECT:
		ctrType[CONTROLLER_P1] = TYPE_MAX;
		break;
	case CANSELL:
		PlaySoundMem(cansell, DX_PLAYTYPE_BACK);
		CharFlag[CONTROLLER_P1] = false;
		ctrType[CONTROLLER_P1] = TYPE_MAX;
		break;
	case LEFT:
		tmpPos1.x -= 360;

		// CharID‚ðŽæ“¾
		if (tmpPos1.x > 0)
		{
			PlaySoundMem(choice, DX_PLAYTYPE_BACK);
			CharID[CONTROLLER_P1] = (Character)(CharID[CONTROLLER_P1] - 1);
		}
		ctrType[CONTROLLER_P1] = TYPE_MAX;
		break;
	case RIGHT:
		tmpPos1.x += 360;

		// CharID‚ðŽæ“¾
		if (tmpPos1.x < 1200)
		{
			PlaySoundMem(choice, DX_PLAYTYPE_BACK);
			CharID[CONTROLLER_P1] = (Character)(CharID[CONTROLLER_P1] + 1);
		}
		ctrType[CONTROLLER_P1] = TYPE_MAX;
		break;
	case TYPE_MAX:
		break;
	default:
		break;
	}

	if (!CharFlag[CONTROLLER_P1])
	{
		if (GetCtr[CONTROLLER_P1][SELECT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_BUTTON_B, CONTROLLER_P1) == PAD_PUSH)
			{
				PlaySoundMem(kettei, DX_PLAYTYPE_BACK);
				CharFlag[CONTROLLER_P1] = true;
				ctrType[CONTROLLER_P1] = SELECT;
			}
		}
		if (GetCtr[CONTROLLER_P1][RIGHT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_RIGHT, CONTROLLER_P1) == PAD_PUSH)
			{
				ctrType[CONTROLLER_P1] = RIGHT;
			}
		}
		if (GetCtr[CONTROLLER_P1][LEFT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_LEFT, CONTROLLER_P1) == PAD_PUSH)
			{
				ctrType[CONTROLLER_P1] = LEFT;
			}
		}
	}
	else
	{
		if (GetCtr[CONTROLLER_P1][CANSELL] == PAD_FREE)
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
		ctrType[CONTROLLER_P2] = TYPE_MAX;
		break;
	case CANSELL:
		CharFlag[CONTROLLER_P2] = false;
		ctrType[CONTROLLER_P2] = TYPE_MAX;
		break;
	case LEFT:
		tmpPos2.x -= 360;

		// CharID‚ðŽæ“¾
		if (tmpPos2.x > 0)
		{
			CharID[CONTROLLER_P2] = (Character)(CharID[CONTROLLER_P2] - 1);
		}
		ctrType[CONTROLLER_P2] = TYPE_MAX;
		break;
	case RIGHT:
		tmpPos2.x += 360;

		// CharID‚ðŽæ“¾
		if (tmpPos2.x < 1200)
		{
			CharID[CONTROLLER_P2] = (Character)(CharID[CONTROLLER_P2] + 1);
		}
		ctrType[CONTROLLER_P2] = TYPE_MAX;
		break;
	case TYPE_MAX:
		break;
	default:
		break;

	}

if (!CharFlag[CONTROLLER_P2])
{
	if (GetCtr[CONTROLLER_P2][SELECT] == PAD_FREE)
	{
		if (controller.GetCtr(INPUT_BUTTON_B, CONTROLLER_P2) == PAD_PUSH)
		{
			CharFlag[CONTROLLER_P2] = true;
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
		posTBL[CONTROLLER_P1] = tmpPos1;
	}

	// ‰¼ˆÚ“®‚©‚çŽÀˆÚ“®
	if (0 < tmpPos2.x && tmpPos2.x < 1200)
	{
		posTBL[CONTROLLER_P2] = tmpPos2;
	}

	Draw();
}

bool SelectCur::GetCharFlag(P_TYPE pType)
{
	return CharFlag[pType];
}

