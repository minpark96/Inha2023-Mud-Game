#include "main.h"

void PrintMainMenu(void)
{
	SetColor(DARK_YELLOW);
	gotoxy(TITLE_X, TITLE_Y); printf("#### ###    #     ##### ### #### ######  ######  ####  ##### ######\n");
	gotoxy(TITLE_X, TITLE_Y + 1); printf(" ##   #    ###   ##   #  ##  ##  # ## #   ##  ##  ##  ##   #  ##  #\n");
	gotoxy(TITLE_X, TITLE_Y + 2); printf("  ## #     ###   ##      ##  ##    ##     ##  ##  ##  ##      ##   \n");
	gotoxy(TITLE_X, TITLE_Y + 3); printf("  ####     # #   ##      ######    ##     ##  ##  ##  ##      #### \n");
	gotoxy(TITLE_X, TITLE_Y + 4); printf("   ##     #####  ##      ##  ##    ##     ##  ##  ##  ##      ##   \n");
	gotoxy(TITLE_X, TITLE_Y + 5); printf("   ##     #  ##  ##   #  ##  ##    ##     ##  ##  ##  ##   #  ##  #\n");
	gotoxy(TITLE_X, TITLE_Y + 6); printf("  ####   ### ###  ##### #### ###  ####   ######  ####  ##### ######\n");
	SetColor(BRIGHT_WHITE);
}

void PrintRoundInfo()
{
	cls;
	SetColor(SKY_BLUE);
	gotoxy(ROUND_X, ROUND_Y); printf("%2d번째 턴 - 플레이어%d\n", turn, player);
	SetColor(BRIGHT_WHITE);
	Sleep(POPUP_DELAY);
	cls;
}

void PrintKeepedDice(void)
{
	gotoxy(KEEPED_DICE_TITLE_X, KEEPED_DICE_TITLE_Y); printf("Keeped  Dice");

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
			PrintDiceNull(x, y);
		}
	}
}

void PrintRolledDice()
{
	int count = CountRolledDice();

	gotoxy(ROLLED_DICE_TITLE_X, ROLLED_DICE_TITLE_Y); printf("Rolled  Dice");

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

void PrintDiceNull(int x, int y)
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
	int x, y;
	if (turn > MAX_NUMBER_OF_TURNS)
	{
		x = GAME_OVER_X;
		y = GAME_OVER_Y;
	}
	else 
	{
		x = SCOREBOARD_X;
		y = SCOREBOARD_Y;
	}

	gotoxy(x, y); puts("                ■■■■■■■■■■■■■");
	if (turn > MAX_NUMBER_OF_TURNS)
	{
		gotoxy(x, y + 2); printf("                ■ Player 1 ■ Player 2 ■\n");

		if (totalP1 > totalP2)
		{
			gotoxy(x, y + 1); puts("     Results    ■  Winner! ■Too Bad...■");
			gotoxy(x, y + 3); printf("   Categories   ■    1st   ■    2nd   ■\n");
		}
		else if (totalP1 < totalP2)
		{
			gotoxy(x, y + 1); puts("     Results    ■Too Bad...■  Winner! ■");
			gotoxy(x, y + 3); printf("   Categories   ■    2nd   ■    1st   ■\n");
		}
		else
		{
			gotoxy(x, y + 1); puts("     Results    ■   Draw   ■   Draw   ■");
			gotoxy(x, y + 3); printf("   Categories   ■    1st   ■    1st   ■\n");
		}
	}
	else
	{
		gotoxy(x, y + 1); puts("       Turn     ■          ■          ■");
		gotoxy(x, y + 2); printf("      %2d/12     ■ Player 1 ■ Player 2 ■\n", turn);
		gotoxy(x, y + 3); printf("   Categories   ■          ■          ■\n");
	}
	
	
	gotoxy(x, y + 4); puts("■■■■■■■■■■■■■■■■■■■■■");
	for (int i = ACES; i < CHOICE; i++)
	{
		gotoxy(x, y + 4 + i); PrintPointElements(i);
	}
	gotoxy(x, y + 11); puts("■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(x, y + 12); printf("■ Subtotal     ■  %3d/63  ■  %3d/63  ■\n", subTotalP1, subTotalP2);
	gotoxy(x, y + 13); PrintPointElements(BONUS);
	gotoxy(x, y + 14); puts("■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(x, y + 15); puts(" Bonus if Aces ~ Sixes are over 63 points");
	gotoxy(x, y + 16); puts("■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(x, y + 17); PrintPointElements(CHOICE);
	gotoxy(x, y + 18); puts("■■■■■■■■■■■■■■■■■■■■■");
	for (int i = FOUR_OF_A_KIND; i < SCOREBOARD_ITEM_COUNT; i++)
	{
		gotoxy(x, y + 18 + i - 7); PrintPointElements(i);
	}
	gotoxy(x, y + 24); puts("■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(x, y + 25); printf("■ Total        ■   %3d    ■   %3d    ■\n", totalP1, totalP2);
	gotoxy(x, y + 26); printf("■■■■■■■■■■■■■■■■■■■■■");
}

void PrintPointElements(int num)
{
	char* name[SCOREBOARD_ITEM_COUNT] = { "Bonus", "Aces", "Deuces", "Threes", "Fours", "Fives", "Sixes", "Choice",
	"4 of a Kind", "Full House", "S. Straight", "L. Straight", "Yacht" };

	if (num == BONUS)
	{
		if (point[num]->isUsedP1 == 2 && point[num]->isUsedP2 == 2)
			printf("■ +35 %s    ■   +%2d    ■   +%2d    ■\n", name[num], point[num]->pointP1, point[num]->pointP2);
		else if (point[num]->isUsedP1 == 2)
			printf("■ +35 %s    ■   +%2d    ■          ■\n", name[num], point[num]->pointP1);
		else if (point[num]->isUsedP2 == 2)
			printf("■ +35 %s    ■          ■   +%2d    ■\n", name[num], point[num]->pointP2);
		else
			printf("■ +35 %s    ■          ■          ■\n", name[num]);
	}
	else
	{
		if (strlen(name[num]) > strlen(name[FULL_HOUSE]))
			printf("■ %s  ■", name[num]);
		else if (strlen(name[num]) > strlen(name[DEUCES]))
			printf("■ %s   ■", name[num]);
		else if (strlen(name[num]) > strlen(name[FOURS]))
			printf("■ %s       ■", name[num]);
		else if (strlen(name[num]) > strlen(name[ACES]))
			printf("■ %s        ■", name[num]);
		else
			printf("■ %s         ■", name[num]);

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

void PrintHeader()
{
	gotoxy(PLAYER_X, PLAYER_Y); printf("Player %d\n", player);
	gotoxy(ROLL_COUNT_X, ROLL_COUNT_Y); printf("Roll: %d left\n", MAX_NUMBER_OF_ROLLS - rollCount);
}

void PrintUI()
{
	cls;
	PrintHeader();
	PrintKeepedDice();
	PrintRolledDice();
	PrintScoreboard();
}