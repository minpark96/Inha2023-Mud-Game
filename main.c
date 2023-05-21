#include "main.h"

Point* point[NUMBER_OF_POINTS];
int subTotalP1, subTotalP2, totalP1, totalP2;
int rolledDice[NUMBER_OF_DICE];
int keepedDice[NUMBER_OF_DICE];
int finalDice[NUMBER_OF_DICE];
int turn = 1;
int player = 1;
int rollCount = 0;

int main(void)
{
	int POS = 0;
	srand(time(0));
	CursorView(0);
	system("COLOR 0F");
	PrintMenu();
	while (1)
	{
		if (GetAsyncKeyState(VK_LEFT))
			if (POS == 0) POS = 1;
			else POS -= 1;
		else if (GetAsyncKeyState(VK_RIGHT))
			if (POS == 1) POS = 0;
			else POS += 1;
		else if (GetAsyncKeyState(VK_RETURN))
			break;
		else;

		switch (POS) 
		{
			case 0:
				SetColor(11);
				gotoxy(35, 4); printf("게임 플레이");
				SetColor(15);
				gotoxy(60, 4); printf("게임  종료");
				break;
			case 1:
				gotoxy(35, 4); printf("게임 플레이");
				SetColor(11);
				gotoxy(60, 4); printf("게임  종료");
				SetColor(15);
				break;
		default: break;
		}
		Sleep(100);
	}
	
	if (POS == 0)
	{
		// 구조체 변수 초기화
		InitPoints();
		//InitDice();
		cls;
		ShowTurnAndPlayer();
		Sleep(1000);
		system("mode con: cols=70 lines=48");
		while (1)
		{
			cls;
			gotoxy(0, 0); printf("Player%d\n", player);
			gotoxy(58, 0); printf("Roll: %d left\n", 3 - rollCount);
			PrintKeepedDice();
			PrintRolledDice();
			PrintTable();
			if (rollCount == 0)
			{
				if (GetAsyncKeyState(VK_RETURN))
				{
					RollTheDice(&rollCount);
				}
				SetColor(11);
				gotoxy(33, 22); printf("Roll\n");
				SetColor(15);
			}
			else if (rollCount == MAX_ROLL_COUNT)
			{
				if (GetAsyncKeyState(VK_RETURN))
				{
					Sleep(50);
					ChooseCategory();
					// 점수판 고르기 (취소 불가능)
				}
				SetColor(11);
				gotoxy(28, 22); printf("Choose Category\n");
				SetColor(15);
			}
			else
			{
				if (GetAsyncKeyState(VK_LEFT))
					if (POS == 0) POS = 2;
					else POS -= 1;
				else if (GetAsyncKeyState(VK_RIGHT))
					if (POS == 2) POS = 0;
					else POS += 1;
				else if (GetAsyncKeyState(VK_RETURN))
				{
					if (POS == 0)
					{
						Sleep(50);
						ChooseCategory();
						// 점수판 고르기 (취소 가능)
					}
					else if (POS == 1)
					{
						Sleep(50);
						Keep();
					}
					else
					{
						Sleep(50);
						RollTheDice(&rollCount);
					}
				}
				else;

				switch (POS)
				{
					case 0:
						SetColor(11);
						gotoxy(3, 22); printf("Choose Category\n");
						SetColor(15);
						gotoxy(33, 22); printf("Keep\n");
						gotoxy(60, 22); printf("Reroll\n");
						break;
					case 1:
						gotoxy(3, 22); printf("Choose Category\n");
						SetColor(11);
						gotoxy(33, 22); printf("Keep\n");
						SetColor(15);
						gotoxy(60, 22); printf("Reroll\n");
						break;
					case 2:
						gotoxy(3, 22); printf("Choose Category\n");
						gotoxy(33, 22); printf("Keep\n");
						SetColor(11);
						gotoxy(60, 22); printf("Reroll\n");
						SetColor(15);
						break;
				}
			}
			Sleep(100);
		}
	}
	
	else puts("게임  종료를 눌렀습니다.");
	
	return 0;
}

