#include "PlayerMng.h"
#include "DxLib.h"
#include "ImageMng.h"
#include "BaseScene.h"


PlayerMng::PlayerMng()
{
	hpPos_TBL = {
	hpPos[ONE_HP] = {0,0},
	hpPos[TWO_HP] = {64,0},
	hpPos[THREE_HP] = {128,0},
	hpPos[FOUR_HP] = {192,0},
	};

	hpFlag = {
		true,
		true,
		true,
		false,
	};

	pPos[CONTROLLER_P1] = { 120,30 };
	pPos[CONTROLLER_P2] = { SCREEN_SIZE_X - 120 - (64 * 4),30 };
	pPos[CONTROLLER_P3] = { 120,SCREEN_SIZE_Y - 90 };
	pPos[CONTROLLER_P4] = { SCREEN_SIZE_X - 120 - (64 * 4),SCREEN_SIZE_Y - 90 };
}


PlayerMng::~PlayerMng()
{
}

void PlayerMng::ColTrap(CharacterStatusData * charData)
{
}

bool PlayerMng::CheckObjType(OBJ_TYPE type)
{
	return true;
}

const int PlayerMng::SetSlimePlayerDamage(int Damage)
{
	SDamage = Damage;
	return 0;
}

const int PlayerMng::GetSlimeDamageData()
{
	return SDamage;
}

const int PlayerMng::SetSkeletonPlayerDamage(int Damage)
{
	NDamage = Damage;
	return 0;
}

const int PlayerMng::GetSkeletonDamageData()
{
	return NDamage;
}

const int PlayerMng::SetCarbunclePlayerDamage(int Damage)
{
	CDamage = Damage;
	return 0;
}

const int PlayerMng::GetCarbuncleDamageData()
{
	return CDamage;
}

