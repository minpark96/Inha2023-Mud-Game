#include "main.h"

void MoveMainMenuButton(int POS)
{
	switch (POS)
	{
	case 0:
		SetColor(LIGHT_GREEN);
		gotoxy(PLAY_BUTTON_X, PLAY_BUTTON_Y); printf("Play");
		SetColor(BRIGHT_WHITE);
		gotoxy(QUIT_BUTTON_X, QUIT_BUTTON_Y); printf("Quit");
		break;
	case 1:
		gotoxy(PLAY_BUTTON_X, PLAY_BUTTON_Y); printf("Play");
		SetColor(LIGHT_GREEN);
		gotoxy(QUIT_BUTTON_X, QUIT_BUTTON_Y); printf("Quit");
		SetColor(BRIGHT_WHITE);
		break;
	default: break;
	}
}

void MoveShakeAndRollButton(int POS)
{
	if (rollCount == 0)
	{
		switch (POS)
		{
		case 0:
			SetColor(LIGHT_GREEN);
			gotoxy(SHAKE_BUTTON_X, BUTTON_Y); printf("Shake");
			SetColor(BRIGHT_WHITE);
			gotoxy(ROLL_BUTTON_X, BUTTON_Y); printf("Roll\n");
			break;
		case 1:
			gotoxy(SHAKE_BUTTON_X, BUTTON_Y); printf("Shake");
			SetColor(LIGHT_GREEN);
			gotoxy(ROLL_BUTTON_X, BUTTON_Y); printf("Roll\n");
			SetColor(BRIGHT_WHITE);
			break;
		default: break;
		}
	}
	else
	{
		switch (POS)
		{
		case 0:
			SetColor(LIGHT_GREEN);
			gotoxy(SHAKE_BUTTON_X, BUTTON_Y); printf("Shake");
			SetColor(BRIGHT_WHITE);
			gotoxy(ROLL_BUTTON_X, BUTTON_Y); printf("Roll\n");
			gotoxy(RETURN_BUTTON_X, BUTTON_Y); printf("Return\n");
			break;
		case 1:
			gotoxy(SHAKE_BUTTON_X, BUTTON_Y); printf("Shake");
			SetColor(LIGHT_GREEN);
			gotoxy(ROLL_BUTTON_X, BUTTON_Y); printf("Roll\n");
			SetColor(BRIGHT_WHITE);
			gotoxy(RETURN_BUTTON_X, BUTTON_Y); printf("Return\n");
			break;
		case 2:
			gotoxy(SHAKE_BUTTON_X, BUTTON_Y); printf("Shake");
			gotoxy(ROLL_BUTTON_X, BUTTON_Y); printf("Roll\n");
			SetColor(LIGHT_GREEN);
			gotoxy(RETURN_BUTTON_X, BUTTON_Y); printf("Return\n");
			SetColor(BRIGHT_WHITE);
			break;
		default: break;
		}
	}
	
}

void MoveCoreButton(int POS)
{
	switch (POS)
	{
	case 0:
		SetColor(LIGHT_GREEN);
		gotoxy(CORE_BUTTON_LEFT_X, BUTTON_Y); printf("Choose Category\n");
		SetColor(BRIGHT_WHITE);
		gotoxy(CORE_BUTTON_MIDDLE_X, BUTTON_Y); printf("Keep & Discard\n");
		gotoxy(CORE_BUTTON_RIGHT_X, BUTTON_Y); printf("Reroll\n");
		break;
	case 1:
		gotoxy(CORE_BUTTON_LEFT_X, BUTTON_Y); printf("Choose Category\n");
		SetColor(LIGHT_GREEN);
		gotoxy(CORE_BUTTON_MIDDLE_X, BUTTON_Y); printf("Keep & Discard\n");
		SetColor(BRIGHT_WHITE);
		gotoxy(CORE_BUTTON_RIGHT_X, BUTTON_Y); printf("Reroll\n");
		break;
	case 2:
		gotoxy(CORE_BUTTON_LEFT_X, BUTTON_Y); printf("Choose Category\n");
		gotoxy(CORE_BUTTON_MIDDLE_X, BUTTON_Y); printf("Keep & Discard\n");
		SetColor(LIGHT_GREEN);
		gotoxy(CORE_BUTTON_RIGHT_X, BUTTON_Y); printf("Reroll\n");
		SetColor(BRIGHT_WHITE);
		break;
	}
}

