#include "main.h"

void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void InitBuffer()
{
	// init buffer
	for (int j = 0; j < SCR_HEIGHT; j++)
	{
		for (int i = 0; i < SCR_WIDTH; i++)
		{
			frontBuffer[j][i] = '\0';
			backBuffer[j][i] = '\0';
		}
	}
}

void DrawToBackBuffer(const int i, const int j, char* image)
{
	int ix = 0;
	while (1)
	{
		if (image[ix] == '\0') break;

		backBuffer[j][i + ix] = image[ix];

		ix++;
	}
}

void Render()
{
	for (int j = 0; j < SCR_HEIGHT; j++)
	{
		for (int i = 0; i < SCR_WIDTH; i++)
		{
			if (backBuffer[j][i] != frontBuffer[j][i])
			{
				gotoxy(i, j);

				if (backBuffer[j][i] == '\0')
					printf("%c", ' ');
				else
					printf("%c", backBuffer[j][i]);
			}
		}
	}

	for (int j = 0; j < SCR_HEIGHT; j++)
	{
		for (int i = 0; i < SCR_WIDTH; i++)
		{
			frontBuffer[j][i] = backBuffer[j][i];
			backBuffer[j][i] = '\0';
		}
	}
}