void ChooseCategory()
{
	int POS = 0;

	KeepAndRollToFinal();
	SetTable();;
	ShowTempPoints();
	
	while (1)
	{
		cls;
		gotoxy(0, 0); printf("Player%d\n", player);
		gotoxy(58, 0); printf("Roll: %d left\n", MAX_ROLL_COUNT - rollCount);
		PrintKeepedDice();
		PrintRolledDice();
		PrintTable();



		Sleep(100);
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
		if (rolledDice[i] != 0)
		{
			finalDice[idx] = rolledDice[i];
			idx++;
		}
	}

	Sort();
}

void ShowTempPoints()
{
	if (player == 1)
	{
		for (int i = 1; i < NUMBER_OF_POINTS; i++)
		{
			if (point[i]->isUsedP1 == 0)
			{
				point[i]->isUsedP1++;
			}
		}
	}
	else
	{
		for (int i = 1; i < NUMBER_OF_POINTS; i++)
		{
			if (point[i]->isUsedP2 == 0)
			{
				point[i]->isUsedP2++;
			}
		}
	}
}

void Keep()
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
		PrintRolledDice();
		PrintTable();
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
				RollToKeep(idxRolledDice[POS - 1]);
				POS = 0;
			}
			else if (POS > NUMBER_OF_DICE)
			{
				Sleep(50);
				KeepToRoll(idxKeepedDice[POS - (NUMBER_OF_DICE + 1)]);
				POS = 0;
			}
			else
			{
				Sleep(50);
				break;
			}
		}
		else;
		
		PrintChooseButton(POS);
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

		if (rolledDice[i])
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

void RollToKeep(int idx)
{
	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (keepedDice[i] == 0)
		{
			keepedDice[i] = rolledDice[idx];
			rolledDice[idx] = 0;
		}
	}
}

void KeepToRoll(int idx)
{
	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (rolledDice[i] == 0)
		{
			rolledDice[i] = keepedDice[idx];
			keepedDice[idx] = 0;
		}
	}
}

void PrintChooseButton(int POS)
{
	int POSKeep = -1;
	int POSRoll = -1;

	if (POS == 0)
	{
		SetColor(11);
		gotoxy(33, 22); printf("Back");
		SetColor(15);
	}
	else if (POS > NUMBER_OF_DICE)
	{
		gotoxy(33, 22); printf("Back");
		POSKeep = POS - (NUMBER_OF_DICE + 1);
		for (int i = 0; i < POSKeep + 1; i++)
		{
			if (keepedDice[i] == 0)
			{
				POSKeep++;
			}
		}
	}
	else
	{
		gotoxy(33, 22); printf("Back");		
		POSRoll = POS - 1;
		for (int i = 0; i < POSRoll + 1; i++)
		{
			if (rolledDice[i] == 0)
			{
				POSRoll++;
			}
		}
	}

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (keepedDice[i] != 0 && i == POSKeep)
		{
			SetColor(11);
			gotoxy(GetX(i) + NUMBER_OF_DICE + 1, 10); printf("▲");
			SetColor(15);
		}
		else if (keepedDice[i] != 0)
		{
			gotoxy(GetX(i) + NUMBER_OF_DICE + 1, 10); printf("▲");
		}
		else;

		if (rolledDice[i] != 0 && i == POSRoll)
		{
			SetColor(11);
			gotoxy(GetX(i) + NUMBER_OF_DICE + 1, 20); printf("▲");
			SetColor(15);
		}
		else if (rolledDice[i] != 0)
		{
			gotoxy(GetX(i) + NUMBER_OF_DICE + 1, 20); printf("▲");
		}
		else;
	}
}

void PrintKeepedDice(void)
{
	gotoxy(0, 2); printf("Keeped Dice");

	int x;
	int y = 3;

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		x = GetX(i);

		switch (keepedDice[i])
		{
		case 1:
			PrintDiceOne(x, y);
			break;
		case 2:
			PrintDiceTwo(x, y);
			break;
		case 3:
			PrintDiceThree(x, y);
			break;
		case 4:
			PrintDiceFour(x, y);
			break;
		case 5:
			PrintDiceFive(x, y);
			break;
		case 6:
			PrintDiceSix(x, y);
			break;
		Default:
			PrintNull(x, y);
			break;
		}
	}
}

