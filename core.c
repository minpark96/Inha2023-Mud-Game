#include "main.h"

void Start()
{
	int POS = 0;
	srand(time(0));
	CursorView(0);
	system("COLOR 0F");
	system("title 요트 다이스 게임");
	system("mode con: cols=137 lines=31");
	while (1)
	{
		PrintMainMenu();
		if (GetAsyncKeyState(VK_LEFT))
			if (POS == 0) POS = 1;
			else POS -= 1;
		else if (GetAsyncKeyState(VK_RIGHT))
			if (POS == 1) POS = 0;
			else POS += 1;
		else if (GetAsyncKeyState(VK_RETURN))
			if (POS == 0)
			{
				Play();
				continue;
			}
			else
				break;
		else;

		MoveMainMenuButton(POS);
		Sleep(BUTTON_DELAY);
	}
	cls;
	puts("게임을 종료합니다.");
}

void Play()
{
	int POS = 0;

	Init();
	PrintRoundInfo();
	PrintUI();
	while (1)
	{
		if (rollCount == 0)
		{
			ShakeAndRoll();
		}
		else if (rollCount == MAX_NUMBER_OF_ROLLS)
		{
			ChooseCategory();
			Sleep(SELECT_DELAY);
			if (turn > MAX_NUMBER_OF_TURNS)
			{
				GameOver();
				Sleep(SELECT_DELAY);
				break;
			}
			continue;
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
					Sleep(SELECT_DELAY);
					if (turn > MAX_NUMBER_OF_TURNS)
					{
						GameOver();
						Sleep(SELECT_DELAY);
						break;
					}
					continue;
				}
				else if (POS == 1)
				{
					Sleep(SELECT_DELAY);
					KeepAndDiscard();
					Sleep(SELECT_DELAY);
					continue;
				}
				else
				{
					Sleep(SELECT_DELAY);
					ShakeAndRoll();
					continue;
				}
			}
			else;

			MoveCoreButton(POS);
		}

		Sleep(BUTTON_DELAY);
	}
}

void ShakeAndRoll()
{
	int POS;
	int tempDice[5];

	if (rollCount != 0)
	{
		for (int idx = 0; idx < NUMBER_OF_DICE; idx++)
		{
			tempDice[idx] = rolledDice[idx];
		}
		POS = 2;
	}
	else
	{
		POS = 0;
	}

	PrintUI();
	while (1)
	{
		if (rollCount == 0)
		{
			if (GetAsyncKeyState(VK_LEFT))
				if (POS == 0) POS = 1;
				else POS -= 1;
			else if (GetAsyncKeyState(VK_RIGHT))
				if (POS == 1) POS = 0;
				else POS += 1;
			else if (GetAsyncKeyState(VK_RETURN))
			{
				if (POS)
				{
					RollDice();
					break;
				}
				else
				{
					ShakeDice();
					continue;
				}
			}
			else;
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
				if (POS == 1)
				{
					RollDice();
					break;
				}
				else if (POS == 0)
				{
					ShakeDice();
					continue;
				}
				else
				{
					for (int idx = 0; idx < NUMBER_OF_DICE; idx++)
					{
						rolledDice[idx] = tempDice[idx];
					}
					Sleep(SELECT_DELAY);
					PrintUI();
					break;
				}
			}
			else;
		}
		
		MoveShakeAndRollButton(POS);
		Sleep(BUTTON_DELAY);
	}
}

