#pragma once

#define _CRT_SECURE_NO_WARNINGS
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
#define SCR_WIDTH 137
#define SCR_HEIGHT 31

#define NUMBER_OF_DICE 5
#define SCOREBOARD_ITEM_COUNT 13
#define MAX_NUMBER_OF_TURNS 12
#define MAX_NUMBER_OF_ROLLS 3
#define NULL_VALUE_IN_ROLLED_DICE 7

#define BUTTON_DELAY 250
#define SELECT_DELAY 100
#define ROLL_DELAY 300
#define POPUP_DELAY 1500

#define ROLL_EFFECT_COUNT 5
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
/*MAIN TITLE*/
#define TITLE_X 35
#define TITLE_Y 7

/*ROUND INFO*/
#define ROUND_X 57
#define ROUND_Y 15

/*HEADER*/
#define PLAYER_X 55
#define PLAYER_Y 2
#define ROLL_COUNT_X 121
#define ROLL_COUNT_Y 2

/*DICE*/
#define KEEPED_DICE_TITLE_X 88
#define KEEPED_DICE_TITLE_Y 4

#define ROLLED_DICE_TITLE_X 88
#define ROLLED_DICE_TITLE_Y 16

#define KEEPED_DICE_1_X 55
#define KEEPED_DICE_2_X 71
#define KEEPED_DICE_3_X 87
#define KEEPED_DICE_4_X 103
#define KEEPED_DICE_5_X 119
#define KEEPED_DICE_Y 6

#define ROLLED_DICE_1_X 63
#define ROLLED_DICE_2_X 79
#define ROLLED_DICE_3_X 95
#define ROLLED_DICE_4_X 111
#define ROLLED_DICE_Y 18

/*SCOREBOARD*/
#define SCOREBOARD_X 4
#define SCOREBOARD_Y 2
#define GAME_OVER_X 48
#define GAME_OVER_Y 2

/*BUTTON*/
#define PLAY_BUTTON_X 50
#define PLAY_BUTTON_Y 22
#define QUIT_BUTTON_X 83
#define QUIT_BUTTON_Y 22

#define BUTTON_Y 28

#define DISCARD_BUTTON_Y 14
#define KEEP_BUTTON_Y 26

#define CORE_BUTTON_LEFT_X 57
#define CORE_BUTTON_MIDDLE_X 87
#define CORE_BUTTON_RIGHT_X 125

#define SHAKE_BUTTON_X 84
#define ROLL_BUTTON_X 99
#define RETURN_BUTTON_X 125

#define NEXT_X 126

#define ACES_Y 7
#define DEUCES_Y 8
#define THREES_Y 9
#define FOURS_Y 10
#define FIVES_Y 11
#define SIXES_Y 12
#define CHOICE_Y 19
#define FOUR_OF_A_KIND_Y 21
#define FULL_HOUSE_Y 22
#define SMALL_STRAIGHT_Y 23
#define LARGE_STRAIGHT_Y 24
#define YACHT_Y 25

#define PLAYER_1_X 22
#define PLAYER_2_X 34
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
int turn;
int player;
int rollCount;

char frontBuffer[SCR_HEIGHT][SCR_WIDTH];
char backBuffer[SCR_HEIGHT][SCR_WIDTH];

/*API.c*/
void SetColor(int color);
void CursorView(char show);
void gotoxy(int x, int y);
void InitBuffer();
void DrawToBackBuffer(const int i, const int j, char* image);
void Render();
/*API.c*/

/*button.c*/
void MoveMainMenuButton(int POS);
void MoveCoreButton(int POS);
void MoveShakeAndRollButton(int POS);
void MoveKeepAndDiscardButton(int POS, int count);
void MoveChooseCategoryButton(int POS);
/*button.c*/

/*point.c*/
void CountAcesToSixes(int num);
void CountChoice();
void CountFourOfAKind();
void CountFullHouse();
void CountSmallStraight();
void CountLargeStraight();
void CountYacht();
void CountBonus();
void CountTotal(int POS);
/*point.c*/

/*print.c*/
void PrintMainMenu(void);
void PrintRoundInfo();
void PrintKeepedDice(void);
void PrintRolledDice(void);
void PrintDiceOne(int x, int y);
void PrintDiceTwo(int x, int y);
void PrintDiceThree(int x, int y);
void PrintDiceFour(int x, int y);
void PrintDiceFive(int x, int y);
void PrintDiceSix(int x, int y);
void PrintDiceNull(int x, int y);
void PrintScoreboard();
void PrintPointElements(int num);
void PrintHeader();
void PrintUI();
/*print.c*/

/*dice.c*/
void ShakeDice();
void RollDice();
void SetFinalDice();
void KeepDice(int idx);
void DiscardDice(int idx);
void KeepAllDice();
/*dice.c*/

/*core.c*/
void Start();
void Play();
void ShakeAndRoll();
void KeepAndDiscard();
void ChooseCategory();
void GameOver();
/*core.c*/

/*util.c*/
void Init();
void SetScoreboard();
void Sort(int** Dice); 
int CountKeepedDice(int** idxKeep);
int CountRolledDice();
int GetKeepedDiceX(int i);
int GetRolledDiceX(int count, int i);
void ToggleTempPoints();
void ResetRound();
void SetPOSset(int** POSset);
int GetChooseCategoryY(int i);
/*util.c*/