void PrintRolledDice(void)
{
	gotoxy(0, 12); printf("Rolled Dice");
	
	int x;
	int y = 13;

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		x = GetX(i);

		switch (rolledDice[i])
		{
		case 1:
			PrintDiceOne(x, y);
			break;
		case 2:
			PrintDiceTwo(x, y);
			break;
		case 3:
			PrintDiceThree(x, y);
			break;
		case 4:
			PrintDiceFour(x, y);
			break;
		case 5:
			PrintDiceFive(x, y);
			break;
		case 6:
			PrintDiceSix(x, y);
			break;
		Default:
			PrintNull(x, y);
			break;
		}
	}
}

int GetX(int i)
{
	switch (i)
	{
	case 0:
		return 0;
	case 1:
		return 14;
	case 2:
		return 28;
	case 3:
		return 42;
	case 4:
		return 56;
	}
}

void PrintNull(int x, int y)
{
	for (int i = 0; i < 7; i++)
	{
		gotoxy(x, y + i); printf("              \n");
	}
}

void PrintDiceOne(int x, int y)
{
	gotoxy(x, y); printf("■■■■■■■");
	gotoxy(x, y + 1); printf("■          ■\n");
	gotoxy(x, y + 2); printf("■          ■\n");
	gotoxy(x, y + 3); printf("■    ●    ■\n");
	gotoxy(x, y + 4); printf("■          ■\n");
	gotoxy(x, y + 5); printf("■          ■\n");
	gotoxy(x, y + 6); printf("■■■■■■■\n");
}

void PrintDiceTwo(int x, int y)
{
	gotoxy(x, y); printf("■■■■■■■");
	gotoxy(x, y + 1); printf("■          ■\n");
	gotoxy(x, y + 2); printf("■  ●      ■\n");
	gotoxy(x, y + 3); printf("■          ■\n");
	gotoxy(x, y + 4); printf("■      ●  ■\n");
	gotoxy(x, y + 5); printf("■          ■\n");
	gotoxy(x, y + 6); printf("■■■■■■■\n");
}

void PrintDiceThree(int x, int y)
{
	gotoxy(x, y); printf("■■■■■■■");
	gotoxy(x, y + 1); printf("■          ■\n");
	gotoxy(x, y + 2); printf("■  ●      ■\n");
	gotoxy(x, y + 3); printf("■    ●    ■\n");
	gotoxy(x, y + 4); printf("■      ●  ■\n");
	gotoxy(x, y + 5); printf("■          ■\n");
	gotoxy(x, y + 6); printf("■■■■■■■\n");
}

void PrintDiceFour(int x, int y)
{
	gotoxy(x, y); printf("■■■■■■■");
	gotoxy(x, y + 1); printf("■          ■\n");
	gotoxy(x, y + 2); printf("■  ●  ●  ■\n");
	gotoxy(x, y + 3); printf("■          ■\n");
	gotoxy(x, y + 4); printf("■  ●  ●  ■\n");
	gotoxy(x, y + 5); printf("■          ■\n");
	gotoxy(x, y + 6); printf("■■■■■■■\n");
}

void PrintDiceFive(int x, int y)
{
	gotoxy(x, y); printf("■■■■■■■");
	gotoxy(x, y + 1); printf("■          ■\n");
	gotoxy(x, y + 2); printf("■  ●  ●  ■\n");
	gotoxy(x, y + 3); printf("■    ●    ■\n");
	gotoxy(x, y + 4); printf("■  ●  ●  ■\n");
	gotoxy(x, y + 5); printf("■          ■\n");
	gotoxy(x, y + 6); printf("■■■■■■■\n");
}

void PrintDiceSix(int x, int y)
{
	gotoxy(x, y); printf("■■■■■■■");
	gotoxy(x, y + 1); printf("■          ■\n");
	gotoxy(x, y + 2); printf("■  ●  ●  ■\n");
	gotoxy(x, y + 3); printf("■  ●  ●  ■\n");
	gotoxy(x, y + 4); printf("■  ●  ●  ■\n");
	gotoxy(x, y + 5); printf("■          ■\n");
	gotoxy(x, y + 6); printf("■■■■■■■\n");
}