void KeepAndDiscard()
{
	int POS = 0;
	int cntKeepedDice = 0;
	int cntRolledDice = 0;
	int idxKeepedDice[NUMBER_OF_DICE] = { 0 };

	PrintUI();
	while (1)
	{
		cntRolledDice = CountRolledDice();
		cntKeepedDice = CountKeepedDice(&idxKeepedDice);

		
		if (GetAsyncKeyState(VK_LEFT))
			if (POS == 1) POS = cntRolledDice;
			else if (POS == NUMBER_OF_DICE + 1) POS = cntKeepedDice + NUMBER_OF_DICE;
			else if (POS == 0);
			else POS -= 1;
		else if (GetAsyncKeyState(VK_RIGHT))
			if (POS == cntRolledDice) POS = 1;
			else if (POS == cntKeepedDice + NUMBER_OF_DICE) POS = NUMBER_OF_DICE + 1;
			else if (POS == 0);
			else POS += 1;
		else if (GetAsyncKeyState(VK_UP))
			if (POS == 0 && cntRolledDice != 0) POS = 1;
			else if (POS == 0 && cntRolledDice == 0) POS = NUMBER_OF_DICE + 1;
			else if (POS < NUMBER_OF_DICE + 1 && cntKeepedDice != 0) POS = NUMBER_OF_DICE + 1;
			else;
		else if (GetAsyncKeyState(VK_DOWN))
			if (POS > NUMBER_OF_DICE && cntRolledDice != 0) POS = 1;
			else if (POS > NUMBER_OF_DICE && cntRolledDice == 0) POS = 0;
			else if (POS > 0 && POS < NUMBER_OF_DICE + 1) POS = 0;
			else;
		else if (GetAsyncKeyState(VK_RETURN))
		{
			if (POS > 0 && POS < NUMBER_OF_DICE + 1)
			{
				KeepDice(POS - 1);
				POS = 0;
				Sleep(SELECT_DELAY);
				PrintUI();
				continue;
			}
			else if (POS > NUMBER_OF_DICE)
			{
				DiscardDice(idxKeepedDice[POS - (NUMBER_OF_DICE + 1)]);
				POS = 0;
				Sleep(SELECT_DELAY);
				PrintUI();
				continue;
			}
			else
			{
				PrintUI();
				break;
			}
		}
		else;

		MoveKeepAndDiscardButton(POS, cntRolledDice);
		Sleep(BUTTON_DELAY);
	}
}

void ChooseCategory()
{
	int idx = 0;
	int cntPoints = MAX_NUMBER_OF_TURNS - (turn - 1);
	int POSset[SCOREBOARD_ITEM_COUNT - 1] = { 0 };
	SetPOSset(&POSset);
	int POS;

	if (rollCount == MAX_NUMBER_OF_ROLLS)
		POS = POSset[0];
	else
		POS = 0;

	PrintUI();
	while (1)
	{
		
		if (GetAsyncKeyState(VK_LEFT))
			if (rollCount != MAX_NUMBER_OF_ROLLS && POS == 0)
				POS = POSset[0];
			else;
		else if (GetAsyncKeyState(VK_RIGHT))
			if (rollCount != MAX_NUMBER_OF_ROLLS && POS != 0)
			{
				POS = 0;
				idx = 0;
				PrintUI();
			}
			else;
		else if (GetAsyncKeyState(VK_UP))
			if (idx != 0)
				POS = POSset[--idx];
			else;
		else if (GetAsyncKeyState(VK_DOWN))
			if (POS != 0 && idx != cntPoints - 1)
				POS = POSset[++idx];
			else;
		else if (GetAsyncKeyState(VK_RETURN))
		{
			if (POS == 0)
			{
				PrintUI();
				break;
			}
			else
			{
				ToggleTempPoints();
				CountTotal(POS);
				ResetRound();
				cls;
				break;
			}
		}
		else;

		MoveChooseCategoryButton(POS);
		Sleep(BUTTON_DELAY);
	}
}

void GameOver()
{
	PrintScoreboard();

	while (1)
	{
		if (GetAsyncKeyState(VK_RETURN))
		{
			cls;
			break;
		}
		SetColor(LIGHT_GREEN);
		gotoxy(NEXT_X, BUTTON_Y); printf("Next\n");
		SetColor(BRIGHT_WHITE);
	}

	turn = 1;
	totalP1 = 0;
	totalP2 = 0;
	subTotalP1 = 0;
	subTotalP2 = 0;

	for (int i = 0; i < SCOREBOARD_ITEM_COUNT; i++)
	{
		 free(point[i]);
	}

}