#include "main.h"

extern int turn;
extern int player;
extern int rollCount;

void Init()
{
	for (int i = 0; i < SCOREBOARD_ITEM_COUNT; i++)
	{
		point[i] = (Point*)malloc(sizeof(Point));
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