void PrintMenu(void)
{
	// 메인메뉴 출력
	system("mode con: cols=106 lines=9");

	system("title 요트 다이스 게임");
	puts("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	puts("■                                                                                                      ■");
	puts("■                                                                                                      ■");
	puts("■                                                                                                      ■");
	puts("■                                                                                                      ■");
	puts("■                                                                                                      ■");
	puts("■                                                                                                      ■");
	puts("■                                                                                                      ■");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(35, 4); printf("게임 플레이");
	gotoxy(60, 4); printf("게임  종료");
	return;
}

void ShowTurnAndPlayer()
{
	// 턴 보여주기
	system("mode con: cols=106 lines=9");

	puts("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	puts("■                                                                                                      ■");
	puts("■                                                                                                      ■");
	puts("■                                                                                                      ■");
	puts("■                                                                                                      ■");
	puts("■                                                                                                      ■");
	puts("■                                                                                                      ■");
	puts("■                                                                                                      ■");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(40, 4); printf("%2d번째 턴 - 플레이어 %d\n", turn, player);
	return;
}

// 점수 초기화
void InitPoints()
{
	for (int i = 0; i < NUMBER_OF_POINTS; i++)
	{
		point[i] = (Point*)malloc(sizeof(Point));
	}

	for (int i = 0; i < NUMBER_OF_POINTS; i++)
	{
		
		point[i]->pointP1 = 0;
		point[i]->pointP2 = 0;
		point[i]->isUsedP1 = 0;
		point[i]->isUsedP2 = 0;
	}
}

// 주사위 굴리기
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
			if (rolledDice[idx] != 0)
				rolledDice[idx] = rand() % 6 + 1;
		}
		(*rollCount)++;
	}


}

