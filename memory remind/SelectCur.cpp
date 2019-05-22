#include "DxLib.h"
#include "SelectCur.h"
#include "ImageMng.h"
#include "Fader.h"



SelectCur::SelectCur()
{
	playerFlag = {
		false,		// P1
		false,		// P2
		false,		// P3
		false		// P4
	};

	CharFlag = {
		false,		// P1
		false,		// P2
		false,		// P3
		false		// P4
	};

	CharID = {
		static_cast<Character>(Character::NON),		// P1
		static_cast<Character>(Character::NON),		// P2
		static_cast<Character>(Character::NON),		// P3
		static_cast<Character>(Character::NON)		// P4
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

	switch (GetJoypadNum())
	{
	case 1:
		playerFlag[CONTROLLER_P1] = true;

		CharID[CONTROLLER_P1] = static_cast<Character>(Character::slime);
		break;
	case 2:
		playerFlag[CONTROLLER_P1] = true;
		playerFlag[CONTROLLER_P2] = true;

		CharID[CONTROLLER_P1] = static_cast<Character>(Character::slime);
		CharID[CONTROLLER_P2] = static_cast<Character>(Character::slime);
		break;
	case 3:
		playerFlag[CONTROLLER_P1] = true;
		playerFlag[CONTROLLER_P2] = true;
		playerFlag[CONTROLLER_P3] = true;

		CharID[CONTROLLER_P1] = static_cast<Character>(Character::slime);
		CharID[CONTROLLER_P2] = static_cast<Character>(Character::slime);
		CharID[CONTROLLER_P3] = static_cast<Character>(Character::slime);
		break;
	case 4:
		playerFlag[CONTROLLER_P1] = true;
		playerFlag[CONTROLLER_P2] = true;
		playerFlag[CONTROLLER_P3] = true;
		playerFlag[CONTROLLER_P4] = true;

		CharID[CONTROLLER_P1] = static_cast<Character>(Character::slime);
		CharID[CONTROLLER_P2] = static_cast<Character>(Character::slime);
		CharID[CONTROLLER_P3] = static_cast<Character>(Character::slime);
		CharID[CONTROLLER_P4] = static_cast<Character>(Character::slime);
		break;
	default:
		break;
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
		if (playerFlag[(P_TYPE)i])
		{
			if (!CharFlag[i])
			{
				DrawBox(posTBL[i].x, posTBL[i].y, posTBL[i].x + 80, posTBL[i].y + 120, GetColor(255, 128, 64), false);
				DrawFormatString(posTBL[i].x + 5, posTBL[i].y - 20, 0xffffff, "PLAYER_%d", i + 1);
			}
			else
			{
				DrawBox(posTBL[i].x + 10, posTBL[i].y + 10, posTBL[i].x + 70, posTBL[i].y + 110, 0xffffff, true);
			}
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
	VECTOR2 tmpPos1(posTBL[CONTROLLER_P1]);		//âºà⁄ìÆïœêî	
	VECTOR2 tmpPos2(posTBL[CONTROLLER_P2]);		//âºà⁄ìÆïœêî	
	VECTOR2 tmpPos3(posTBL[CONTROLLER_P3]);		//âºà⁄ìÆïœêî	
	VECTOR2 tmpPos4(posTBL[CONTROLLER_P4]);		//âºà⁄ìÆïœêî	

	if (!CharFlag[CONTROLLER_P1])
	{
		if (GetCtr[CONTROLLER_P1][SELECT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_BUTTON_B, CONTROLLER_P1) == PAD_PUSH)
			{
				PlaySoundMem(kettei, DX_PLAYTYPE_BACK);
				CharFlag[CONTROLLER_P1] = true;
			}
		}
		if (GetCtr[CONTROLLER_P1][RIGHT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_RIGHT, CONTROLLER_P1) == PAD_PUSH)
			{
				tmpPos1.x += 360;

				// CharIDÇéÊìæ
				if (tmpPos1.x < 1200)
				{
					PlaySoundMem(choice, DX_PLAYTYPE_BACK);
					CharID[CONTROLLER_P1] = (Character)(CharID[CONTROLLER_P1] + 1);
				}
			}
		}
		if (GetCtr[CONTROLLER_P1][LEFT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_LEFT, CONTROLLER_P1) == PAD_PUSH)
			{
				tmpPos1.x -= 360;

				// CharIDÇéÊìæ
				if (tmpPos1.x > 0)
				{
					PlaySoundMem(choice, DX_PLAYTYPE_BACK);
					CharID[CONTROLLER_P1] = (Character)(CharID[CONTROLLER_P1] - 1);
				}
			}
		}
	}
	else
	{
		if (GetCtr[CONTROLLER_P1][CANSELL] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_BUTTON_Y, CONTROLLER_P1) == PAD_PUSH)
			{
				PlaySoundMem(cansell, DX_PLAYTYPE_BACK);
				CharFlag[CONTROLLER_P1] = false;
			}
		}
	}

	if (!CharFlag[CONTROLLER_P2])
	{
		if (GetCtr[CONTROLLER_P2][SELECT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_BUTTON_B, CONTROLLER_P2) == PAD_PUSH)
			{
				PlaySoundMem(kettei, DX_PLAYTYPE_BACK);
				CharFlag[CONTROLLER_P2] = true;
			}
		}
		if (GetCtr[CONTROLLER_P2][RIGHT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_RIGHT, CONTROLLER_P2) == PAD_PUSH)
			{
				tmpPos2.x += 360;

				// CharIDÇéÊìæ
				if (tmpPos2.x < 1200)
				{
					PlaySoundMem(choice, DX_PLAYTYPE_BACK);
					CharID[CONTROLLER_P2] = (Character)(CharID[CONTROLLER_P2] + 1);
				}
			}
		}
		if (GetCtr[CONTROLLER_P2][LEFT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_LEFT, CONTROLLER_P2) == PAD_PUSH)
			{
				tmpPos2.x -= 360;

				// CharIDÇéÊìæ
				if (tmpPos2.x > 0)
				{
					PlaySoundMem(choice, DX_PLAYTYPE_BACK);
					CharID[CONTROLLER_P2] = (Character)(CharID[CONTROLLER_P2] - 1);
				}
			}
		}
	}
	else
	{
		if (GetCtr[CONTROLLER_P2][CANSELL] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_BUTTON_Y, CONTROLLER_P2) == PAD_PUSH)
			{
				PlaySoundMem(cansell, DX_PLAYTYPE_BACK);
				CharFlag[CONTROLLER_P2] = false;
			}
		}
	}

	if (!CharFlag[CONTROLLER_P3])
	{
		if (GetCtr[CONTROLLER_P3][SELECT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_BUTTON_B, CONTROLLER_P3) == PAD_PUSH)
			{
				PlaySoundMem(kettei, DX_PLAYTYPE_BACK);
				CharFlag[CONTROLLER_P3] = true;
			}
		}
		if (GetCtr[CONTROLLER_P3][RIGHT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_RIGHT, CONTROLLER_P3) == PAD_PUSH)
			{
				tmpPos3.x += 360;

				// CharIDÇéÊìæ
				if (tmpPos3.x < 1200)
				{
					PlaySoundMem(choice, DX_PLAYTYPE_BACK);
					CharID[CONTROLLER_P3] = (Character)(CharID[CONTROLLER_P3] + 1);
				}
			}
		}
		if (GetCtr[CONTROLLER_P3][LEFT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_LEFT, CONTROLLER_P3) == PAD_PUSH)
			{
				tmpPos3.x -= 360;

				// CharIDÇéÊìæ
				if (tmpPos3.x > 0)
				{
					PlaySoundMem(choice, DX_PLAYTYPE_BACK);
					CharID[CONTROLLER_P3] = (Character)(CharID[CONTROLLER_P3] - 1);
				}
			}
		}
	}
	else
	{
		if (GetCtr[CONTROLLER_P3][CANSELL] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_BUTTON_Y, CONTROLLER_P3) == PAD_PUSH)
			{
				PlaySoundMem(cansell, DX_PLAYTYPE_BACK);
				CharFlag[CONTROLLER_P3] = false;
			}
		}
	}

	if (!CharFlag[CONTROLLER_P4])
	{
		if (GetCtr[CONTROLLER_P4][SELECT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_BUTTON_B, CONTROLLER_P4) == PAD_PUSH)
			{
				PlaySoundMem(kettei, DX_PLAYTYPE_BACK);
				CharFlag[CONTROLLER_P4] = true;
			}
		}
		if (GetCtr[CONTROLLER_P4][RIGHT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_RIGHT, CONTROLLER_P4) == PAD_PUSH)
			{
				tmpPos4.x += 360;

				// CharIDÇéÊìæ
				if (tmpPos4.x < 1200)
				{
					PlaySoundMem(choice, DX_PLAYTYPE_BACK);
					CharID[CONTROLLER_P4] = (Character)(CharID[CONTROLLER_P4] + 1);
				}
			}
		}
		if (GetCtr[CONTROLLER_P4][LEFT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_LEFT, CONTROLLER_P4) == PAD_PUSH)
			{
				tmpPos4.x -= 360;

				// CharIDÇéÊìæ
				if (tmpPos4.x > 0)
				{
					PlaySoundMem(choice, DX_PLAYTYPE_BACK);
					CharID[CONTROLLER_P4] = (Character)(CharID[CONTROLLER_P4] - 1);
				}
			}
		}
	}
	else
	{
		if (GetCtr[CONTROLLER_P4][CANSELL] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_BUTTON_Y, CONTROLLER_P4) == PAD_PUSH)
			{
				PlaySoundMem(cansell, DX_PLAYTYPE_BACK);
				CharFlag[CONTROLLER_P4] = false;
			}
		}
	}

	GetCtr[CONTROLLER_P1][SELECT] = controller.GetCtr(INPUT_BUTTON_B, CONTROLLER_P1);
	GetCtr[CONTROLLER_P1][RIGHT] = controller.GetCtr(INPUT_RIGHT, CONTROLLER_P1);
	GetCtr[CONTROLLER_P1][LEFT] = controller.GetCtr(INPUT_LEFT, CONTROLLER_P1);
	GetCtr[CONTROLLER_P1][CANSELL] = controller.GetCtr(INPUT_BUTTON_Y, CONTROLLER_P1);

	GetCtr[CONTROLLER_P2][SELECT] = controller.GetCtr(INPUT_BUTTON_B, CONTROLLER_P2);
	GetCtr[CONTROLLER_P2][RIGHT] = controller.GetCtr(INPUT_RIGHT, CONTROLLER_P2);
	GetCtr[CONTROLLER_P2][LEFT] = controller.GetCtr(INPUT_LEFT, CONTROLLER_P2);
	GetCtr[CONTROLLER_P2][CANSELL] = controller.GetCtr(INPUT_BUTTON_Y, CONTROLLER_P2);

	GetCtr[CONTROLLER_P3][SELECT] = controller.GetCtr(INPUT_BUTTON_B, CONTROLLER_P3);
	GetCtr[CONTROLLER_P3][RIGHT] = controller.GetCtr(INPUT_RIGHT, CONTROLLER_P3);
	GetCtr[CONTROLLER_P3][LEFT] = controller.GetCtr(INPUT_LEFT, CONTROLLER_P3);
	GetCtr[CONTROLLER_P3][CANSELL] = controller.GetCtr(INPUT_BUTTON_Y, CONTROLLER_P3);

	GetCtr[CONTROLLER_P4][SELECT] = controller.GetCtr(INPUT_BUTTON_B, CONTROLLER_P4);
	GetCtr[CONTROLLER_P4][RIGHT] = controller.GetCtr(INPUT_RIGHT, CONTROLLER_P4);
	GetCtr[CONTROLLER_P4][LEFT] = controller.GetCtr(INPUT_LEFT, CONTROLLER_P4);
	GetCtr[CONTROLLER_P4][CANSELL] = controller.GetCtr(INPUT_BUTTON_Y, CONTROLLER_P4);


	// âºà⁄ìÆÇ©ÇÁé¿à⁄ìÆ
	if (0 < tmpPos1.x && tmpPos1.x < 1200)
	{
		posTBL[CONTROLLER_P1] = tmpPos1;
	}

	// âºà⁄ìÆÇ©ÇÁé¿à⁄ìÆ
	if (0 < tmpPos2.x && tmpPos2.x < 1200)
	{
		posTBL[CONTROLLER_P2] = tmpPos2;
	}

	// âºà⁄ìÆÇ©ÇÁé¿à⁄ìÆ
	if (0 < tmpPos3.x && tmpPos3.x < 1200)
	{
		posTBL[CONTROLLER_P3] = tmpPos3;
	}

	// âºà⁄ìÆÇ©ÇÁé¿à⁄ìÆ
	if (0 < tmpPos4.x && tmpPos4.x < 1200)
	{
		posTBL[CONTROLLER_P4] = tmpPos4;
	}

	Draw();
}

bool SelectCur::GetCharFlag(P_TYPE pType)
{
	return CharFlag[pType];
}

bool SelectCur::GetPlayerFlag(P_TYPE pType)
{
	return playerFlag[pType];
}

