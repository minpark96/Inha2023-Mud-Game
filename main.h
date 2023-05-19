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

typedef struct
{
	int scoreP1;
	int scoreP2;
	int isUsedP1;
	int isUsedP2;
} Score;

void SetColor(int color);
void CursorView(char show);
void gotoxy(int x, int y);
void RollTheDice(int* rollCount);
void PrintMenu(void);
void InitScore();
//void InitDice();
void ShowTurnAndPlayer(int turn, int player);
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