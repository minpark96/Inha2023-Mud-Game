#include "main.h"

extern int turn;
extern int player;
extern int rollCount;

void ShakeTheDice(int* rollCount)
{
	if (*rollCount == 0)
	{
		for (int idx = 0; idx < NUMBER_OF_DICE; idx++)
		{
			rolledDice[idx] = rand() % 6 + 1;
		}
		(*rollCount)++;
	}
	else
	{
		for (int idx = 0; idx < NUMBER_OF_DICE; idx++)
		{
			if (rolledDice[idx] != NULL_VALUE_IN_ROLLED_DICE)
				rolledDice[idx] = rand() % 6 + 1;
		}
		(*rollCount)++;
	}

	Sort(&rolledDice);
}

void RollTheDice(int* rollCount)
{
	if (*rollCount == 0)
	{
		for (int idx = 0; idx < NUMBER_OF_DICE; idx++)
		{
			rolledDice[idx] = rand() % 6 + 1;
		}
		(*rollCount)++;
	}
	else
	{
		for (int idx = 0; idx < NUMBER_OF_DICE; idx++)
		{
			if (rolledDice[idx] != NULL_VALUE_IN_ROLLED_DICE)
				rolledDice[idx] = rand() % 6 + 1;
		}
		(*rollCount)++;
	}

	Sort(&rolledDice);
	KeepAndRollToFinal();
	SetScoreboard();
	ShowTempPoints();
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

void KeepAndRollToFinal()
{
	int idx = 0;

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (keepedDice[i] != 0)
		{
			finalDice[idx] = keepedDice[i];
			idx++;
		}
	}

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (rolledDice[i] != NULL_VALUE_IN_ROLLED_DICE)
		{
			finalDice[idx] = rolledDice[i];
			idx++;
		}
	}

	Sort(&finalDice);
}