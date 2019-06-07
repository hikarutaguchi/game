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
		true,		// P1
		true,		// P2
		true,		// P3
		true		// P4
	};

	CharID = {
		static_cast<Character>(Character::NON),		// P1
		static_cast<Character>(Character::NON),		// P2
		static_cast<Character>(Character::NON),		// P3
		static_cast<Character>(Character::NON)		// P4
	};

	posTBL = {
		pos = {300,300},		// P1
		pos = {300,300},		// P2
		pos = {300,300},		// P3
		pos = {300,300}			// P4
	};

	DrawTBL = {
		pos = {300,300},		// スライム選択
		pos = {450,150},		// スケルトン選択
		pos = {600,300},		// カーバンクル選択
		pos = {450,450}		// ランダム選択
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
		CharFlag[CONTROLLER_P1] = false;
		CharID[CONTROLLER_P1] = static_cast<Character>(Character::slime);
		break;
	case 2:
		playerFlag[CONTROLLER_P1] = true;
		playerFlag[CONTROLLER_P2] = true;
		CharFlag[CONTROLLER_P1] = false;
		CharFlag[CONTROLLER_P2] = false;
		CharID[CONTROLLER_P1] = static_cast<Character>(Character::slime);
		CharID[CONTROLLER_P2] = static_cast<Character>(Character::slime);
		break;
	case 3:
		playerFlag[CONTROLLER_P1] = true;
		playerFlag[CONTROLLER_P2] = true;
		playerFlag[CONTROLLER_P3] = true;
		CharFlag[CONTROLLER_P1] = false;
		CharFlag[CONTROLLER_P2] = false;
		CharFlag[CONTROLLER_P3] = false;
		CharID[CONTROLLER_P1] = static_cast<Character>(Character::slime);
		CharID[CONTROLLER_P2] = static_cast<Character>(Character::slime);
		CharID[CONTROLLER_P3] = static_cast<Character>(Character::slime);
		break;
	case 4:
		playerFlag[CONTROLLER_P1] = true;
		playerFlag[CONTROLLER_P2] = true;
		playerFlag[CONTROLLER_P3] = true;
		playerFlag[CONTROLLER_P4] = true;
		CharFlag[CONTROLLER_P1] = false;
		CharFlag[CONTROLLER_P2] = false;
		CharFlag[CONTROLLER_P3] = false;
		CharFlag[CONTROLLER_P4] = false;
		CharID[CONTROLLER_P1] = static_cast<Character>(Character::slime);
		CharID[CONTROLLER_P2] = static_cast<Character>(Character::slime);
		CharID[CONTROLLER_P3] = static_cast<Character>(Character::slime);
		CharID[CONTROLLER_P4] = static_cast<Character>(Character::slime);
		break;
	default:
		break;
	}

	lpImageMng.GetID("image/yubis_s.png", VECTOR2(64, 64), VECTOR2(4, 1));		//
	lpImageMng.GetID("image/selectf.png", VECTOR2(300, 300), VECTOR2(1, 2));		//プレイヤーのフレームを読み込み
	lpImageMng.GetID("image/selectf_s.png", VECTOR2(300, 300), VECTOR2(2, 2));		//プレイヤーのフレームを読み込み
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

	DrawGraph(0, 0, lpImageMng.GetID("image/森.png")[0], true);

	DrawGraph(DrawTBL[0].x, DrawTBL[0].y, lpImageMng.GetID("image/selectf.png", VECTOR2(300, 300), VECTOR2(1, 2))[0], true);
	DrawGraph(DrawTBL[1].x, DrawTBL[1].y, lpImageMng.GetID("image/selectf.png", VECTOR2(300, 300), VECTOR2(1, 2))[0], true);
	DrawGraph(DrawTBL[2].x, DrawTBL[2].y, lpImageMng.GetID("image/selectf.png", VECTOR2(300, 300), VECTOR2(1, 2))[0], true);

	for (int i = 0; i < GetPlayerFlag(CONTROLLER_P1)+ GetPlayerFlag(CONTROLLER_P2)+ GetPlayerFlag(CONTROLLER_P3)+ GetPlayerFlag(CONTROLLER_P4); i++)
	{
		DrawGraph(posTBL[i].x, posTBL[i].y, lpImageMng.GetID("image/selectf_s.png", VECTOR2(300, 300), VECTOR2(2, 2))[i], true);
	}

	DrawGraph(500, 800, lpImageMng.GetID("image/button_UI.png")[2], true);
	DrawGraph(850, 800, lpImageMng.GetID("image/button_UI.png")[4], true);

	DrawGraph(0, 0, lpImageMng.GetID("image/erandene.png")[0], true);

	DrawGraph(DrawTBL[0].x + 120, DrawTBL[0].y + 80, lpImageMng.GetID("image/slimes.png", VECTOR2(64, 100), VECTOR2(4, 4))[1], true);
	DrawGraph(DrawTBL[1].x + 120, DrawTBL[1].y + 80, lpImageMng.GetID("image/skeleton.png", VECTOR2(64, 100), VECTOR2(4, 4))[1], true);
	DrawGraph(DrawTBL[2].x + 120, DrawTBL[2].y + 80, lpImageMng.GetID("image/Carbuncle.png", VECTOR2(64, 100), VECTOR2(4, 4))[1], true);