void PrintTable()
{
	gotoxy(0, 24); puts("■■■■■■■■■■■■■■■■■■■■■");
	puts("■     Turn\t■          ■          ■");
	printf("■    %2d/12\t■ Player 1 ■ Player 2 ■\n", 1);
	printf("■ Categories\t■          ■          ■\n");
	puts("■■■■■■■■■■■■■■■■■■■■■");

	if (point[ACES]->isUsedP1 && point[ACES]->isUsedP2)
		printf("■ %s\t■     %d    ■     %d    ■\n", "Aces", point[ACES]->pointP1, point[ACES]->pointP2);
	else if(point[ACES]->isUsedP1)
		printf("■ Aces         ■     %d    ■          ■\n", point[ACES]->pointP1);
	else if(point[ACES]->isUsedP2)
		printf("■ Aces         ■          ■     %d    ■\n", point[ACES]->pointP2);
	else
		printf("■ Aces         ■          ■          ■\n");

	if (point[DEUCES]->isUsedP1 && point[DEUCES]->isUsedP2)
		printf("■ Deuces       ■    %2d    ■    %2d    ■\n", point[DEUCES]->pointP1, point[DEUCES]->pointP2);
	else if (point[DEUCES]->isUsedP1)
		printf("■ Deuces       ■    %2d    ■          ■\n", point[DEUCES]->pointP1);
	else if (point[DEUCES]->isUsedP2)
		printf("■ Deuces       ■          ■    %2d    ■\n", point[DEUCES]->pointP2);
	else
		printf("■ Deuces       ■          ■          ■\n");
	
	if (point[THREES]->isUsedP1 && point[THREES]->isUsedP2)
		printf("■ Threes       ■    %2d    ■    %2d    ■\n", point[THREES]->pointP1, point[THREES]->pointP2);
	else if (point[THREES]->isUsedP1)
		printf("■ Threes       ■    %2d    ■          ■\n", point[THREES]->pointP1);
	else if (point[THREES]->isUsedP2)
		printf("■ Threes       ■          ■    %2d    ■\n", point[THREES]->pointP2);
	else
		printf("■ Threes       ■          ■          ■\n");

	if (point[FOURS]->isUsedP1 && point[FOURS]->isUsedP2)
		printf("■ Fours        ■    %2d    ■    %2d    ■\n", point[FOURS]->pointP1, point[FOURS]->pointP2);
	else if (point[FOURS]->isUsedP1)
		printf("■ Fours        ■    %2d    ■          ■\n", point[FOURS]->pointP1);
	else if (point[FOURS]->isUsedP2)
		printf("■ Fours        ■          ■    %2d    ■\n", point[FOURS]->pointP2);
	else
		printf("■ Fours        ■          ■          ■\n");

	if (point[FIVES]->isUsedP1 && point[FIVES]->isUsedP2)
		printf("■ Fives        ■    %2d    ■    %2d    ■\n", point[FIVES]->pointP1, point[FIVES]->pointP2);
	else if (point[FIVES]->isUsedP1)
		printf("■ Fives        ■    %2d    ■          ■\n", point[FIVES]->pointP1);
	else if (point[FIVES]->isUsedP2)
		printf("■ Fives        ■          ■    %2d    ■\n", point[FIVES]->pointP2);
	else
		printf("■ Fives        ■          ■          ■\n");

	if (point[SIXES]->isUsedP1 && point[SIXES]->isUsedP2)
		printf("■ Sixes        ■    %2d    ■    %2d    ■\n", point[SIXES]->pointP1, point[SIXES]->pointP2);
	else if (point[SIXES]->isUsedP1)
		printf("■ Sixes        ■    %2d    ■          ■\n", point[SIXES]->pointP1);
	else if (point[SIXES]->isUsedP2)
		printf("■ Sixes        ■          ■    %2d    ■\n", point[SIXES]->pointP2);
	else
		printf("■ Sixes        ■          ■          ■\n");

	puts("■■■■■■■■■■■■■■■■■■■■■");

	printf("■ Subtotal     ■  %3d/63  ■  %3d/63  ■\n", subTotalP1, subTotalP2);
	
	if (point[BONUS]->isUsedP1 && point[BONUS]->isUsedP2)
		printf("■ +35 Bonus    ■   +%2d    ■   +%2d    ■\n", point[BONUS]->pointP1, point[BONUS]->pointP2);
	else if (point[BONUS]->isUsedP1)
		printf("■ +35 Bonus    ■   +%2d    ■          ■\n", point[BONUS]->pointP1);
	else if (point[BONUS]->isUsedP2)
		printf("■ +35 Bonus    ■          ■   +%2d    ■\n", point[BONUS]->pointP2);
	else
		printf("■ +35 Bonus    ■          ■          ■\n");

	puts("■■■■■■■■■■■■■■■■■■■■■");

	if (point[CHOICE]->isUsedP1 && point[CHOICE]->isUsedP2)
		printf("■ Choice       ■    %2d    ■    %2d    ■\n", point[CHOICE]->pointP1, point[CHOICE]->pointP2);
	else if (point[CHOICE]->isUsedP1)
		printf("■ Choice       ■    %2d    ■          ■\n", point[CHOICE]->pointP1);
	else if (point[CHOICE]->isUsedP2)
		printf("■ Choice       ■          ■    %2d    ■\n", point[CHOICE]->pointP2);
	else
		printf("■ Choice       ■          ■          ■\n");

	if (point[FOUR_OF_A_KIND]->isUsedP1 && point[FOUR_OF_A_KIND]->isUsedP2)
		printf("■ 4 of a Kind  ■    %2d    ■    %2d    ■\n", point[FOUR_OF_A_KIND]->pointP1, point[FOUR_OF_A_KIND]->pointP2);
	else if (point[FOUR_OF_A_KIND]->isUsedP1)
		printf("■ 4 of a Kind  ■    %2d    ■          ■\n", point[FOUR_OF_A_KIND]->pointP1);
	else if (point[FOUR_OF_A_KIND]->isUsedP2)
		printf("■ 4 of a Kind  ■          ■    %2d    ■\n", point[FOUR_OF_A_KIND]->pointP2);
	else
		printf("■ 4 of a Kind  ■          ■          ■\n");

	if (point[FULL_HOUSE]->isUsedP1 && point[FULL_HOUSE]->isUsedP2)
		printf("■ Full House   ■    %2d    ■    %2d    ■\n", point[FULL_HOUSE]->pointP1, point[FULL_HOUSE]->pointP2);
	else if (point[FULL_HOUSE]->isUsedP1)
		printf("■ Full House   ■    %2d    ■          ■\n", point[FULL_HOUSE]->pointP1);
	else if (point[FULL_HOUSE]->isUsedP2)
		printf("■ Full House   ■          ■    %2d    ■\n", point[FULL_HOUSE]->pointP2);
	else
		printf("■ Full House   ■          ■          ■\n");

	if (point[SMALL_STRAIGHT]->isUsedP1 && point[SMALL_STRAIGHT]->isUsedP2)
		printf("■ S. Straight  ■    %2d    ■    %2d    ■\n", point[SMALL_STRAIGHT]->pointP1, point[SMALL_STRAIGHT]->pointP2);
	else if (point[SMALL_STRAIGHT]->isUsedP1)
		printf("■ S. Straight  ■    %2d    ■          ■\n", point[SMALL_STRAIGHT]->pointP1);
	else if (point[SMALL_STRAIGHT]->isUsedP2)
		printf("■ S. Straight  ■          ■    %2d    ■\n", point[SMALL_STRAIGHT]->pointP2);
	else
		printf("■ S. Straight  ■          ■          ■\n");

	if (point[LARGE_STRAIGHT]->isUsedP1 && point[LARGE_STRAIGHT]->isUsedP2)
		printf("■ L. Straight  ■    %2d    ■    %2d    ■\n", point[LARGE_STRAIGHT]->pointP1, point[LARGE_STRAIGHT]->pointP2);
	else if (point[LARGE_STRAIGHT]->isUsedP1)
		printf("■ L. Straight  ■    %2d    ■          ■\n", point[LARGE_STRAIGHT]->pointP1);
	else if (point[LARGE_STRAIGHT]->isUsedP2)
		printf("■ L. Straight  ■          ■    %2d    ■\n", point[LARGE_STRAIGHT]->pointP2);
	else
		printf("■ L. Straight  ■          ■          ■\n");

	if (point[YACHT]->isUsedP1 && point[YACHT]->isUsedP2)
		printf("■ Yacht        ■    %2d    ■    %2d    ■\n", point[YACHT]->pointP1, point[YACHT]->pointP2);
	else if (point[YACHT]->isUsedP1)
		printf("■ Yacht        ■    %2d    ■          ■\n", point[YACHT]->pointP1);
	else if (point[YACHT]->isUsedP2)
		printf("■ Yacht        ■          ■    %2d    ■\n", point[YACHT]->pointP2);
	else
		printf("■ Yacht        ■          ■          ■\n");

	puts("■■■■■■■■■■■■■■■■■■■■■");

	printf("■ Total        ■   %3d    ■   %3d    ■\n", totalP1, totalP2);

	printf("■■■■■■■■■■■■■■■■■■■■■");
}