void MoveKeepAndDiscardButton(int POS, int count)
{
	int POSKeep = -1;
	int POSRoll = -1;

	if (POS == 0)
	{
		SetColor(LIGHT_GREEN);
		gotoxy(RETURN_BUTTON_X, BUTTON_Y); printf("Return");
		SetColor(BRIGHT_WHITE);
	}
	else if (POS > NUMBER_OF_DICE)
	{
		gotoxy(RETURN_BUTTON_X, BUTTON_Y); printf("Return");
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
		gotoxy(RETURN_BUTTON_X, BUTTON_Y); printf("Return");
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
			gotoxy(GetKeepedDiceX(i) + NUMBER_OF_DICE + 1, DISCARD_BUTTON_Y); printf("бу");
			SetColor(BRIGHT_WHITE);
		}
		else if (keepedDice[i] != 0)
		{
			gotoxy(GetKeepedDiceX(i) + NUMBER_OF_DICE + 1, DISCARD_BUTTON_Y); printf("бу");
		}
		else;

		if (rolledDice[i] != NULL_VALUE_IN_ROLLED_DICE && i == POSRoll)
		{
			SetColor(BACKGROUND_LIGHT_GREEN);
			gotoxy(GetRolledDiceX(count, i) + NUMBER_OF_DICE + 1, KEEP_BUTTON_Y); printf("бу");
			SetColor(BRIGHT_WHITE);
		}
		else if (rolledDice[i] != NULL_VALUE_IN_ROLLED_DICE)
		{
			gotoxy(GetRolledDiceX(count, i) + NUMBER_OF_DICE + 1, KEEP_BUTTON_Y); printf("бу");
		}
		else;
	}
}

void MoveChooseCategoryButton(int POS)
{
	if (rollCount != MAX_NUMBER_OF_ROLLS)
	{
		if (POS == 0)
		{
			SetColor(LIGHT_GREEN);
			gotoxy(RETURN_BUTTON_X, BUTTON_Y); printf("Return");
			SetColor(BRIGHT_WHITE);
		}
		else
		{
			gotoxy(RETURN_BUTTON_X, BUTTON_Y); printf("Return");
			for (int i = ACES; i < SCOREBOARD_ITEM_COUNT; i++)
			{
				if (player == 1)
				{
					if (i == POS)
					{
						SetColor(BACKGROUND_LIGHT_GREEN);
						gotoxy(PLAYER_1_X, GetChooseCategoryY(i)); printf("    %2d    ", point[i]->pointP1);
						SetColor(BRIGHT_WHITE);
					}
					else
					{
						if (point[i]->isUsedP1 != 2)
						{
							SetColor(GRAY);
							gotoxy(PLAYER_1_X, GetChooseCategoryY(i)); printf("    %2d    ", point[i]->pointP1);
							SetColor(BRIGHT_WHITE);
						}
					}
				}
				else
				{
					if (i == POS)
					{
						SetColor(BACKGROUND_LIGHT_GREEN);
						gotoxy(PLAYER_2_X, GetChooseCategoryY(i)); printf("    %2d    ", point[i]->pointP2);
						SetColor(BRIGHT_WHITE);
					}
					else
					{
						if (point[i]->isUsedP2 != 2)
						{
							SetColor(GRAY);
							gotoxy(PLAYER_2_X, GetChooseCategoryY(i)); printf("    %2d    ", point[i]->pointP2);
							SetColor(BRIGHT_WHITE);
						}
					}
				}
			}
		}
	}
	else
	{
		for (int i = ACES; i < SCOREBOARD_ITEM_COUNT; i++)
		{
			if (player == 1)
			{
				if (i == POS)
				{
					SetColor(BACKGROUND_LIGHT_GREEN);
					gotoxy(PLAYER_1_X, GetChooseCategoryY(i)); printf("    %2d    ", point[i]->pointP1);
					SetColor(BRIGHT_WHITE);
				}
				else
				{
					if (point[i]->isUsedP1 != 2)
					{
						SetColor(GRAY);
						gotoxy(PLAYER_1_X, GetChooseCategoryY(i)); printf("    %2d    ", point[i]->pointP1);
						SetColor(BRIGHT_WHITE);
					}
				}
			}
			else
			{
				if (i == POS)
				{
					SetColor(BACKGROUND_LIGHT_GREEN);
					gotoxy(PLAYER_2_X, GetChooseCategoryY(i)); printf("    %2d    ", point[i]->pointP2);
					SetColor(BRIGHT_WHITE);
				}
				else
				{
					if (point[i]->isUsedP2 != 2)
					{
						SetColor(GRAY);
						gotoxy(PLAYER_2_X, GetChooseCategoryY(i)); printf("    %2d    ", point[i]->pointP2);
						SetColor(BRIGHT_WHITE);
					}
				}
			}
		}
	}
}