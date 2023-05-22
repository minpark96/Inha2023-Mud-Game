#include "main.h"

extern int turn;
extern int player;
extern int rollCount;

void ChooseCategory()
{
	int idx = 0;
	int cntPoints = MAX_NUMBER_OF_TURNS - (turn - 1);
	int POSset[SCOREBOARD_ITEM_COUNT - 1] = { 0 };
	SetPOSset(&POSset);
	int POS = POSset[0];

	while (1)
	{
		cls;
		gotoxy(0, 0); printf("Player%d\n", player);
		gotoxy(58, 0); printf("Roll: %d left\n", MAX_NUMBER_OF_ROLLS - rollCount);
		PrintKeepedDice();
		PrintRolledDice();
		PrintScoreboard();

		if (GetAsyncKeyState(VK_UP))
			if (rollCount != 3 && idx == 0)
				POS = 0;
			else if (idx != 0)
				POS = POSset[--idx];
			else;
		else if (GetAsyncKeyState(VK_DOWN))
			if (POS == 0)
				POS = POSset[0];
			else if (idx != cntPoints - 1)
				POS = POSset[++idx];
			else;
		else if (GetAsyncKeyState(VK_RETURN))
		{
			if (POS == 0)
			{
				Sleep(50);
				break;
			}
			else
			{
				Sleep(50);
				HideTempPoints();
				CountTotal(POS);
				Reset();

				break;
			}
		}
		else;

		MovingOnTheScoreboard(POS);

		Sleep(100);
	}
}

void SetPOSset(int** POSset)
{
	int idx = 0;

	if (player == 1)
	{
		for (int i = 1; i < SCOREBOARD_ITEM_COUNT; i++)
		{
			if (point[i]->isUsedP1 == 1)
			{
				*(POSset + idx) = i;
				idx++;
			}
		}
	}
	else
	{
		for (int i = 1; i < SCOREBOARD_ITEM_COUNT; i++)
		{
			if (point[i]->isUsedP2 == 1)
			{
				*(POSset + idx) = i;
				idx++;
			}
		}
	}
}

void Reset()
{
	memset(keepedDice, 0, sizeof(keepedDice));
	memset(rolledDice, NULL_VALUE_IN_ROLLED_DICE, sizeof(rolledDice));
	memset(finalDice, 0, sizeof(finalDice));

	if (player == 1)
	{
		player++;
		rollCount = 0;
	}
	else
	{
		player = 1;
		rollCount = 0;
		turn++;
	}
	cls;
	ShowTurnAndPlayer();
	Sleep(1000);
	cls;
	system("mode con: cols=70 lines=48");
}

void CountTotal(int POS)
{
	int isBonus = 1;

	if (player == 1)
	{
		if (POS < CHOICE)
			subTotalP1 += point[POS]->pointP1;

		point[POS]->isUsedP1 = 2;

		for (int i = ACES; i < CHOICE; i++)
		{
			if (point[i]->isUsedP1 != 2)
			{
				isBonus = 0;
				break;
			}
		}

		if (point[BONUS]->isUsedP1 != 2 && isBonus)
		{
			SetBonus();
		}

		totalP1 += point[POS]->pointP1;
	}
	else
	{
		if (POS < CHOICE)
			subTotalP2 += point[POS]->pointP2;

		point[POS]->isUsedP2 = 2;

		for (int i = ACES; i < CHOICE; i++)
		{
			if (point[i]->isUsedP2 != 2)
			{
				isBonus = 0;
				break;
			}
		}

		if (point[BONUS]->isUsedP2 != 2 && isBonus)
		{
			SetBonus();
		}

		totalP2 += point[POS]->pointP2;
	}
}

void MovingOnTheScoreboard(int POS)
{
	if (rollCount != MAX_NUMBER_OF_ROLLS)
	{
		if (POS == 0)
		{
			SetColor(11);
			gotoxy(33, 22); printf("Back");
			SetColor(15);
		}
		else
		{
			gotoxy(33, 22); printf("Back");
			if (player == 1)
			{
				SetColor(LIGHT_GREEN);
				gotoxy(18, GetY(POS)); printf("    %2d    ", point[POS]->pointP1);
				SetColor(BRIGHT_WHITE);
			}
			else
			{
				SetColor(LIGHT_GREEN);
				gotoxy(30, GetY(POS)); printf("    %2d    ", point[POS]->pointP2);
				SetColor(BRIGHT_WHITE);
			}
		}
	}
	else
	{
		if (player == 1)
		{
			SetColor(LIGHT_GREEN);
			gotoxy(18, GetY(POS)); printf("    %2d    ", point[POS]->pointP1);
			SetColor(BRIGHT_WHITE);
		}
		else
		{
			SetColor(LIGHT_GREEN);
			gotoxy(30, GetY(POS)); printf("    %2d    ", point[POS]->pointP2);
			SetColor(BRIGHT_WHITE);
		}
	}
}

int GetY(int i)
{
	switch (i)
	{
	case ACES:
		return 29;
	case DEUCES:
		return 30;
	case THREES:
		return 31;
	case FOURS:
		return 32;
	case FIVES:
		return 33;
	case SIXES:
		return 34;
	case CHOICE:
		return 39;
	case FOUR_OF_A_KIND:
		return 40;
	case FULL_HOUSE:
		return 41;
	case SMALL_STRAIGHT:
		return 42;
	case LARGE_STRAIGHT:
		return 43;
	case YACHT:
		return 44;
	}
}

