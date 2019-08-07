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

	HpFlag = false;
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
	return SDamage;
}

const int PlayerMng::GetSlimeDamageData()
{
	int damage = SDamage;
	if (GetRestartHpFlag())
	{
		SDamage = 0;
	}
	if (damage != 0)
	{
		SDamage = damage;
	}
	return SDamage;
}

const int PlayerMng::SetSkeletonPlayerDamage(int Damage)
{
	NDamage = Damage;
	return NDamage;
}

const int PlayerMng::GetSkeletonDamageData()
{

	int damage = NDamage;
	if (GetRestartHpFlag())
	{
		NDamage = 0;
	}
	if (damage != 0)
	{
		NDamage = damage;
	}
	return NDamage;
}

const int PlayerMng::SetCarbunclePlayerDamage(int Damage)
{
	CDamage = Damage;
	return CDamage;
}

const int PlayerMng::GetCarbuncleDamageData()
{
	int damage = CDamage;
	if (GetRestartHpFlag())
	{
		CDamage = 0;
	}
	if (damage != 0)
	{
		CDamage = damage;
	}
	return CDamage;
}

const int PlayerMng::SetSlimePlayerDamage2(int Damage)
{
	SDamage2 = Damage;
	return 0;
}

const int PlayerMng::GetSlimeDamageData2()
{
	int damage = SDamage2;
	if (GetRestartHpFlag())
	{
		SDamage2 = 0;
	}
	if (damage != 0)
	{
		SDamage2 = damage;
	}
	return SDamage2;
}

const int PlayerMng::SetSkeletonPlayerDamage2(int Damage)
{
	NDamage2 = Damage;
	return 0;
}

const int PlayerMng::GetSkeletonDamageData2()
{
	int damage = NDamage2;
	if (GetRestartHpFlag())
	{
		NDamage2 = 0;
	}
	if (damage != 0)
	{
		NDamage2 = damage;
	}
	return NDamage2;
}

const int PlayerMng::SetCarbunclePlayerDamage2(int Damage)
{
	CDamage2 = Damage;
	return 0;
}

const int PlayerMng::GetCarbuncleDamageData2()
{
	int damage = CDamage2;
	if (GetRestartHpFlag())
	{
		CDamage2 = 0;
	}
	if (damage != 0)
	{
		CDamage2 = damage;
	}
	return CDamage2;
}

const bool PlayerMng::SetRestartHpFlag(bool rhpflag)
{
	HpFlag = rhpflag;
	return HpFlag;
}

const bool PlayerMng::GetRestartHpFlag()
{
	return HpFlag;
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
					// P1のSlimeのHP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[0], true);

					// 体力が0
					if (GetSlimeDamageData() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// ダメージを受けていた時
				if (GetSlimeDamageData() != 0)
				{
					// ダメージ値が偶数の時
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
					// ダメージ値が奇数の時
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
					// P1のSkeletonのHP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[0], true);

					// 体力が0
					if (GetSkeletonDamageData() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// ダメージを受けていた時
				if (GetSkeletonDamageData() != 0)
				{
					// ダメージ値が偶数の時
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
					// ダメージ値が奇数の時
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
					// P1のCarbuncleのHP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[0], true);

					// 体力が0
					if (GetCarbuncleDamageData() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P1].x, hpPos_TBL[i].y + pPos[CONTROLLER_P1].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// ダメージを受けていた時
				if (GetCarbuncleDamageData() != 0)
				{
					// ダメージ値が偶数の時
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
					// ダメージ値が奇数の時
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
					// P2のSlimeのHP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[0], true);

					// 体力が0
					if (GetSlimeDamageData2() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// ダメージを受けていた時
				if (GetSlimeDamageData2() != 0)
				{
					// ダメージ値が偶数の時
					if (GetSlimeDamageData2() % 2 == 0)
					{
						switch (GetSlimeDamageData2())
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
					// ダメージ値が奇数の時
					else
					{
						switch (GetSlimeDamageData2())
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
					// P2のSkeletonのHP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[0], true);

					// 体力が0
					if (GetSkeletonDamageData2() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// ダメージを受けていた時
				if (GetSkeletonDamageData2() != 0)
				{
					// ダメージ値が偶数の時
					if (GetSkeletonDamageData2() % 2 == 0)
					{
						switch (GetSkeletonDamageData2())
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
					// ダメージ値が奇数の時
					else
					{
						switch (GetSkeletonDamageData2())
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
					// P2のCarbuncleのHP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[0], true);

					// 体力が0
					if (GetCarbuncleDamageData2() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P2].x, hpPos_TBL[i].y + pPos[CONTROLLER_P2].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// ダメージを受けていた時
				if (GetCarbuncleDamageData2() != 0)
				{
					// ダメージ値が偶数の時
					if (GetCarbuncleDamageData2() % 2 == 0)
					{
						switch (GetCarbuncleDamageData2())
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
					// ダメージ値が奇数の時
					else
					{
						switch (GetCarbuncleDamageData2())
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
					// P3のSlimeのHP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[0], true);

					// 体力が0
					if (GetSlimeDamageData() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// ダメージを受けていた時
				if (GetSlimeDamageData() != 0)
				{
					// ダメージ値が偶数の時
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
					// ダメージ値が奇数の時
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
					// P3のSkeletonのHP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[0], true);

					// 体力が0
					if (GetSkeletonDamageData() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// ダメージを受けていた時
				if (GetSkeletonDamageData() != 0)
				{
					// ダメージ値が偶数の時
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
					// ダメージ値が奇数の時
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
					// P3のCarbuncleのHP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[0], true);

					// 体力が0
					if (GetCarbuncleDamageData() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P3].x, hpPos_TBL[i].y + pPos[CONTROLLER_P3].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// ダメージを受けていた時
				if (GetCarbuncleDamageData() != 0)
				{
					// ダメージ値が偶数の時
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
					// ダメージ値が奇数の時
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
					// P4のSlimeのHP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[0], true);

					// 体力が0
					if (GetSlimeDamageData() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// ダメージを受けていた時
				if (GetSlimeDamageData() != 0)
				{
					// ダメージ値が偶数の時
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
					// ダメージ値が奇数の時
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
					// P4のSkeletonのHP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[0], true);

					// 体力が0
					if (GetSkeletonDamageData() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// ダメージを受けていた時
				if (GetSkeletonDamageData() != 0)
				{
					// ダメージ値が偶数の時
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
					// ダメージ値が奇数の時
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
					// P4のCarbuncleのHP
					DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[0], true);

					// 体力が0
					if (GetCarbuncleDamageData() > 6)
					{
						DrawGraph(hpPos_TBL[i].x + pPos[CONTROLLER_P4].x, hpPos_TBL[i].y + pPos[CONTROLLER_P4].y, lpImageMng.GetID("image/hp.png")[2], true);
					}
				}
				// ダメージを受けていた時
				if (GetCarbuncleDamageData() != 0)
				{
					// ダメージ値が偶数の時
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
					// ダメージ値が奇数の時
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