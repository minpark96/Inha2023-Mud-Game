#include "main.h"

extern int turn;
extern int player;
extern int rollCount;

void Start()
{
	int POS = 0;
	PrintMainMenu();

	while (1)
	{
		if (GetAsyncKeyState(VK_LEFT))
			if (POS == 0) POS = 1;
			else POS -= 1;
		else if (GetAsyncKeyState(VK_RIGHT))
			if (POS == 1) POS = 0;
			else POS += 1;
		else if (GetAsyncKeyState(VK_RETURN))
			if (POS == 0)
				PlayGame(POS);
			else
				break;
		else;

		switch (POS)
		{
		case 0:
			SetColor(LIGHT_GREEN);
			gotoxy(PLAY_X, PLAY_Y); printf("플레이");
			SetColor(BRIGHT_WHITE);
			gotoxy(QUIT_X, QUIT_Y); printf("게임  종료");
			break;
		case 1:
			gotoxy(PLAY_X, PLAY_Y); printf("플레이");
			SetColor(LIGHT_GREEN);
			gotoxy(QUIT_X, QUIT_Y); printf("게임  종료");
			SetColor(BRIGHT_WHITE);
			break;
		default: break;
		}
		Sleep(BUTTON_DELAY);
	}
	cls;
	puts("게임을 종료합니다.");
}

void PlayGame(int POS)
{
	int count;

	Init();
	cls;
	ShowTurnAndPlayer();
	Sleep(1000);
	system("mode con: cols=150 lines=70");
	while (1)
	{
		cls;
		count = CountRolledDice();
		gotoxy(PLAYER_X, PLAYER_Y); printf("Player%d\n", player);
		gotoxy(ROLL_COUNT_X, ROLL_COUNT_Y); printf("Roll: %d left\n", 3 - rollCount);
		PrintKeepedDice();
		PrintRolledDice(count);
		PrintScoreboard();
		if (rollCount == 0)
		{
			if (GetAsyncKeyState(VK_RETURN))
			{
				RollTheDice(&rollCount);
			}
			SetColor(LIGHT_GREEN);
			gotoxy(33, 22); printf("Roll\n");
			SetColor(BRIGHT_WHITE);
		}
		else if (rollCount == MAX_NUMBER_OF_ROLLS)
		{
			if (GetAsyncKeyState(VK_RETURN))
			{
				Sleep(SELECT_DELAY);
				ChooseCategory();
				if (turn > MAX_NUMBER_OF_TURNS)
					break;
			}
			SetColor(11);
			gotoxy(28, 22); printf("Choose Category\n");
			SetColor(15);
		}
		else
		{
			if (GetAsyncKeyState(VK_LEFT))
				if (POS == 0) POS = 2;
				else POS -= 1;
			else if (GetAsyncKeyState(VK_RIGHT))
				if (POS == 2) POS = 0;
				else POS += 1;
			else if (GetAsyncKeyState(VK_RETURN))
			{
				if (POS == 0)
				{
					Sleep(SELECT_DELAY);
					ChooseCategory();
				}
				else if (POS == 1)
				{
					Sleep(SELECT_DELAY);
					KeepAndDiscard();
				}
				else
				{
					Sleep(SELECT_DELAY);
					RollTheDice(&rollCount);
				}
			}
			else;

			switch (POS)
			{
			case 0:
				SetColor(11);
				gotoxy(3, 22); printf("Choose Category\n");
				SetColor(15);
				gotoxy(33, 22); printf("Keep\n");
				gotoxy(60, 22); printf("Reroll\n");
				break;
			case 1:
				gotoxy(3, 22); printf("Choose Category\n");
				SetColor(11);
				gotoxy(33, 22); printf("Keep\n");
				SetColor(15);
				gotoxy(60, 22); printf("Reroll\n");
				break;
			case 2:
				gotoxy(3, 22); printf("Choose Category\n");
				gotoxy(33, 22); printf("Keep\n");
				SetColor(11);
				gotoxy(60, 22); printf("Reroll\n");
				SetColor(15);
				break;
			}
		}
		Sleep(BUTTON_DELAY);
	}
}

int CountRolledDice()
{
	int count = 0;

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (rolledDice[i] != NULL_VALUE_IN_ROLLED_DICE)
		{
			count++;
		}
	}

	return count;
}