void SetTable()
{
	SetAces();
	SetDeuces();
	SetThrees();
	SetFours();
	SetFives();
	SetSixes();
	SetChoice();
	SetFourOfAKind();
	SetFullHouse();
	SetSmallStraight();
	SetLargeStraight();
	SetYacht();
}

void SetAces()
{
	int sum = 0;

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (finalDice[i] == 1)
		{
			sum += 1;
		}
	}

	if (player == 1)
	{
		point[ACES]->pointP1 = sum;
	}
	else
	{
		point[ACES]->pointP2 = sum;
	}
}

void SetDeuces()
{
	int sum = 0;

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (finalDice[i] == 2)
		{
			sum += 2;
		}
	}

	if (player == 1)
	{
		point[DEUCES]->pointP1 = sum;
	}
	else
	{
		point[DEUCES]->pointP2 = sum;
	}
}

void SetThrees()
{
	int sum = 0;

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (finalDice[i] == 3)
		{
			sum += 3;
		}
	}

	if (player == 1)
	{
		point[THREES]->pointP1 = sum;
	}
	else
	{
		point[THREES]->pointP2 = sum;
	}
}

void SetFours()
{
	int sum = 0;

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (finalDice[i] == 4)
		{
			sum += 4;
		}
	}

	if (player == 1)
	{
		point[FOURS]->pointP1 = sum;
	}
	else
	{
		point[FOURS]->pointP2 = sum;
	}
}