#ifdef _DEBUG
	for (int i = 0; i < CONTROLLER_MAX; i++)
	{
		DrawFormatString(0, 0 + (i * 15), 0xff0000, "pos%d,x = %d", i + 1, posTBL[i].x);
		DrawFormatString(0, 100 + (i * 15), 0xff0000, "CharID[%d] = %d", i + 1, static_cast<int>(CharID[i]));
		DrawFormatString(0, 200 + (i * 15), 0xff0000, "CharFlag%d = %d", i + 1, static_cast<int>(CharFlag[i]));
	}
	lpFader.Draw();
#endif
	ScreenFlip();
}

void SelectCur::MoveCur(Game_ctr & controller)
{
	VECTOR2 tmpPos1(posTBL[CONTROLLER_P1]);		//仮移動変数	
	VECTOR2 tmpPos2(posTBL[CONTROLLER_P2]);		//仮移動変数	
	VECTOR2 tmpPos3(posTBL[CONTROLLER_P3]);		//仮移動変数	
	VECTOR2 tmpPos4(posTBL[CONTROLLER_P4]);		//仮移動変数	

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
				tmpPos1.x += 150;

				if (tmpPos1.x == 450)
				{
					tmpPos1 = DrawTBL[1];
				}
				else
				{
					tmpPos1 = DrawTBL[2];
				}

				// CharIDを取得
				if (tmpPos1.x <= 600)
				{
					PlaySoundMem(choice, DX_PLAYTYPE_BACK);
					if (CharID[CONTROLLER_P1] != 3)
					{
						CharID[CONTROLLER_P1] = (Character)(CharID[CONTROLLER_P1] + 1);
					}
					else
					{
						CharID[CONTROLLER_P1] = (Character)CharID[CONTROLLER_P1];
					}
				}
			}
		}
		if (GetCtr[CONTROLLER_P1][LEFT] == PAD_FREE)
		{
			if (controller.GetCtr(INPUT_LEFT, CONTROLLER_P1) == PAD_PUSH)
			{
				tmpPos1.x -= 150;

				if (tmpPos1.x == 450)
				{
					tmpPos1 = DrawTBL[1];
				}
				else
				{
					tmpPos1 = DrawTBL[0];
				}

				// CharIDを取得
				if (tmpPos1.x >= 300)
				{
					PlaySoundMem(choice, DX_PLAYTYPE_BACK);
					if (CharID[CONTROLLER_P1] != 1)
					{
						CharID[CONTROLLER_P1] = (Character)(CharID[CONTROLLER_P1] - 1);
					}
					else
					{
						CharID[CONTROLLER_P1] = (Character)CharID[CONTROLLER_P1];
					}
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
					tmpPos2.x += 150;

					if (tmpPos2.x == 450)
					{
						tmpPos2 = DrawTBL[1];
					}
					else
					{
						tmpPos2 = DrawTBL[2];
					}

					// CharIDを取得
					if (tmpPos2.x <= 600)
					{
						PlaySoundMem(choice, DX_PLAYTYPE_BACK);
						if (CharID[CONTROLLER_P2] != 3)
						{
							CharID[CONTROLLER_P2] = (Character)(CharID[CONTROLLER_P2] + 1);
						}
						else
						{
							CharID[CONTROLLER_P2] = (Character)CharID[CONTROLLER_P2];
						}
					}
				}
			}
			if (GetCtr[CONTROLLER_P2][LEFT] == PAD_FREE)
			{
				if (controller.GetCtr(INPUT_LEFT, CONTROLLER_P2) == PAD_PUSH)
				{
					tmpPos2.x -= 150;

					if (tmpPos2.x == 450)
					{
						tmpPos2 = DrawTBL[1];
					}
					else
					{
						tmpPos2 = DrawTBL[0];
					}

					// CharIDを取得
					if (tmpPos2.x >= 300)
					{
						PlaySoundMem(choice, DX_PLAYTYPE_BACK);
						if (CharID[CONTROLLER_P2] != 1)
						{
							CharID[CONTROLLER_P2] = (Character)(CharID[CONTROLLER_P2] - 1);
						}
						else
						{
							CharID[CONTROLLER_P2] = (Character)CharID[CONTROLLER_P2];
						}
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
					tmpPos3.x += 150;

					if (tmpPos3.x == 450)
					{
						tmpPos3 = DrawTBL[1];
					}
					else
					{
						tmpPos3 = DrawTBL[2];
					}

					// CharIDを取得
					if (tmpPos3.x <= 600)
					{
						PlaySoundMem(choice, DX_PLAYTYPE_BACK);
						if (CharID[CONTROLLER_P3] != 3)
						{
							CharID[CONTROLLER_P3] = (Character)(CharID[CONTROLLER_P3] + 1);
						}
						else
						{
							CharID[CONTROLLER_P3] = (Character)CharID[CONTROLLER_P3];
						}
					}
				}
			}
			if (GetCtr[CONTROLLER_P3][LEFT] == PAD_FREE)
			{
				if (controller.GetCtr(INPUT_LEFT, CONTROLLER_P3) == PAD_PUSH)
				{
					tmpPos3.x -= 150;

					if (tmpPos3.x == 450)
					{
						tmpPos3 = DrawTBL[1];
					}
					else
					{
						tmpPos3 = DrawTBL[0];
					}

					// CharIDを取得
					if (tmpPos3.x >= 300)
					{
						PlaySoundMem(choice, DX_PLAYTYPE_BACK);
						if (CharID[CONTROLLER_P3] != 1)
						{
							CharID[CONTROLLER_P3] = (Character)(CharID[CONTROLLER_P3] - 1);
						}
						else
						{
							CharID[CONTROLLER_P3] = (Character)CharID[CONTROLLER_P3];
						}
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
					tmpPos4.x += 150;

					if (tmpPos4.x == 450)
					{
						tmpPos4 = DrawTBL[1];
					}
					else
					{
						tmpPos4 = DrawTBL[2];
					}

					// CharIDを取得
					if (tmpPos4.x <= 600)
					{
						PlaySoundMem(choice, DX_PLAYTYPE_BACK);
						if (CharID[CONTROLLER_P4] != 3)
						{
							CharID[CONTROLLER_P4] = (Character)(CharID[CONTROLLER_P4] + 1);
						}
						else
						{
							CharID[CONTROLLER_P4] = (Character)CharID[CONTROLLER_P4];
						}
					}
				}
			}
			if (GetCtr[CONTROLLER_P4][LEFT] == PAD_FREE)
			{
				if (controller.GetCtr(INPUT_LEFT, CONTROLLER_P4) == PAD_PUSH)
				{
					tmpPos4.x -= 150;

					if (tmpPos4.x == 450)
					{
						tmpPos4 = DrawTBL[1];
					}
					else
					{
						tmpPos4 = DrawTBL[0];
					}

					// CharIDを取得
					if (tmpPos4.x >= 300)
					{
						PlaySoundMem(choice, DX_PLAYTYPE_BACK);
						if (CharID[CONTROLLER_P4] != 1)
						{
							CharID[CONTROLLER_P4] = (Character)(CharID[CONTROLLER_P4] - 1);
						}
						else
						{
							CharID[CONTROLLER_P4] = (Character)CharID[CONTROLLER_P4];
						}
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
		GetCtr[CONTROLLER_P1][DOWN] = controller.GetCtr(INPUT_DOWN, CONTROLLER_P1);
		GetCtr[CONTROLLER_P1][CANSELL] = controller.GetCtr(INPUT_BUTTON_Y, CONTROLLER_P1);

		GetCtr[CONTROLLER_P2][SELECT] = controller.GetCtr(INPUT_BUTTON_B, CONTROLLER_P2);
		GetCtr[CONTROLLER_P2][RIGHT] = controller.GetCtr(INPUT_RIGHT, CONTROLLER_P2);
		GetCtr[CONTROLLER_P2][LEFT] = controller.GetCtr(INPUT_LEFT, CONTROLLER_P2);
		GetCtr[CONTROLLER_P1][DOWN] = controller.GetCtr(INPUT_DOWN, CONTROLLER_P1);
		GetCtr[CONTROLLER_P2][CANSELL] = controller.GetCtr(INPUT_BUTTON_Y, CONTROLLER_P2);

		GetCtr[CONTROLLER_P3][SELECT] = controller.GetCtr(INPUT_BUTTON_B, CONTROLLER_P3);
		GetCtr[CONTROLLER_P3][RIGHT] = controller.GetCtr(INPUT_RIGHT, CONTROLLER_P3);
		GetCtr[CONTROLLER_P3][LEFT] = controller.GetCtr(INPUT_LEFT, CONTROLLER_P3);
		GetCtr[CONTROLLER_P3][CANSELL] = controller.GetCtr(INPUT_BUTTON_Y, CONTROLLER_P3);

		GetCtr[CONTROLLER_P4][SELECT] = controller.GetCtr(INPUT_BUTTON_B, CONTROLLER_P4);
		GetCtr[CONTROLLER_P4][RIGHT] = controller.GetCtr(INPUT_RIGHT, CONTROLLER_P4);
		GetCtr[CONTROLLER_P4][LEFT] = controller.GetCtr(INPUT_LEFT, CONTROLLER_P4);
		GetCtr[CONTROLLER_P4][CANSELL] = controller.GetCtr(INPUT_BUTTON_Y, CONTROLLER_P4);


		// 仮移動から実移動
		if (300 <= tmpPos1.x && tmpPos1.x <= 600)
		{
			posTBL[CONTROLLER_P1] = tmpPos1;
		}

		// 仮移動から実移動
		if (0 < tmpPos2.x && tmpPos2.x < 1200)
		{
			posTBL[CONTROLLER_P2] = tmpPos2;
		}

		// 仮移動から実移動
		if (0 < tmpPos3.x && tmpPos3.x < 1200)
		{
			posTBL[CONTROLLER_P3] = tmpPos3;
		}

		// 仮移動から実移動
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

