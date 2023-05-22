#include "main.h"

extern int turn;
extern int player;
extern int rollCount;

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
					SetAcesToSixes(i);
				}
				else if (i == CHOICE)
					SetChoice();
				else if (i == FOUR_OF_A_KIND)
					SetFourOfAKind();
				else if (i == FULL_HOUSE)
					SetFullHouse();
				else if (i == SMALL_STRAIGHT)
					SetSmallStraight();
				else if (i == LARGE_STRAIGHT)
					SetLargeStraight();
				else
					SetYacht();
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
					SetAcesToSixes(i);
				}
				else if (i == CHOICE)
					SetChoice();
				else if (i == FOUR_OF_A_KIND)
					SetFourOfAKind();
				else if (i == FULL_HOUSE)
					SetFullHouse();
				else if (i == SMALL_STRAIGHT)
					SetSmallStraight();
				else if (i == LARGE_STRAIGHT)
					SetLargeStraight();
				else
					SetYacht();
			}
		}
	}
}

void SetAcesToSixes(int num)
{
	int sum = 0;

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (finalDice[i] == num)
		{
			sum += num;
		}
	}

	if (player == 1)
	{
		point[num]->pointP1 = sum;
	}
	else
	{
		point[num]->pointP2 = sum;
	}
}

void SetChoice()
{
	int sum = 0;

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		sum += finalDice[i];
	}

	if (player == 1)
	{
		point[CHOICE]->pointP1 = sum;
	}
	else
	{
		point[CHOICE]->pointP2 = sum;
	}
}

void SetFourOfAKind()
{
	int isFourOfAKind = 1;

	if (finalDice[0] == finalDice[1])
	{
		for (int i = 1; i < 3; i++)
		{
			if (finalDice[i] != finalDice[i + 1])
			{
				isFourOfAKind = 0;
				break;
			}
		}
	}
	else if (finalDice[1] == finalDice[2])
	{
		for (int i = 2; i < 4; i++)
		{
			if (finalDice[i] != finalDice[i + 1])
			{
				isFourOfAKind = 0;
				break;
			}
		}
	}
	else
	{
		isFourOfAKind = 0;
	}

	if (isFourOfAKind)
	{
		int sum = 0;

		for (int i = 0; i < NUMBER_OF_DICE; i++)
		{
			sum += finalDice[i];
		}

		if (player == 1)
		{
			point[FOUR_OF_A_KIND]->pointP1 = sum;
		}
		else
		{
			point[FOUR_OF_A_KIND]->pointP2 = sum;
		}
	}
	else
	{
		if (player == 1)
		{
			point[FOUR_OF_A_KIND]->pointP1 = 0;
		}
		else
		{
			point[FOUR_OF_A_KIND]->pointP2 = 0;
		}
	}
}

void SetFullHouse()
{
	int isFullHouse = 0;

	if (finalDice[0] == finalDice[1])
	{
		if (finalDice[1] == finalDice[2])
		{
			if (finalDice[3] == finalDice[4])
			{
				isFullHouse = 1;
			}
		}
		else
		{
			if (finalDice[2] == finalDice[3])
			{
				if (finalDice[3] == finalDice[4])
				{
					isFullHouse = 1;
				}
			}
		}
	}

	if (isFullHouse)
	{
		int sum = 0;

		for (int i = 0; i < NUMBER_OF_DICE; i++)
		{
			sum += finalDice[i];
		}

		if (player == 1)
		{
			point[FULL_HOUSE]->pointP1 = sum;
		}
		else
		{
			point[FULL_HOUSE]->pointP2 = sum;
		}
	}
	else
	{
		if (player == 1)
		{
			point[FULL_HOUSE]->pointP1 = 0;
		}
		else
		{
			point[FULL_HOUSE]->pointP2 = 0;
		}
	}
}

void SetSmallStraight()
{
	int isSmallStraight = 0;
	int countNum1 = 0;
	int countNum2 = 0;
	int countNum3 = 0;
	int countNum4 = 0;
	int countNum5 = 0;
	int countNum6 = 0;

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		switch (finalDice[i])
		{
		case 1:
			countNum1++;
			break;
		case 2:
			countNum2++;
			break;
		case 3:
			countNum3++;
			break;
		case 4:
			countNum4++;
			break;
		case 5:
			countNum5++;
			break;
		case 6:
			countNum6++;
			break;
		}
	}

	if ((countNum1 > 0) && (countNum2 > 0) && (countNum3 > 0) && (countNum4 > 0))
	{
		isSmallStraight = 1;
	}
	else if ((countNum2 > 0) && (countNum3 > 0) && (countNum4 > 0) && (countNum5 > 0))
	{
		isSmallStraight = 1;
	}
	else if ((countNum3 > 0) && (countNum4 > 0) && (countNum5 > 0) && (countNum6 > 0))
	{
		isSmallStraight = 1;
	}
	else
		;

	if (isSmallStraight)
	{
		if (player == 1)
		{
			point[SMALL_STRAIGHT]->pointP1 = 15;
		}
		else
		{
			point[SMALL_STRAIGHT]->pointP2 = 15;
		}
	}
	else
	{
		if (player == 1)
		{
			point[SMALL_STRAIGHT]->pointP1 = 0;
		}
		else
		{
			point[SMALL_STRAIGHT]->pointP2 = 0;
		}
	}
}

void SetLargeStraight()
{
	int isLargeStraight = 1;

	for (int i = 0; i < 4; i++)
	{
		if (finalDice[i] + 1 != finalDice[i + 1])
		{
			isLargeStraight = 0;
			break;
		}
	}

	if (isLargeStraight)
	{
		if (player == 1)
		{
			point[LARGE_STRAIGHT]->pointP1 = 30;
		}
		else
		{
			point[LARGE_STRAIGHT]->pointP2 = 30;
		}
	}
	else
	{
		if (player == 1)
		{
			point[LARGE_STRAIGHT]->pointP1 = 0;
		}
		else
		{
			point[LARGE_STRAIGHT]->pointP2 = 0;
		}
	}
}

void SetYacht()
{
	int isYacht = 1;

	for (int i = 0; i < 4; i++)
	{
		if (finalDice[i] != finalDice[i + 1])
		{
			isYacht = 0;
			break;
		}
	}

	if (isYacht)
	{
		if (player == 1)
		{
			point[YACHT]->pointP1 = 50;
		}
		else
		{
			point[YACHT]->pointP2 = 50;
		}
	}
	else
	{
		if (player == 1)
		{
			point[YACHT]->pointP1 = 0;
		}
		else
		{
			point[YACHT]->pointP2 = 0;
		}
	}
}

void SetBonus()
{
	int sum = 0;
	if (player == 1)
	{
		for (int i = ACES; i < CHOICE; i++)
		{
			sum += point[i]->pointP1;
		}
		if (sum >= 63)
		{
			point[BONUS]->pointP1 = 35;
			point[BONUS]->isUsedP1 = 2;
		}
		else
		{
			point[BONUS]->pointP1 = 0;
			point[BONUS]->isUsedP1 = 2;
		}
	}
	else
	{
		for (int i = ACES; i < CHOICE; i++)
		{
			sum += point[i]->pointP2;
		}
		if (sum >= 63)
		{
			point[BONUS]->pointP2 = 35;
			point[BONUS]->isUsedP2 = 2;
		}
		else
		{
			point[BONUS]->pointP2 = 0;
			point[BONUS]->isUsedP2 = 2;
		}

	}

}