void SetFives()
{
	int sum = 0;

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (finalDice[i] == 5)
		{
			sum += 5;
		}
	}

	if (player == 1)
	{
		point[FIVES]->pointP1 = sum;
	}
	else
	{
		point[FIVES]->pointP2 = sum;
	}
}

void SetSixes()
{
	int sum = 0;

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		if (finalDice[i] == 6)
		{
			sum += 6;
		}
	}

	if (player == 1)
	{
		point[SIXES]->pointP1 = sum;
	}
	else
	{
		point[SIXES]->pointP2 = sum;
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

void Sort()
{
	// 오름차순 정렬
	int min;
	int temp;
	int idx;

	for (int i = 0; i < NUMBER_OF_DICE; i++)
	{
		min = INT_MAX;

		for (int j = i; j < NUMBER_OF_DICE; j++)
		{
			if (finalDice[j] < min)
			{
				min = finalDice[j];
				idx = j;
			}
		}
		temp = finalDice[i];
		finalDice[i] = min;
		finalDice[idx] = temp;
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

// 보너스 여부 계산
void SetBonus()
{
	if (point[ACES]->isUsedP1 && point[ACES]->isUsedP2 && point[DEUCES]->isUsedP1 && point[DEUCES]->isUsedP2
		&& point[THREES]->isUsedP1 && point[THREES]->isUsedP2 && point[FOURS]->isUsedP1 && point[FOURS]->isUsedP2
		&& point[FIVES]->isUsedP1 && point[FIVES]->isUsedP2 && point[SIXES]->isUsedP1 && point[SIXES]->isUsedP2)
	{
		if (subTotalP1 >= 63 && subTotalP2 >= 63)
		{
			point[BONUS]->pointP1 = 35;
			point[BONUS]->pointP2 = 35;
			point[BONUS]->isUsedP1 = 1;
			point[BONUS]->isUsedP2 = 1;
		}
		else if (subTotalP1 >= 63)
		{
			point[BONUS]->pointP1 = 35;
			point[BONUS]->pointP2 = 0;
			point[BONUS]->isUsedP1 = 1;
			point[BONUS]->isUsedP2 = 1;
		}
		else if (subTotalP2 >= 63)
		{
			point[BONUS]->pointP1 = 0;
			point[BONUS]->pointP2 = 35;
			point[BONUS]->isUsedP1 = 1;
			point[BONUS]->isUsedP2 = 1;
		}
		else
		{
			point[BONUS]->pointP1 = 0;
			point[BONUS]->pointP2 = 0;
			point[BONUS]->isUsedP1 = 1;
			point[BONUS]->isUsedP2 = 1;
		}
	}
	else if (point[ACES]->isUsedP1 && point[DEUCES]->isUsedP1 && point[THREES]->isUsedP1 && point[FOURS]->isUsedP1 && point[FIVES]->isUsedP1 && point[SIXES]->isUsedP1)
	{
		if (subTotalP1 >= 63)
		{
			point[BONUS]->pointP1 = 35;
			point[BONUS]->isUsedP1 = 1;
		}
		else
		{
			point[BONUS]->pointP1 = 0;
			point[BONUS]->isUsedP1 = 1;
		}
	}
	else if (point[ACES]->isUsedP2 && point[DEUCES]->isUsedP2 && point[THREES]->isUsedP2 && point[FOURS]->isUsedP2 && point[FIVES]->isUsedP2 && point[SIXES]->isUsedP2)
	{
		if (subTotalP2 >= 63)
		{
			point[BONUS]->pointP2 = 35;
			point[BONUS]->isUsedP2 = 1;
		}
		else
		{
			point[BONUS]->pointP2 = 0;
			point[BONUS]->isUsedP2 = 1;
		}
	}
	else
		return;
}
