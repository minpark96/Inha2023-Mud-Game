#include "main.h"

extern int turn;
extern int player;
extern int rollCount;

void PrintMainMenu(void)
{
	srand(time(0));
	CursorView(0);
	system("COLOR 0F");
	system("mode con: cols=102 lines=16");

	system("title 요트 다이스 게임");
	SetColor(DARK_YELLOW);
	printf("\n");
	printf("\n");
	printf("\t\t#### ###    #     ##### ### #### ######  ######  ####  ##### ######\n");
	printf("\t\t ##   #    ###   ##   #  ##  ##  # ## #   ##  ##  ##  ##   #  ##  #\n");
	printf("\t\t  ## #     ###   ##      ##  ##    ##     ##  ##  ##  ##      ##   \n");
	printf("\t\t  ####     # #   ##      ######    ##     ##  ##  ##  ##      #### \n");
	printf("\t\t   ##     #####  ##      ##  ##    ##     ##  ##  ##  ##      ##   \n");
	printf("\t\t   ##     #  ##  ##   #  ##  ##    ##     ##  ##  ##  ##   #  ##  #\n");
	printf("\t\t  ####   ### ###  ##### #### ###  ####   ######  ####  ##### ######\n");
	return;
}

void ShowTurnAndPlayer()
{
	system("mode con: cols=102 lines=16");
	SetColor(SKY_BLUE);
	gotoxy(ROUND_X, ROUND_Y); printf("%2d번째 턴 - 플레이어%d\n", turn, player);
	SetColor(BRIGHT_WHITE);
	return;
}

void PrintKeepedDice(void)
{
	gotoxy(KEEPED_DICE_TITLE_X, KEEPED_DICE_TITLE_Y); printf("Keeped Dice");

	int x;
	int y = KEEPED_DICE_Y;

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		x = GetKeepedDiceX(i);

		switch (keepedDice[i])
		{
		case 1:
			PrintDiceOne(x, y);
			break;
		case 2:
			PrintDiceTwo(x, y);
			break;
		case 3:
			PrintDiceThree(x, y);
			break;
		case 4:
			PrintDiceFour(x, y);
			break;
		case 5:
			PrintDiceFive(x, y);
			break;
		case 6:
			PrintDiceSix(x, y);
			break;
		default:
			PrintNull(x, y);
		}
	}
}

int GetKeepedDiceX(int i)
{
	switch (i)
	{
	case 0:
		return KEEPED_DICE_1_X;
	case 1:
		return KEEPED_DICE_2_X;
	case 2:
		return KEEPED_DICE_3_X;
	case 3:
		return KEEPED_DICE_4_X;
	case 4:
		return KEEPED_DICE_5_X;
	}
}

void PrintRolledDice(int count)
{
	gotoxy(ROLLED_DICE_TITLE_X, ROLLED_DICE_TITLE_Y); printf("Rolled Dice");

	int x;
	int y = ROLLED_DICE_Y;

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (count == 0)
			break;
		else
			x = GetRolledDiceX(count, i);
		
		switch (rolledDice[i])
		{
		case 1:
			PrintDiceOne(x, y);
			break;
		case 2:
			PrintDiceTwo(x, y);
			break;
		case 3:
			PrintDiceThree(x, y);
			break;
		case 4:
			PrintDiceFour(x, y);
			break;
		case 5:
			PrintDiceFive(x, y);
			break;
		case 6:
			PrintDiceSix(x, y);
			break;
		default:
			break;
		}
	}
}

int GetRolledDiceX(int count, int i)
{
	switch (count)
	{
	case 1:
			return KEEPED_DICE_3_X;
	case 2:
		switch (i)
		{
		case 0:
			return ROLLED_DICE_2_X;
		case 1:
			return ROLLED_DICE_3_X;
		}
	case 3:
		switch (i)
		{
		case 0:
			return KEEPED_DICE_2_X;
		case 1:
			return KEEPED_DICE_3_X;
		case 2:
			return KEEPED_DICE_4_X;
		}
	case 4:
		switch (i)
		{
		case 0:
			return ROLLED_DICE_1_X;
		case 1:
			return ROLLED_DICE_2_X;
		case 2:
			return ROLLED_DICE_3_X;
		case 3:
			return ROLLED_DICE_4_X;
		}
	case 5:
		return GetKeepedDiceX(i);
	default:
		break;
	}
}

