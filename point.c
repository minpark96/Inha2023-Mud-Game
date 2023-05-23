#include "main.h"

void CountAcesToSixes(int num)
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

void CountChoice()
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

void CountFourOfAKind()
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

void CountFullHouse()
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

void CountSmallStraight()
{
	int isSmallStraight = 0;
	int cntOneToSix[6] = { 0 };

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		switch (finalDice[i])
		{
		case 1:
			cntOneToSix[0]++;
			break;
		case 2:
			cntOneToSix[1]++;
			break;
		case 3:
			cntOneToSix[2]++;
			break;
		case 4:
			cntOneToSix[3]++;
			break;
		case 5:
			cntOneToSix[4]++;
			break;
		case 6:
			cntOneToSix[5]++;
			break;
		}
	}

	if ((cntOneToSix[0] > 0) && (cntOneToSix[1] > 0) && (cntOneToSix[2] > 0) && (cntOneToSix[3] > 0))
	{
		isSmallStraight = 1;
	}
	else if ((cntOneToSix[1] > 0) && (cntOneToSix[2] > 0) && (cntOneToSix[3] > 0) && (cntOneToSix[4] > 0))
	{
		isSmallStraight = 1;
	}
	else if ((cntOneToSix[2] > 0) && (cntOneToSix[3] > 0) && (cntOneToSix[4] > 0) && (cntOneToSix[5] > 0))
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

void CountLargeStraight()
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

void CountYacht()
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

void CountBonus()
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
			totalP1 += 35;
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
			totalP2 += 35;
		}
		else
		{
			point[BONUS]->pointP2 = 0;
			point[BONUS]->isUsedP2 = 2;
		}
	}
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
			CountBonus();
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
			CountBonus();
		}

		totalP2 += point[POS]->pointP2;
	}
}