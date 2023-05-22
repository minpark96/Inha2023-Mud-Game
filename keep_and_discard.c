#include "main.h"

extern int turn;
extern int player;
extern int rollCount;

void KeepAndDiscard()
{
	int POS = 0;
	int cntKeepedDice = 0;
	int cntRolledDice = 0;
	int idxKeepedDice[NUMBER_OF_DICE] = { 0 };
	int idxRolledDice[NUMBER_OF_DICE] = { 0 };

	while (1)
	{
		CountKeepAndRoll(&cntKeepedDice, &cntRolledDice, &idxKeepedDice, &idxRolledDice);
		cls;
		gotoxy(0, 0); printf("Player%d\n", player);
		gotoxy(58, 0); printf("Roll: %d left\n", 3 - rollCount);
		PrintKeepedDice();
		PrintRolledDice(cntRolledDice);
		PrintScoreboard();
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
				Sleep(50);
				Keep(idxRolledDice[POS - 1]);
				POS = 0;
			}
			else if (POS > NUMBER_OF_DICE)
			{
				Sleep(50);
				Discard(idxKeepedDice[POS - (NUMBER_OF_DICE + 1)]);
				POS = 0;
			}
			else
			{
				Sleep(50);
				break;
			}
		}
		else;

		PrintChooseButton(POS, cntRolledDice);
		Sleep(100);
	}
}

void CountKeepAndRoll(int* cntKeep, int* cntRoll, int** idxKeep, int** idxRoll)
{
	*cntKeep = 0;
	*cntRoll = 0;

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (keepedDice[i])
		{
			idxKeep[*cntKeep] = i;
			(*cntKeep)++;
		}
		else
		{
			idxKeep[*cntKeep] = 0;
		}

		if (rolledDice[i] != NULL_VALUE_IN_ROLLED_DICE)
		{
			idxRoll[*cntRoll] = i;
			(*cntRoll)++;
		}
		else
		{
			idxRoll[*cntRoll] = 0;
		}
	}
}

void Keep(int idx)
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

void Discard(int idx)
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

//void KeepAll()
//{
//	for (int i = 0; i < NUMBER_OF_DICE; i++)
//	{
//		if (keepedDice[i] == 0)
//		{
//			keepedDice[i] = rolledDice[idx];
//			rolledDice[idx] = 0;
//		}
//	}
//}