void PrintChooseButton(int POS, int count)
{
	int POSKeep = -1;
	int POSRoll = -1;

	if (POS == 0)
	{
		SetColor(LIGHT_GREEN);
		gotoxy(RETURN_BUTTON_X, RETURN_BUTTON_Y); printf("Return");
		SetColor(BRIGHT_WHITE);
	}
	else if (POS > NUMBER_OF_DICE)
	{
		gotoxy(RETURN_BUTTON_X, RETURN_BUTTON_Y); printf("Return");
		POSKeep = POS - (NUMBER_OF_DICE + 1);
		for (int i = 0; i < POSKeep + 1; i++)
		{
			if (keepedDice[i] == 0)
			{
				POSKeep++;
			}
		}
	}
	else
	{
		gotoxy(RETURN_BUTTON_X, RETURN_BUTTON_Y); printf("Return");
		POSRoll = POS - 1;
		for (int i = 0; i < POSRoll + 1; i++)
		{
			if (rolledDice[i] == NULL_VALUE_IN_ROLLED_DICE)
			{
				break;
			}
		}
	}

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (keepedDice[i] != 0 && i == POSKeep)
		{
			SetColor(BACKGROUND_LIGHT_GREEN);
			gotoxy(GetKeepedDiceX(i) + NUMBER_OF_DICE + 1, DISCARD_BUTTON_Y); printf("▲");
			SetColor(BRIGHT_WHITE);
		}
		else if (keepedDice[i] != 0)
		{
			gotoxy(GetKeepedDiceX(i) + NUMBER_OF_DICE + 1, DISCARD_BUTTON_Y); printf("▲");
		}
		else;

		if (rolledDice[i] != NULL_VALUE_IN_ROLLED_DICE && i == POSRoll)
		{
			SetColor(BACKGROUND_LIGHT_GREEN);
			gotoxy(GetRolledDiceX(count, i) + NUMBER_OF_DICE + 1, KEEP_BUTTON_Y); printf("▲");
			SetColor(BRIGHT_WHITE);
		}
		else if (rolledDice[i] != NULL_VALUE_IN_ROLLED_DICE)
		{
			gotoxy(GetRolledDiceX(count, i) + NUMBER_OF_DICE + 1, KEEP_BUTTON_Y); printf("▲");
		}
		else;
	}
}

void ShowTempPoints()
{
	if (player == 1)
	{
		for (int i = 1; i < SCOREBOARD_ITEM_COUNT; i++)
		{
			if (point[i]->isUsedP1 == 0)
			{
				point[i]->isUsedP1++;
			}
		}
	}
	else
	{
		for (int i = 1; i < SCOREBOARD_ITEM_COUNT; i++)
		{
			if (point[i]->isUsedP2 == 0)
			{
				point[i]->isUsedP2++;
			}
		}
	}
}

void HideTempPoints()
{
	if (player == 1)
	{
		for (int i = 1; i < SCOREBOARD_ITEM_COUNT; i++)
		{
			if (point[i]->isUsedP1 == 1)
			{
				point[i]->isUsedP1--;
			}
		}
	}
	else
	{
		for (int i = 1; i < SCOREBOARD_ITEM_COUNT; i++)
		{
			if (point[i]->isUsedP2 == 1)
			{
				point[i]->isUsedP2--;
			}
		}
	}
}

void PrintDiceOne(int x, int y)
{
	gotoxy(x, y); printf("■■■■■■■");
	gotoxy(x, y + 1); printf("■          ■\n");
	gotoxy(x, y + 2); printf("■          ■\n");
	gotoxy(x, y + 3); printf("■    ●    ■\n");
	gotoxy(x, y + 4); printf("■          ■\n");
	gotoxy(x, y + 5); printf("■          ■\n");
	gotoxy(x, y + 6); printf("■■■■■■■\n");
}

void PrintDiceTwo(int x, int y)
{
	gotoxy(x, y); printf("■■■■■■■");
	gotoxy(x, y + 1); printf("■          ■\n");
	gotoxy(x, y + 2); printf("■  ●      ■\n");
	gotoxy(x, y + 3); printf("■          ■\n");
	gotoxy(x, y + 4); printf("■      ●  ■\n");
	gotoxy(x, y + 5); printf("■          ■\n");
	gotoxy(x, y + 6); printf("■■■■■■■\n");
}

void PrintDiceThree(int x, int y)
{
	gotoxy(x, y); printf("■■■■■■■");
	gotoxy(x, y + 1); printf("■          ■\n");
	gotoxy(x, y + 2); printf("■  ●      ■\n");
	gotoxy(x, y + 3); printf("■    ●    ■\n");
	gotoxy(x, y + 4); printf("■      ●  ■\n");
	gotoxy(x, y + 5); printf("■          ■\n");
	gotoxy(x, y + 6); printf("■■■■■■■\n");
}

void PrintDiceFour(int x, int y)
{
	gotoxy(x, y); printf("■■■■■■■");
	gotoxy(x, y + 1); printf("■          ■\n");
	gotoxy(x, y + 2); printf("■  ●  ●  ■\n");
	gotoxy(x, y + 3); printf("■          ■\n");
	gotoxy(x, y + 4); printf("■  ●  ●  ■\n");
	gotoxy(x, y + 5); printf("■          ■\n");
	gotoxy(x, y + 6); printf("■■■■■■■\n");
}

void PrintDiceFive(int x, int y)
{
	gotoxy(x, y); printf("■■■■■■■");
	gotoxy(x, y + 1); printf("■          ■\n");
	gotoxy(x, y + 2); printf("■  ●  ●  ■\n");
	gotoxy(x, y + 3); printf("■    ●    ■\n");
	gotoxy(x, y + 4); printf("■  ●  ●  ■\n");
	gotoxy(x, y + 5); printf("■          ■\n");
	gotoxy(x, y + 6); printf("■■■■■■■\n");
}

