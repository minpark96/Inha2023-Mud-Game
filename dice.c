#include "main.h"

void ShakeDice()
{
	for (int count = 0; count < ROLL_EFFECT_COUNT; count++) 
	{
		if (rollCount == 0)
		{
			for (int idx = 0; idx < NUMBER_OF_DICE; idx++)
			{
				rolledDice[idx] = rand() % 6 + 1;
			}
		}
		else
		{
			for (int idx = 0; idx < NUMBER_OF_DICE; idx++)
			{
				if (rolledDice[idx] != NULL_VALUE_IN_ROLLED_DICE)
					rolledDice[idx] = rand() % 6 + 1;
			}
		}

		Sort(&rolledDice);
		Sleep(ROLL_DELAY);
		PrintUI();
	}
}

void RollDice()
{
	ShakeDice();
	if (rollCount == 0)
		ToggleTempPoints();

	rollCount++;

	if (rollCount == MAX_NUMBER_OF_ROLLS)
		KeepAllDice();

	SetFinalDice();
	SetScoreboard();
	PrintUI();
}

void SetFinalDice()
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

void KeepDice(int idx)
{
	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (keepedDice[i] == 0)
		{
			keepedDice[i] = rolledDice[idx];
			rolledDice[idx] = NULL_VALUE_IN_ROLLED_DICE;
			break;
		}
	}

	Sort(&rolledDice);
}

void DiscardDice(int idx)
{
	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (rolledDice[i] == NULL_VALUE_IN_ROLLED_DICE)
		{
			rolledDice[i] = keepedDice[idx];
			keepedDice[idx] = 0;
			break;
		}
	}

	Sort(&rolledDice);
}

void KeepAllDice()
{
	int idx = 0;

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (keepedDice[i] == 0)
		{
			keepedDice[i] = rolledDice[idx];
			rolledDice[idx] = NULL_VALUE_IN_ROLLED_DICE;
			idx++;
		}
	}
}