const void PlayerMng::HP_Draw()
{
	for (int i = 0; i < GetJoypadNum(); i++)
	{
		switch ((P_TYPE)i)
		{
		case CONTROLLER_P1:
			if (lpSelCur.GetCharData(CONTROLLER_P1) == 1)
			{
				for (int i = 0; i < FOUR_HP; i++)
				{
					// P1��Slime��HP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[0], true);

					// �̗͂�0
					if (GetSlimeDamageData() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// �_���[�W���󂯂Ă�����
				if (GetSlimeDamageData() != 0)
				{
					// �_���[�W�l�������̎�
					if (GetSlimeDamageData() % 2 == 0)
					{
						switch (GetSlimeDamageData())
						{
						case 2:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P1].x, hpPos_TBL[2].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
							break;
						case 4:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P1].x, hpPos_TBL[0].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[0], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
						case 6:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*	case 8:
									for (int i = 0; i < FOUR_HP; i++)
									{
										DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
									}
									break;*/
						}
					}
					// �_���[�W�l����̎�
					else
					{
						switch (GetSlimeDamageData())
						{
						case 1:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P1].x, hpPos_TBL[2].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[1], true);
							break;
						case 3:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[i], true);
							}
							break;
						case 5:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P1].x, hpPos_TBL[0].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[1], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*		case 7:
										DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P1].x, hpPos_TBL[0].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[1], true);
										for (int i = 0; i < FOUR_HP - 1; i++)
										{
											DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
										}
										break;*/
						}
					}
				}
			}

			if (lpSelCur.GetCharData(CONTROLLER_P1) == 2)
			{
				for (int i = 0; i < FOUR_HP; i++)
				{
					// P1��Skeleton��HP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[0], true);

					// �̗͂�0
					if (GetSkeletonDamageData() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// �_���[�W���󂯂Ă�����
				if (GetSkeletonDamageData() != 0)
				{
					// �_���[�W�l�������̎�
					if (GetSkeletonDamageData() % 2 == 0)
					{
						switch (GetSkeletonDamageData())
						{
						case 2:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P1].x, hpPos_TBL[2].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
							break;
						case 4:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P1].x, hpPos_TBL[0].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[0], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
						case 6:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*	case 8:
									for (int i = 0; i < FOUR_HP; i++)
									{
										DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
									}
									break;*/
						}
					}
					// �_���[�W�l����̎�
					else
					{
						switch (GetSkeletonDamageData())
						{
						case 1:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P1].x, hpPos_TBL[2].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[1], true);
							break;
						case 3:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[i], true);
							}
							break;
						case 5:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P1].x, hpPos_TBL[0].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[1], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*		case 7:
										DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P1].x, hpPos_TBL[0].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[1], true);
										for (int i = 0; i < FOUR_HP - 1; i++)
										{
											DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
										}
										break;*/
						}
					}
				}
			}

			if (lpSelCur.GetCharData(CONTROLLER_P1) == 3)
			{
				for (int i = 0; i < FOUR_HP; i++)
				{
					// P1��Carbuncle��HP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[0], true);

					// �̗͂�0
					if (GetCarbuncleDamageData() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// �_���[�W���󂯂Ă�����
				if (GetCarbuncleDamageData() != 0)
				{
					// �_���[�W�l�������̎�
					if (GetCarbuncleDamageData() % 2 == 0)
					{
						switch (GetCarbuncleDamageData())
						{
						case 2:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P1].x, hpPos_TBL[2].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
							break;
						case 4:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P1].x, hpPos_TBL[0].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[0], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
						case 6:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*	case 8:
									for (int i = 0; i < FOUR_HP; i++)
									{
										DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
									}
									break;*/
						}
					}
					// �_���[�W�l����̎�
					else
					{
						switch (GetCarbuncleDamageData())
						{
						case 1:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P1].x, hpPos_TBL[2].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[1], true);
							break;
						case 3:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[i], true);
							}
							break;
						case 5:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P1].x, hpPos_TBL[0].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[1], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*		case 7:
										DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P1].x, hpPos_TBL[0].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[1], true);
										for (int i = 0; i < FOUR_HP - 1; i++)
										{
											DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
										}
										break;*/
						}
					}
				}
			}
			break;

		case CONTROLLER_P2:
			if (lpSelCur.GetCharData(CONTROLLER_P2) == 1)
			{
				for (int i = 0; i < FOUR_HP; i++)
				{
					// P2��Slime��HP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[0], true);

					// �̗͂�0
					if (GetSlimeDamageData() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// �_���[�W���󂯂Ă�����
				if (GetSlimeDamageData() != 0)
				{
					// �_���[�W�l�������̎�
					if (GetSlimeDamageData() % 2 == 0)
					{
						switch (GetSlimeDamageData())
						{
						case 2:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P2].x, hpPos_TBL[2].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[2], true);
							break;
						case 4:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P2].x, hpPos_TBL[0].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[0], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
						case 6:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*	case 8:
									for (int i = 0; i < FOUR_HP; i++)
									{
										DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
									}
									break;*/
						}
					}
					// �_���[�W�l����̎�
					else
					{
						switch (GetSlimeDamageData())
						{
						case 1:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P2].x, hpPos_TBL[2].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[1], true);
							break;
						case 3:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[i], true);
							}
							break;
						case 5:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P2].x, hpPos_TBL[0].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[1], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*		case 7:
										DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P1].x, hpPos_TBL[0].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[1], true);
										for (int i = 0; i < FOUR_HP - 1; i++)
										{
											DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
										}
										break;*/
						}
					}
				}
			}

			if (lpSelCur.GetCharData(CONTROLLER_P2) == 2)
			{
				for (int i = 0; i < FOUR_HP; i++)
				{
					// P2��Skeleton��HP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[0], true);

					// �̗͂�0
					if (GetSkeletonDamageData() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// �_���[�W���󂯂Ă�����
				if (GetSkeletonDamageData() != 0)
				{
					// �_���[�W�l�������̎�
					if (GetSkeletonDamageData() % 2 == 0)
					{
						switch (GetSkeletonDamageData())
						{
						case 2:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P2].x, hpPos_TBL[2].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[2], true);
							break;
						case 4:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P2].x, hpPos_TBL[0].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[0], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
						case 6:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*	case 8:
									for (int i = 0; i < FOUR_HP; i++)
									{
										DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
									}
									break;*/
						}
					}
					// �_���[�W�l����̎�
					else
					{
						switch (GetSkeletonDamageData())
						{
						case 1:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P2].x, hpPos_TBL[2].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[1], true);
							break;
						case 3:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[i], true);
							}
							break;
						case 5:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P2].x, hpPos_TBL[0].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[1], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*		case 7:
										DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P1].x, hpPos_TBL[0].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[1], true);
										for (int i = 0; i < FOUR_HP - 1; i++)
										{
											DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
										}
										break;*/
						}
					}
				}
			}

			if (lpSelCur.GetCharData(CONTROLLER_P2) == 3)
			{
				for (int i = 0; i < FOUR_HP; i++)
				{
					// P2��Carbuncle��HP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[0], true);

					// �̗͂�0
					if (GetCarbuncleDamageData() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// �_���[�W���󂯂Ă�����
				if (GetCarbuncleDamageData() != 0)
				{
					// �_���[�W�l�������̎�
					if (GetCarbuncleDamageData() % 2 == 0)
					{
						switch (GetCarbuncleDamageData())
						{
						case 2:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P2].x, hpPos_TBL[2].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[2], true);
							break;
						case 4:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P2].x, hpPos_TBL[0].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[0], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
						case 6:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*	case 8:
									for (int i = 0; i < FOUR_HP; i++)
									{
										DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
									}
									break;*/
						}
					}
					// �_���[�W�l����̎�
					else
					{
						switch (GetCarbuncleDamageData())
						{
						case 1:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P2].x, hpPos_TBL[2].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[1], true);
							break;
						case 3:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[i], true);
							}
							break;
						case 5:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P2].x, hpPos_TBL[0].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[1], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*		case 7:
										DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P1].x, hpPos_TBL[0].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[1], true);
										for (int i = 0; i < FOUR_HP - 1; i++)
										{
											DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
										}
										break;*/
						}
					}
				}
			}
			break;

		case CONTROLLER_P3:
			if (lpSelCur.GetCharData(CONTROLLER_P3) == 1)
			{
				for (int i = 0; i < FOUR_HP; i++)
				{
					// P3��Slime��HP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[0], true);

					// �̗͂�0
					if (GetSlimeDamageData() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// �_���[�W���󂯂Ă�����
				if (GetSlimeDamageData() != 0)
				{
					// �_���[�W�l�������̎�
					if (GetSlimeDamageData() % 2 == 0)
					{
						switch (GetSlimeDamageData())
						{
						case 2:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P3].x, hpPos_TBL[2].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[2], true);
							break;
						case 4:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P3].x, hpPos_TBL[0].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[0], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
						case 6:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*	case 8:
									for (int i = 0; i < FOUR_HP; i++)
									{
										DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
									}
									break;*/
						}
					}
					// �_���[�W�l����̎�
					else
					{
						switch (GetSlimeDamageData())
						{
						case 1:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P3].x, hpPos_TBL[2].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[1], true);
							break;
						case 3:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[i], true);
							}
							break;
						case 5:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P3].x, hpPos_TBL[0].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[1], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*		case 7:
										DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P1].x, hpPos_TBL[0].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[1], true);
										for (int i = 0; i < FOUR_HP - 1; i++)
										{
											DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
										}
										break;*/
						}
					}
				}
			}

			if (lpSelCur.GetCharData(CONTROLLER_P3) == 2)
			{
				for (int i = 0; i < FOUR_HP; i++)
				{
					// P3��Skeleton��HP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[0], true);

					// �̗͂�0
					if (GetSkeletonDamageData() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// �_���[�W���󂯂Ă�����
				if (GetSkeletonDamageData() != 0)
				{
					// �_���[�W�l�������̎�
					if (GetSkeletonDamageData() % 2 == 0)
					{
						switch (GetSkeletonDamageData())
						{
						case 2:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P3].x, hpPos_TBL[2].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[2], true);
							break;
						case 4:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P3].x, hpPos_TBL[0].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[0], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
						case 6:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*	case 8:
									for (int i = 0; i < FOUR_HP; i++)
									{
										DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
									}
									break;*/
						}
					}
					// �_���[�W�l����̎�
					else
					{
						switch (GetSkeletonDamageData())
						{
						case 1:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P3].x, hpPos_TBL[2].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[1], true);
							break;
						case 3:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[i], true);
							}
							break;
						case 5:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P3].x, hpPos_TBL[0].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[1], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*		case 7:
										DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P1].x, hpPos_TBL[0].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[1], true);
										for (int i = 0; i < FOUR_HP - 1; i++)
										{
											DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
										}
										break;*/
						}
					}
				}
			}

			if (lpSelCur.GetCharData(CONTROLLER_P3) == 3)
			{
				for (int i = 0; i < FOUR_HP; i++)
				{
					// P3��Carbuncle��HP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[0], true);

					// �̗͂�0
					if (GetCarbuncleDamageData() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// �_���[�W���󂯂Ă�����
				if (GetCarbuncleDamageData() != 0)
				{
					// �_���[�W�l�������̎�
					if (GetCarbuncleDamageData() % 2 == 0)
					{
						switch (GetCarbuncleDamageData())
						{
						case 2:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P3].x, hpPos_TBL[2].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[2], true);
							break;
						case 4:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P3].x, hpPos_TBL[0].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[0], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
						case 6:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*	case 8:
									for (int i = 0; i < FOUR_HP; i++)
									{
										DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
									}
									break;*/
						}
					}
					// �_���[�W�l����̎�
					else
					{
						switch (GetCarbuncleDamageData())
						{
						case 1:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P3].x, hpPos_TBL[2].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[1], true);
							break;
						case 3:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[i], true);
							}
							break;
						case 5:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P3].x, hpPos_TBL[0].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[1], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*		case 7:
										DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P1].x, hpPos_TBL[0].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[1], true);
										for (int i = 0; i < FOUR_HP - 1; i++)
										{
											DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
										}
										break;*/
						}
					}
				}
			}
			break;
		case CONTROLLER_P4:
			if (lpSelCur.GetCharData(CONTROLLER_P4) == 1)
			{
				for (int i = 0; i < FOUR_HP; i++)
				{
					// P4��Slime��HP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[0], true);

					// �̗͂�0
					if (GetSlimeDamageData() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// �_���[�W���󂯂Ă�����
				if (GetSlimeDamageData() != 0)
				{
					// �_���[�W�l�������̎�
					if (GetSlimeDamageData() % 2 == 0)
					{
						switch (GetSlimeDamageData())
						{
						case 2:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P4].x, hpPos_TBL[2].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[2], true);
							break;
						case 4:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P4].x, hpPos_TBL[0].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[0], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
						case 6:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*	case 8:
									for (int i = 0; i < FOUR_HP; i++)
									{
										DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
									}
									break;*/
						}
					}
					// �_���[�W�l����̎�
					else
					{
						switch (GetSlimeDamageData())
						{
						case 1:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P4].x, hpPos_TBL[2].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[1], true);
							break;
						case 3:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[i], true);
							}
							break;
						case 5:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P4].x, hpPos_TBL[0].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[1], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*		case 7:
										DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P1].x, hpPos_TBL[0].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[1], true);
										for (int i = 0; i < FOUR_HP - 1; i++)
										{
											DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
										}
										break;*/
						}
					}
				}
			}

			if (lpSelCur.GetCharData(CONTROLLER_P4) == 2)
			{
				for (int i = 0; i < FOUR_HP; i++)
				{
					// P4��Skeleton��HP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[0], true);

					// �̗͂�0
					if (GetSkeletonDamageData() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// �_���[�W���󂯂Ă�����
				if (GetSkeletonDamageData() != 0)
				{
					// �_���[�W�l�������̎�
					if (GetSkeletonDamageData() % 2 == 0)
					{
						switch (GetSkeletonDamageData())
						{
						case 2:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P4].x, hpPos_TBL[2].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[2], true);
							break;
						case 4:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P4].x, hpPos_TBL[0].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[0], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
						case 6:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*	case 8:
									for (int i = 0; i < FOUR_HP; i++)
									{
										DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
									}
									break;*/
						}
					}
					// �_���[�W�l����̎�
					else
					{
						switch (GetSkeletonDamageData())
						{
						case 1:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P4].x, hpPos_TBL[2].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[1], true);
							break;
						case 3:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[i], true);
							}
							break;
						case 5:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P4].x, hpPos_TBL[0].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[1], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*		case 7:
										DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P1].x, hpPos_TBL[0].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[1], true);
										for (int i = 0; i < FOUR_HP - 1; i++)
										{
											DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
										}
										break;*/
						}
					}
				}
			}

			if (lpSelCur.GetCharData(CONTROLLER_P4) == 3)
			{
				for (int i = 0; i < FOUR_HP; i++)
				{
					// P4��Carbuncle��HP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[0], true);

					// �̗͂�0
					if (GetCarbuncleDamageData() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// �_���[�W���󂯂Ă�����
				if (GetCarbuncleDamageData() != 0)
				{
					// �_���[�W�l�������̎�
					if (GetCarbuncleDamageData() % 2 == 0)
					{
						switch (GetCarbuncleDamageData())
						{
						case 2:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P4].x, hpPos_TBL[2].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[2], true);
							break;
						case 4:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P4].x, hpPos_TBL[0].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[0], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
						case 6:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*	case 8:
									for (int i = 0; i < FOUR_HP; i++)
									{
										DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
									}
									break;*/
						}
					}
					// �_���[�W�l����̎�
					else
					{
						switch (GetCarbuncleDamageData())
						{
						case 1:
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[0], true);
							}
							DrawGraph(hpPos_TBL[2].x + pPos[CONTROLLER_P4].x, hpPos_TBL[2].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[1], true);
							break;
						case 3:
							for (int i = 0; i < FOUR_HP; i++)
							{
								DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[i], true);
							}
							break;
						case 5:
							DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P4].x, hpPos_TBL[0].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[1], true);
							for (int i = 0; i < FOUR_HP - 1; i++)
							{
								DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[2], true);
							}
							break;
							/*		case 7:
										DrawGraph(hpPos_TBL[0].x + pPos[CONTROLLER_P1].x, hpPos_TBL[0].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[1], true);
										for (int i = 0; i < FOUR_HP - 1; i++)
										{
											DrawGraph(hpPos_TBL[i + 1].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i + 1].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
										}
										break;*/
						}
					}
				}
			}
			break;
		}
	}
	return;
}