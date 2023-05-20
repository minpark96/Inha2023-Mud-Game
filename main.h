#pragma once

#include <stdio.h>
#include <windows.h>
#include <stralign.h>
#include <stdlib.h>
#include <time.h>

#define pause system("pause > nul")
#define cls system("cls")

/*typedef struct
{
	int num;
	int isKeeped;
}Dice;*/

#define MAX_TURN_COUNT 12
#define MAX_ROLL_COUNT 3
#define NUMBER_OF_POINTS 13
#define NUMBER_OF_DICE 5

#define BONUS 0
#define ACES 1
#define DEUCES 2
#define THREES 3
#define FOURS 4
#define FIVES 5
#define SIXES 6
#define CHOICE 7
#define FOUR_OF_A_KIND 8
#define FULL_HOUSE 9
#define SMALL_STRAIGHT 10
#define LARGE_STRAIGHT 11
#define YACHT 12

typedef struct
{
	int pointP1;
	int pointP2;
	int isUsedP1;
	int isUsedP2;
} Point;

void SetColor(int color);
void CursorView(char show);
void gotoxy(int x, int y);
void RollTheDice(int* rollCount);
void PrintMenu(void);
void InitPoint();
void ChooseCategory();
void Sort();
void KeepAndRollToFinal();
void ShowTurnAndPlayer();
void ShowTempPoints();
void PrintKeepedDice(void);
void PrintRolledDice(void);
int GetX(int i);
void Keep();
void CountKeepAndRoll(int* cntKeep, int* cntRoll, int** idxKeep, int** idxRoll);
void RollToKeep(int idx);
void KeepToRoll(int idx);
void PrintChooseButton(int POS);
void PrintNull(int x, int y);
void PrintDiceOne(int x, int y);
void PrintDiceTwo(int x, int y);
void PrintDiceThree(int x, int y);
void PrintDiceFour(int x, int y);
void PrintDiceFive(int x, int y);
void PrintDiceSix(int x, int y);
void PrintTable();
void SetTable();
void SetAces();
void SetDeuces();
void SetThrees();
void SetFours();
void SetFives();
void SetSixes();
void SetChoice();
void SetFourOfAKind();
void SetFullHouse();
void SetSmallStraight();
void SetLargeStraight();
void SetYacht();
void SetBonus();