void PrintDiceSix(int x, int y)
{
	gotoxy(x, y); printf("■■■■■■■");
	gotoxy(x, y + 1); printf("■          ■\n");
	gotoxy(x, y + 2); printf("■  ●  ●  ■\n");
	gotoxy(x, y + 3); printf("■  ●  ●  ■\n");
	gotoxy(x, y + 4); printf("■  ●  ●  ■\n");
	gotoxy(x, y + 5); printf("■          ■\n");
	gotoxy(x, y + 6); printf("■■■■■■■\n");
}

void PrintNull(int x, int y)
{
	gotoxy(x, y); printf("■■■■■■■");
	gotoxy(x, y + 1); printf("■          ■\n");
	gotoxy(x, y + 2); printf("■          ■\n");
	gotoxy(x, y + 3); printf("■          ■\n");
	gotoxy(x, y + 4); printf("■          ■\n");
	gotoxy(x, y + 5); printf("■          ■\n");
	gotoxy(x, y + 6); printf("■■■■■■■\n");
}

void PrintScoreboard()
{
	gotoxy(0, 30); puts("■■■■■■■■■■■■■■■■■■■■■");
	puts("■     Turn\t■          ■          ■");
	printf("■    %2d/12\t■ Player 1 ■ Player 2 ■\n", turn);
	printf("■ Categories\t■          ■          ■\n");
	puts("■■■■■■■■■■■■■■■■■■■■■");
	for (int i = ACES; i < CHOICE; i++)
	{
		PrintLine(i);
	}
	puts("■■■■■■■■■■■■■■■■■■■■■");
	printf("■ Subtotal\t■  %3d/63  ■  %3d/63  ■\n", subTotalP1, subTotalP2);
	PrintLine(BONUS);
	puts("■■■■■■■■■■■■■■■■■■■■■");
	for (int i = CHOICE; i < SCOREBOARD_ITEM_COUNT; i++)
	{
		PrintLine(i);
	}
	puts("■■■■■■■■■■■■■■■■■■■■■");
	printf("■ Total\t■   %3d    ■   %3d    ■\n", totalP1, totalP2);
	printf("■■■■■■■■■■■■■■■■■■■■■");
}

void PrintLine(int num)
{
	char* name[SCOREBOARD_ITEM_COUNT] = { "Bonus", "Aces", "Deuces", "Threes", "Fours", "Fives", "Sixes", "Choice",
	"4 of a Kind", "Full House", "S. Straight", "L. Straight", "Yacht" };

	if (num == 1)
	{
		printf("■ %s\t\t■", name[num]);
		if (point[num]->isUsedP1 == 2)
			printf("    %2d    ■", point[num]->pointP1);
		else if (point[num]->isUsedP1 == 1)
		{
			SetColor(GRAY);
			printf("    %2d    ", point[num]->pointP1);
			SetColor(BRIGHT_WHITE);
			printf("■");
		}
		else
			printf("          ■");

		if (point[num]->isUsedP2 == 2)
			printf("    %2d    ■\n", point[num]->pointP2);
		else if (point[num]->isUsedP2 == 1)
		{
			SetColor(GRAY);
			printf("    %2d    ", point[num]->pointP2);
			SetColor(BRIGHT_WHITE);
			printf("■\n");
		}
		else
			printf("          ■\n");
	}
	else if (num == 0) // 뽀너스
	{
		if (point[num]->isUsedP1 == 2 && point[num]->isUsedP2 == 2)
			printf("■ +35 %s\t■   +%2d    ■   +%2d    ■\n", name[num], point[num]->pointP1, point[num]->pointP2);
		else if (point[num]->isUsedP1 == 2)
			printf("■ +35 %s\t■   +%2d    ■          ■\n", name[num], point[num]->pointP1);
		else if (point[num]->isUsedP2 == 2)
			printf("■ +35 %s\t■          ■   +%2d    ■\n", name[num], point[num]->pointP2);
		else
			printf("■ +35 %s\t■          ■          ■\n", name[num]);
	}
	else // ACES 제외
	{
		printf("■ %s\t■", name[num]);
		if (point[num]->isUsedP1 == 2)
			printf("    %2d    ■", point[num]->pointP1);
		else if (point[num]->isUsedP1 == 1)
		{
			SetColor(GRAY);
			printf("    %2d    ", point[num]->pointP1);
			SetColor(BRIGHT_WHITE);
			printf("■");
		}
		else
			printf("          ■");

		if (point[num]->isUsedP2 == 2)
			printf("    %2d    ■\n", point[num]->pointP2);
		else if (point[num]->isUsedP2 == 1)
		{
			SetColor(GRAY);
			printf("    %2d    ", point[num]->pointP2);
			SetColor(BRIGHT_WHITE);
			printf("■\n");
		}
		else
			printf("          ■\n");
	}
}