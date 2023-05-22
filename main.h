#pragma once

#include <stdio.h>
#include <windows.h>
#include <stralign.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define cls system("cls")

#pragma region 컬러
#define DARK_YELLOW 6
#define GRAY 8
#define LIGHT_GREEN 10
#define SKY_BLUE 11
#define BRIGHT_WHITE 15
#define BACKGROUND_LIGHT_GREEN 175
#pragma endregion

#pragma region 게임 기본 항목
#define NUMBER_OF_DICE 5
#define SCOREBOARD_ITEM_COUNT 13
#define MAX_NUMBER_OF_TURNS 12
#define MAX_NUMBER_OF_ROLLS 3
#define NULL_VALUE_IN_ROLLED_DICE 7
#define BUTTON_DELAY 200
#define SELECT_DELAY 100
#pragma endregion

#pragma region 점수판 항목 인덱스
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
#pragma endregion

#pragma region 좌표값
#define PLAY_X 33
#define PLAY_Y 11
#define QUIT_X 58
#define QUIT_Y 11
#define ROUND_X 40
#define ROUND_Y 7
#define PLAYER_X 3
#define PLAYER_Y 1
#define ROLL_COUNT_X 69
#define ROLL_COUNT_Y 1
#define KEEPED_DICE_TITLE_X 37
#define KEEPED_DICE_TITLE_Y 3
#define KEEPED_DICE_1_X 5
#define KEEPED_DICE_2_X 20
#define KEEPED_DICE_3_X 35
#define KEEPED_DICE_4_X 50
#define KEEPED_DICE_5_X 65
#define KEEPED_DICE_Y 5
#define ROLLED_DICE_TITLE_X 37
#define ROLLED_DICE_TITLE_Y 15
#define ROLLED_DICE_1_X 13
#define ROLLED_DICE_2_X 28
#define ROLLED_DICE_3_X 43
#define ROLLED_DICE_4_X 58
#define ROLLED_DICE_Y 17
#define DISCARD_BUTTON_Y 13
#define KEEP_BUTTON_Y 25
#define RETURN_BUTTON_X 32
#define RETURN_BUTTON_Y 27
#pragma endregion


typedef struct
{
	int pointP1;
	int pointP2;
	int isUsedP1;
	int isUsedP2;
} Point;

Point* point[SCOREBOARD_ITEM_COUNT];
int subTotalP1, subTotalP2, totalP1, totalP2;
int rolledDice[NUMBER_OF_DICE];
int keepedDice[NUMBER_OF_DICE];
int finalDice[NUMBER_OF_DICE];

/*API.c*/
void SetColor(int color);
void CursorView(char show);
void gotoxy(int x, int y);
/*API.c*/

/*calculate.c*/
void SetScoreboard();
void SetAcesToSixes(int num);
void SetChoice();
void SetFourOfAKind();
void SetFullHouse();
void SetSmallStraight();
void SetLargeStraight();
void SetYacht();
void SetBonus();
/*calculate.c*/

/*choose_category.c*/
void ChooseCategory();
void SetPOSset(int** POSset);
void Reset();
void CountTotal(int POS);
void MovingOnTheScoreboard(int POS);
int GetY(int i);
/*choose_category.c*/

/*init.c*/
void Init();
/*init.c*/

/*keep_and_discard.c*/
void KeepAndDiscard();
void CountKeepAndRoll(int* cntKeep, int* cntRoll, int** idxKeep, int** idxRoll);
void Keep(int idx);
void Discard(int idx);

/*keep_and_discard.c*/

/*print.c*/
void PrintMainMenu(void);
void ShowTurnAndPlayer();
void PrintKeepedDice(void);
int GetKeepedDiceX(int i);
void PrintRolledDice(void);
int GetRolledDiceX(int count, int i);
void PrintChooseButton(int POS, int count);
void ShowTempPoints();
void HideTempPoints();
void PrintDiceOne(int x, int y);
void PrintDiceTwo(int x, int y);
void PrintDiceThree(int x, int y);
void PrintDiceFour(int x, int y);
void PrintDiceFive(int x, int y);
void PrintDiceSix(int x, int y);
void PrintNull(int x, int y);
void PrintScoreboard();
void PrintLine(int num);
/*print.c*/

/*roll.c*/
void ShakeTheDice(int* rollCount);
void RollTheDice(int* rollCount);
void Sort(int** Dice);
void KeepAndRollToFinal();
/*roll.c*/

/*yacht.c*/
void Start();
void PlayGame(int POS);
int CountRolledDice();
/*yacht.c*/

//void KeepAll();




















