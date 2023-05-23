#include "main.h"

void Init()
{
	turn = 1;
	player = 1;
	rollCount = 0;

	for (int i = 0; i < SCOREBOARD_ITEM_COUNT; i++)
	{
		point[i] = (Point*)malloc(sizeof(Point));

		if (point[i] == NULL)
		{
			printf("메모리 할당 실패\n");
			exit(1);
		}
	}

	for (int i = 0; i < SCOREBOARD_ITEM_COUNT; i++)
	{
		point[i]->pointP1 = 0;
		point[i]->pointP2 = 0;
		point[i]->isUsedP1 = 0;
		point[i]->isUsedP2 = 0;
	}

	memset(rolledDice, NULL_VALUE_IN_ROLLED_DICE, sizeof(rolledDice));
}

void SetScoreboard()
{
	if (player == 1)
	{
		for (int i = ACES; i < SCOREBOARD_ITEM_COUNT; i++)
		{
			if (point[i]->isUsedP1 != 2)
			{
				if (i < CHOICE)
				{
					CountAcesToSixes(i);
				}
				else if (i == CHOICE)
					CountChoice();
				else if (i == FOUR_OF_A_KIND)
					CountFourOfAKind();
				else if (i == FULL_HOUSE)
					CountFullHouse();
				else if (i == SMALL_STRAIGHT)
					CountSmallStraight();
				else if (i == LARGE_STRAIGHT)
					CountLargeStraight();
				else
					CountYacht();
			}
		}
	}
	else
	{
		for (int i = ACES; i < SCOREBOARD_ITEM_COUNT; i++)
		{
			if (point[i]->isUsedP2 != 2)
			{
				if (i < CHOICE)
				{
					CountAcesToSixes(i);
				}
				else if (i == CHOICE)
					CountChoice();
				else if (i == FOUR_OF_A_KIND)
					CountFourOfAKind();
				else if (i == FULL_HOUSE)
					CountFullHouse();
				else if (i == SMALL_STRAIGHT)
					CountSmallStraight();
				else if (i == LARGE_STRAIGHT)
					CountLargeStraight();
				else
					CountYacht();
			}
		}
	}
}

void Sort(int** Dice)
{
	int min;
	int temp;
	int idx;

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		min = INT_MAX;

		for (int j = i; j < NUMBER_OF_DICE; j++)
		{
			if (*(Dice + j) < min)
			{
				min = *(Dice + j);
				idx = j;
			}
		}
		temp = *(Dice + i);
		*(Dice + i) = min;
		*(Dice + idx) = temp;
	}
}

int CountKeepedDice(int** idxKeep)
{
	int count = 0;

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (keepedDice[i])
		{
			idxKeep[count] = i;
			count++;
		}
		else
		{
			idxKeep[count] = 0;
		}
	}

	return count;
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

int GetKeepedDiceX(int idx)
{
	switch (idx)
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

int GetRolledDiceX(int count, int idx)
{
	switch (count)
	{
	case 1:
		return KEEPED_DICE_3_X;
	case 2:
		switch (idx)
		{
		case 0:
			return ROLLED_DICE_2_X;
		case 1:
			return ROLLED_DICE_3_X;
		}
	case 3:
		switch (idx)
		{
		case 0:
			return KEEPED_DICE_2_X;
		case 1:
			return KEEPED_DICE_3_X;
		case 2:
			return KEEPED_DICE_4_X;
		}
	case 4:
		switch (idx)
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
		return GetKeepedDiceX(idx);
	}
}

void ToggleTempPoints()
{
	if (player == 1)
	{
		for (int i = 1; i < SCOREBOARD_ITEM_COUNT; i++)
		{
			if (point[i]->isUsedP1 == 0)
			{
				point[i]->isUsedP1++;
			}
			else if (point[i]->isUsedP1 == 1)
			{
				point[i]->isUsedP1--;
			}
			else;
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
			else if (point[i]->isUsedP2 == 1)
			{
				point[i]->isUsedP2--;
			}
			else;
		}
	}
}

void ResetRound()
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
	if (turn <= MAX_NUMBER_OF_TURNS)
	{
		PrintRoundInfo();
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

int GetChooseCategoryY(int i)
{
	switch (i)
	{
	case ACES:
		return ACES_Y;
	case DEUCES:
		return DEUCES_Y;
	case THREES:
		return THREES_Y;
	case FOURS:
		return FOURS_Y;
	case FIVES:
		return FIVES_Y;
	case SIXES:
		return SIXES_Y;
	case CHOICE:
		return CHOICE_Y;
	case FOUR_OF_A_KIND:
		return FOUR_OF_A_KIND_Y;
	case FULL_HOUSE:
		return FULL_HOUSE_Y;
	case SMALL_STRAIGHT:
		return SMALL_STRAIGHT_Y;
	case LARGE_STRAIGHT:
		return LARGE_STRAIGHT_Y;
	case YACHT:
		return YACHT_Y;
	}
}