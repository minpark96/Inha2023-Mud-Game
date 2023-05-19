#include "main.h"

Score* aces, * deuces, * threes, * fours, * fives, * sixes, * bonus;
Score* choice, * fourOfAKind, * fullHouse, * smallStraight, * largeStraight, * yacht;
int subTotalP1, subTotalP2, totalP1, totalP2;
int rolledDice[5];
int keepedDice[5];
int finalDice[5];
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
		InitScore();
		//InitDice();
		cls;
		ShowTurnAndPlayer(turn, player);
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
			else if (rollCount == 3)
			{
				if (GetAsyncKeyState(VK_RETURN))
				{
					// 점수판 고르기인데 못돌아감
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

void Keep()
{
	
	int POS = 0;
	int cntKeepedDice = 0;
	int cntRolledDice = 0;
	int idxKeepedDice[5] = { 0 };
	int idxRolledDice[5] = { 0 };

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
			else if (POS == 6) POS = cntKeepedDice + 5;
			else if (POS == 0);
			else POS -= 1;
		else if (GetAsyncKeyState(VK_RIGHT))
			if (POS == cntRolledDice) POS = 1;
			else if (POS == cntKeepedDice + 5) POS = 6;
			else if (POS == 0);
			else POS += 1;
		else if (GetAsyncKeyState(VK_UP))
			if (POS == 0 && cntRolledDice != 0) POS = 1;
			else if (POS == 0 && cntRolledDice == 0) POS = 6;
			else if (POS < 6 && cntKeepedDice != 0) POS = 6;
			else;
		else if (GetAsyncKeyState(VK_DOWN))
			if (POS > 5 && cntRolledDice != 0) POS = 1;
			else if (POS > 5 && cntRolledDice == 0) POS = 0;
			else if (POS > 0 && POS < 6) POS = 0;
			else;
		else if (GetAsyncKeyState(VK_RETURN))
		{
			if (POS > 0 && POS < 6)
			{
				Sleep(50);
				RollToKeep(idxRolledDice[POS - 1]);
				POS = 0;
			}
			else if (POS > 5)
			{
				Sleep(50);
				KeepToRoll(idxKeepedDice[POS - 6]);
				POS = 0;
			}
			else
			{
				Sleep(50);
				break;
			}
		}
		else;

		switch (POS)
		{
		case 0:
			PrintChooseButton(POS);
			break;
		case 1:
			PrintChooseButton(POS);
			break;
		case 2:
			PrintChooseButton(POS);
			break;
		case 3:
			PrintChooseButton(POS);
			break;
		case 4:
			PrintChooseButton(POS);
			break;
		case 5:
			PrintChooseButton(POS);
			break;
		case 6:
			PrintChooseButton(POS);
			break;
		case 7:
			PrintChooseButton(POS);
			break;
		case 8:
			PrintChooseButton(POS);
			break;
		case 9:
			PrintChooseButton(POS);
			break;
		case 10:
			PrintChooseButton(POS);
			break;
		}
		Sleep(100);
	}
}

void CountKeepAndRoll(int* cntKeep, int* cntRoll, int** idxKeep, int** idxRoll)
{
	*cntKeep = 0;
	*cntRoll = 0;

	for (int i = 0; i < 5; i++)
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
	for (int i = 0; i < 5; i++)
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
	for (int i = 0; i < 5; i++)
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
	else if (POS > 5)
	{
		gotoxy(33, 22); printf("Back");
		POSKeep = POS - 6;
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

	for (int i = 0; i < 5; i++)
	{
		if (keepedDice[i] != 0 && i == POSKeep)
		{
			SetColor(11);
			gotoxy(GetX(i) + 6, 10); printf("▲");
			SetColor(15);
		}
		else if (keepedDice[i] != 0)
		{
			gotoxy(GetX(i) + 6, 10); printf("▲");
		}
		else;

		if (rolledDice[i] != 0 && i == POSRoll)
		{
			SetColor(11);
			gotoxy(GetX(i) + 6, 20); printf("▲");
			SetColor(15);
		}
		else if (rolledDice[i] != 0)
		{
			gotoxy(GetX(i) + 6, 20); printf("▲");
		}
		else;
	}
}

void PrintKeepedDice(void)
{
	gotoxy(0, 2); printf("Keeped Dice");

	int x;
	int y = 3;

	for (int i = 0; i < 5; i++)
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

	for (int i = 0; i < 5; i++)
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

void ShowTurnAndPlayer(int turn, int player)
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
void InitScore()
{
	aces = (Score*)malloc(sizeof(Score));
	deuces = (Score*)malloc(sizeof(Score));
	threes = (Score*)malloc(sizeof(Score));
	fours = (Score*)malloc(sizeof(Score));
	fives = (Score*)malloc(sizeof(Score));
	sixes = (Score*)malloc(sizeof(Score));
	bonus = (Score*)malloc(sizeof(Score));
	choice = (Score*)malloc(sizeof(Score));
	fourOfAKind = (Score*)malloc(sizeof(Score));
	fullHouse = (Score*)malloc(sizeof(Score));
	smallStraight = (Score*)malloc(sizeof(Score));
	largeStraight = (Score*)malloc(sizeof(Score));
	yacht = (Score*)malloc(sizeof(Score));

	aces->scoreP1 = 0;
	aces->scoreP2 = 0;
	deuces->scoreP1 = 0;
	deuces->scoreP2 = 0;
	threes->scoreP1 = 0;
	threes->scoreP2 = 0;
	fours->scoreP1 = 0;
	fours->scoreP2 = 0;
	fives->scoreP1 = 0;
	fives->scoreP2 = 0;
	sixes->scoreP1 = 0;
	sixes->scoreP2 = 0;
	bonus->scoreP1 = 0;
	bonus->scoreP2 = 0;
	choice->scoreP1 = 0;
	choice->scoreP2 = 0;
	fourOfAKind->scoreP1 = 0;
	fourOfAKind->scoreP2 = 0;
	fullHouse->scoreP1 = 0;
	fullHouse->scoreP2 = 0;
	smallStraight->scoreP1 = 0;
	smallStraight->scoreP2 = 0;
	largeStraight->scoreP1 = 0;
	largeStraight->scoreP2 = 0;
	yacht->scoreP1 = 0;
	yacht->scoreP2 = 0;

	aces->isUsedP1 = 0;
	aces->isUsedP2 = 0;
	deuces->isUsedP1 = 0;
	deuces->isUsedP2 = 0;
	threes->isUsedP1 = 0;
	threes->isUsedP2 = 0;
	fours->isUsedP1 = 0;
	fours->isUsedP2 = 0;
	fives->isUsedP1 = 0;
	fives->isUsedP2 = 0;
	sixes->isUsedP1 = 0;
	sixes->isUsedP2 = 0;
	bonus->isUsedP1 = 0;
	bonus->isUsedP2 = 0;
	choice->isUsedP1 = 0;
	choice->isUsedP2 = 0;
	fourOfAKind->isUsedP1 = 0;
	fourOfAKind->isUsedP2 = 0;
	fullHouse->isUsedP1 = 0;
	fullHouse->isUsedP2 = 0;
	smallStraight->isUsedP1 = 0;
	smallStraight->isUsedP2 = 0;
	largeStraight->isUsedP1 = 0;
	largeStraight->isUsedP2 = 0;
	yacht->isUsedP1 = 0;
	yacht->isUsedP2 = 0;
}

// 주사위 굴리기
void RollTheDice(int* rollCount)
{
	if (*rollCount == 0)
	{
		for (int idx = 0; idx < 5; idx++)
		{
			rolledDice[idx] = rand() % 6 + 1;
		}
		(*rollCount)++;
	}
	else
	{
		for (int idx = 0; idx < 5; idx++)
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
	puts("■     Turn     ■          ■          ■");
	printf("■    %2d/12     ■ Player 1 ■ Player 2 ■\n", turn);
	printf("■ Categories   ■          ■          ■\n");
	puts("■■■■■■■■■■■■■■■■■■■■■");

	if (aces->isUsedP1 && aces->isUsedP2)
		printf("■ Aces         ■     %d    ■     %d    ■\n", aces->scoreP1, aces->scoreP2);
	else if(aces->isUsedP1)
		printf("■ Aces         ■     %d    ■          ■\n", aces->scoreP1);
	else if(aces->isUsedP2)
		printf("■ Aces         ■          ■     %d    ■\n", aces->scoreP2);
	else
		printf("■ Aces         ■          ■          ■\n");

	if (deuces->isUsedP1 && deuces->isUsedP2)
		printf("■ Deuces       ■    %2d    ■    %2d    ■\n", deuces->scoreP1, deuces->scoreP2);
	else if (deuces->isUsedP1)
		printf("■ Deuces       ■    %2d    ■          ■\n", deuces->scoreP1);
	else if (deuces->isUsedP2)
		printf("■ Deuces       ■          ■    %2d    ■\n", deuces->scoreP2);
	else
		printf("■ Deuces       ■          ■          ■\n");
	
	if (threes->isUsedP1 && threes->isUsedP2)
		printf("■ Threes       ■    %2d    ■    %2d    ■\n", threes->scoreP1, threes->scoreP2);
	else if (threes->isUsedP1)
		printf("■ Threes       ■    %2d    ■          ■\n", threes->scoreP1);
	else if (threes->isUsedP2)
		printf("■ Threes       ■          ■    %2d    ■\n", threes->scoreP2);
	else
		printf("■ Threes       ■          ■          ■\n");

	if (fours->isUsedP1 && fours->isUsedP2)
		printf("■ Fours        ■    %2d    ■    %2d    ■\n", fours->scoreP1, fours->scoreP2);
	else if (fours->isUsedP1)
		printf("■ Fours        ■    %2d    ■          ■\n", fours->scoreP1);
	else if (fours->isUsedP2)
		printf("■ Fours        ■          ■    %2d    ■\n", fours->scoreP2);
	else
		printf("■ Fours        ■          ■          ■\n");

	if (fives->isUsedP1 && fives->isUsedP2)
		printf("■ Fives        ■    %2d    ■    %2d    ■\n", fives->scoreP1, fives->scoreP2);
	else if (fives->isUsedP1)
		printf("■ Fives        ■    %2d    ■          ■\n", fives->scoreP1);
	else if (fives->isUsedP2)
		printf("■ Fives        ■          ■    %2d    ■\n", fives->scoreP2);
	else
		printf("■ Fives        ■          ■          ■\n");

	if (sixes->isUsedP1 && sixes->isUsedP2)
		printf("■ Sixes        ■    %2d    ■    %2d    ■\n", sixes->scoreP1, sixes->scoreP2);
	else if (sixes->isUsedP1)
		printf("■ Sixes        ■    %2d    ■          ■\n", sixes->scoreP1);
	else if (sixes->isUsedP2)
		printf("■ Sixes        ■          ■    %2d    ■\n", sixes->scoreP2);
	else
		printf("■ Sixes        ■          ■          ■\n");

	puts("■■■■■■■■■■■■■■■■■■■■■");

	printf("■ Subtotal     ■  %3d/63  ■  %3d/63  ■\n", subTotalP1, subTotalP2);
	
	if (bonus->isUsedP1 && bonus->isUsedP2)
		printf("■ +35 Bonus    ■   +%2d    ■   +%2d    ■\n", bonus->scoreP1, bonus->scoreP2);
	else if (bonus->isUsedP1)
		printf("■ +35 Bonus    ■   +%2d    ■          ■\n", bonus->scoreP1);
	else if (bonus->isUsedP2)
		printf("■ +35 Bonus    ■          ■   +%2d    ■\n", bonus->scoreP2);
	else
		printf("■ +35 Bonus    ■          ■          ■\n");

	puts("■■■■■■■■■■■■■■■■■■■■■");

	if (choice->isUsedP1 && choice->isUsedP2)
		printf("■ Choice       ■    %2d    ■    %2d    ■\n", choice->scoreP1, choice->scoreP2);
	else if (choice->isUsedP1)
		printf("■ Choice       ■    %2d    ■          ■\n", choice->scoreP1);
	else if (choice->isUsedP2)
		printf("■ Choice       ■          ■    %2d    ■\n", choice->scoreP2);
	else
		printf("■ Choice       ■          ■          ■\n");

	if (fourOfAKind->isUsedP1 && fourOfAKind->isUsedP2)
		printf("■ 4 of a Kind  ■    %2d    ■    %2d    ■\n", fourOfAKind->scoreP1, fourOfAKind->scoreP2);
	else if (fourOfAKind->isUsedP1)
		printf("■ 4 of a Kind  ■    %2d    ■          ■\n", fourOfAKind->scoreP1);
	else if (fourOfAKind->isUsedP2)
		printf("■ 4 of a Kind  ■          ■    %2d    ■\n", fourOfAKind->scoreP2);
	else
		printf("■ 4 of a Kind  ■          ■          ■\n");

	if (fullHouse->isUsedP1 && fullHouse->isUsedP2)
		printf("■ Full House   ■    %2d    ■    %2d    ■\n", fullHouse->scoreP1, fullHouse->scoreP2);
	else if (fullHouse->isUsedP1)
		printf("■ Full House   ■    %2d    ■          ■\n", fullHouse->scoreP1);
	else if (fullHouse->isUsedP2)
		printf("■ Full House   ■          ■    %2d    ■\n", fullHouse->scoreP2);
	else
		printf("■ Full House   ■          ■          ■\n");

	if (smallStraight->isUsedP1 && smallStraight->isUsedP2)
		printf("■ S. Straight  ■    %2d    ■    %2d    ■\n", smallStraight->scoreP1, smallStraight->scoreP2);
	else if (smallStraight->isUsedP1)
		printf("■ S. Straight  ■    %2d    ■          ■\n", smallStraight->scoreP1);
	else if (smallStraight->isUsedP2)
		printf("■ S. Straight  ■          ■    %2d    ■\n", smallStraight->scoreP2);
	else
		printf("■ S. Straight  ■          ■          ■\n");

	if (largeStraight->isUsedP1 && largeStraight->isUsedP2)
		printf("■ L. Straight  ■    %2d    ■    %2d    ■\n", largeStraight->scoreP1, largeStraight->scoreP2);
	else if (largeStraight->isUsedP1)
		printf("■ L. Straight  ■    %2d    ■          ■\n", largeStraight->scoreP1);
	else if (largeStraight->isUsedP2)
		printf("■ L. Straight  ■          ■    %2d    ■\n", largeStraight->scoreP2);
	else
		printf("■ L. Straight  ■          ■          ■\n");

	if (yacht->isUsedP1 && yacht->isUsedP2)
		printf("■ Yacht        ■    %2d    ■    %2d    ■\n", yacht->scoreP1, yacht->scoreP2);
	else if (yacht->isUsedP1)
		printf("■ Yacht        ■    %2d    ■          ■\n", yacht->scoreP1);
	else if (yacht->isUsedP2)
		printf("■ Yacht        ■          ■    %2d    ■\n", yacht->scoreP2);
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

	for (int i = 0; i < 5; i++)
	{
		if (finalDice[i] == 1)
		{
			sum += 1;
		}
	}

	if (player == 1)
	{
		aces->scoreP1 = sum;
	}
	else
	{
		aces->scoreP2 = sum;
	}
}

void SetDeuces()
{
	int sum = 0;

	for (int i = 0; i < 5; i++)
	{
		if (finalDice[i] == 2)
		{
			sum += 2;
		}
	}

	if (player == 1)
	{
		deuces->scoreP1 = sum;
	}
	else
	{
		deuces->scoreP2 = sum;
	}
}

void SetThrees()
{
	int sum = 0;

	for (int i = 0; i < 5; i++)
	{
		if (finalDice[i] == 3)
		{
			sum += 3;
		}
	}

	if (player == 1)
	{
		threes->scoreP1 = sum;
	}
	else
	{
		threes->scoreP2 = sum;
	}
}

void SetFours()
{
	int sum = 0;

	for (int i = 0; i < 5; i++)
	{
		if (finalDice[i] == 4)
		{
			sum += 4;
		}
	}

	if (player == 1)
	{
		fours->scoreP1 = sum;
	}
	else
	{
		fours->scoreP2 = sum;
	}
}

void SetFives()
{
	int sum = 0;

	for (int i = 0; i < 5; i++)
	{
		if (finalDice[i] == 5)
		{
			sum += 5;
		}
	}

	if (player == 1)
	{
		fives->scoreP1 = sum;
	}
	else
	{
		fives->scoreP2 = sum;
	}
}

void SetSixes()
{
	int sum = 0;

	for (int i = 0; i < 5; i++)
	{
		if (finalDice[i] == 6)
		{
			sum += 6;
		}
	}

	if (player == 1)
	{
		sixes->scoreP1 = sum;
	}
	else
	{
		sixes->scoreP2 = sum;
	}
}

void SetChoice()
{
	int sum = 0;

	for (int i = 0; i < 5; i++)
	{
		sum += finalDice[i];
	}

	if (player == 1)
	{
		choice->scoreP1 = sum;
	}
	else
	{
		choice->scoreP2 = sum;
	}
}

void SetFourOfAKind()
{
	// 오름차순 정렬
	int min;
	int temp;
	int idx;

	for (int i = 0; i < 5; i++)
	{
		min = INT_MAX;

		for (int j = i; j < 5; j++)
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

		for (int i = 0; i < 5; i++)
		{
			sum += finalDice[i];
		}

		if (player == 1)
		{
			fourOfAKind->scoreP1 = sum;
		}
		else
		{
			fourOfAKind->scoreP2 = sum;
		}
	}
	else
	{
		if (player == 1)
		{
			fourOfAKind->scoreP1 = 0;
		}
		else
		{
			fourOfAKind->scoreP2 = 0;
		}
	}
}

void SetFullHouse()
{
	// 오름차순 정렬
	int min;
	int temp;
	int idx;

	for (int i = 0; i < 5; i++)
	{
		min = INT_MAX;

		for (int j = i; j < 5; j++)
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

		for (int i = 0; i < 5; i++)
		{
			sum += finalDice[i];
		}

		if (player == 1)
		{
			fullHouse->scoreP1 = sum;
		}
		else
		{
			fullHouse->scoreP2 = sum;
		}
	}
	else
	{
		if (player == 1)
		{
			fullHouse->scoreP1 = 0;
		}
		else
		{
			fullHouse->scoreP2 = 0;
		}
	}
}

void SetSmallStraight()
{
	// 오름차순 정렬
	int min;
	int temp;
	int idx;

	for (int i = 0; i < 5; i++)
	{
		min = INT_MAX;

		for (int j = i; j < 5; j++)
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

	int isSmallStraight = 0;
	int countNum1 = 0;
	int countNum2 = 0;
	int countNum3 = 0;
	int countNum4 = 0;
	int countNum5 = 0;
	int countNum6 = 0;
	 
	for (int i = 0; i < 5; i++)
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
			smallStraight->scoreP1 = 15;
		}
		else
		{
			smallStraight->scoreP2 = 15;
		}
	}
	else
	{
		if (player == 1)
		{
			smallStraight->scoreP1 = 0;
		}
		else
		{
			smallStraight->scoreP2 = 0;
		}
	}
}

void SetLargeStraight()
{
	// 오름차순 정렬
	int min;
	int temp;
	int idx;

	for (int i = 0; i < 5; i++)
	{
		min = INT_MAX;

		for (int j = i; j < 5; j++)
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
			largeStraight->scoreP1 = 30;
		}
		else
		{
			largeStraight->scoreP2 = 30;
		}
	}
	else
	{
		if (player == 1)
		{
			largeStraight->scoreP1 = 0;
		}
		else
		{
			largeStraight->scoreP2 = 0;
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
			yacht->scoreP1 = 50;
		}
		else
		{
			yacht->scoreP2 = 50;
		}
	}
	else
	{
		if (player == 1)
		{
			yacht->scoreP1 = 0;
		}
		else
		{
			yacht->scoreP2 = 0;
		}
	}
}

// 보너스 여부 계산
void SetBonus()
{
	if (aces->isUsedP1 && aces->isUsedP2 && deuces->isUsedP1 && deuces->isUsedP2
		&& threes->isUsedP1 && threes->isUsedP2 && fours->isUsedP1 && fours->isUsedP2
		&& fives->isUsedP1 && fives->isUsedP2 && sixes->isUsedP1 && sixes->isUsedP2)
	{
		if (subTotalP1 >= 63 && subTotalP2 >= 63)
		{
			bonus->scoreP1 = 35;
			bonus->scoreP2 = 35;
			bonus->isUsedP1 = 1;
			bonus->isUsedP2 = 1;
		}
		else if (subTotalP1 >= 63)
		{
			bonus->scoreP1 = 35;
			bonus->scoreP2 = 0;
			bonus->isUsedP1 = 1;
			bonus->isUsedP2 = 1;
		}
		else if (subTotalP2 >= 63)
		{
			bonus->scoreP1 = 0;
			bonus->scoreP2 = 35;
			bonus->isUsedP1 = 1;
			bonus->isUsedP2 = 1;
		}
		else
		{
			bonus->scoreP1 = 0;
			bonus->scoreP2 = 0;
			bonus->isUsedP1 = 1;
			bonus->isUsedP2 = 1;
		}
	}
	else if (aces->isUsedP1 && deuces->isUsedP1 && threes->isUsedP1 && fours->isUsedP1 && fives->isUsedP1 && sixes->isUsedP1)
	{
		if (subTotalP1 >= 63)
		{
			bonus->scoreP1 = 35;
			bonus->isUsedP1 = 1;
		}
		else
		{
			bonus->scoreP1 = 0;
			bonus->isUsedP1 = 1;
		}
	}
	else if (aces->isUsedP2 && deuces->isUsedP2 && threes->isUsedP2 && fours->isUsedP2 && fives->isUsedP2 && sixes->isUsedP2)
	{
		if (subTotalP2 >= 63)
		{
			bonus->scoreP2 = 35;
			bonus->isUsedP2 = 1;
		}
		else
		{
			bonus->scoreP2 = 0;
			bonus->isUsedP2 = 1;
		}
	}
	else
		return;
}

// 주사위 고정하기
