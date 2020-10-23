#include<stdio.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>
void draw_star(int x, int y);
void setcursor(bool visible);
void gotoxy(int x, int y);
void erase_ship(int x, int y);
void erase(int x, int y);
void draw_ship(int x, int y);
void setcolor(int fg, int bg);
void createbullet(int x, int y);
void erase_bullet(int x, int y);
void score(int x, int y);
char cursor(int x, int y);
void erase_star(int x, int y);
struct ans
{
	char ch = ' ';
	int x = 38, y = 23;
	int num[50];
	int bullet[5];
	int bulletx[5];
	int bullety[5];
	int star;
	int starx[20];
	int stary[20];
	int curser =0;
}t;

int main()
{
	int i;
	srand(time(NULL));
	for (t.star = 0; t.star < 20; t.star++)
	{
		t.starx[t.star] = rand() %100 ;
		t.stary[t.star] = rand() %5;
		t.stary[t.star] += 1;

		draw_star(t.starx[t.star], t.stary[t.star]);

	}
	draw_ship(t.x, t.y);
	setcursor(0);
	do
	{
		score(t.x, t.y);
		if (_kbhit())
		{
			t.ch = _getch();

			if (t.ch == 'w')
			{
				t.num[0] = 1;
			}
			if (t.ch == 's')
			{
				t.num[0] = 2;
			}
			if (t.ch == 'a')
			{
				t.num[0] = 3;
			}
			if (t.ch == 'd')
			{
				t.num[0] = 4;
			}
			if (t.ch == ' ')
			{
				for (int i = 0; i < 5; i++)
				{
					if (t.bullet[i] == 0)
					{
						
						t.bullet[i] = 1;
						t.bulletx[i] = t.x + 4;
						t.bullety[i] = t.y - 1;
						createbullet(t.bulletx[i], t.bullety[i]);
						Beep(700, 100);
						break;
					}
				}
			}

			fflush(stdin);
		}
		if (t.num[0] == 1)
		{
			draw_ship(t.x, t.y);

		}
		if (t.num[0] == 2)
		{
			draw_ship(t.x, t.y);
		}
		if (t.num[0] == 3 && t.x > 0)
		{
			erase_ship(t.x, t.y);
			draw_ship(--t.x, t.y);
		}
		if (t.num[0] == 4 && t.x < 108)
		{
			erase_ship(t.x, t.y);
			draw_ship(++t.x, t.y);
		}
		for (int i = 0; i < 5; i++)
		{
			if (t.bullet[i] == 1)
			{
				erase_bullet(t.bulletx[i], t.bullety[i]);
				if (t.bullety[i] > 0)
				{
					if (cursor(t.bulletx[i], t.bullety[i]-1 ) == '*') 
					{
						Beep(700, 100);
						t.bullet[i] = 0;
						erase_bullet(t.bulletx[i], t.bullety[i] - 1);
						erase_star(t.bulletx[i], t.bullety[i] - 1);
						t.curser++;
						draw_star(rand() % 100, rand() % 5);

					}
					else
					{
						createbullet(t.bulletx[i], --t.bullety[i]);
					}
				}
				else
				{
					erase_bullet(t.bulletx[i], t.bullety[i]);
					t.bullet[i] = 0;
				}
			}

		}
		Sleep(100);
		setcolor(2, 0);
	} while (t.ch != 'x');
}


void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);

}
void erase(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf("  ");
}
void erase_ship(int x, int y)
{
	gotoxy(x, y);
	setcolor(2, 0);
	printf("            ");

}
void erase_star(int x, int y)
{
	gotoxy(0, 0);
	setcolor(0, 0);
	printf(" ");
}
void draw_ship(int x, int y)
{
	setcursor(0);
	gotoxy(x, y);
	setcolor(2, 4);
	printf(" [--:0:--]  ");
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void createbullet(int x, int y)
{
	setcolor(6, 0);
	gotoxy(x, y);
	printf("^");
}
void erase_bullet(int x, int y)
{
	setcolor(2, 0);
	gotoxy(x, y);
	printf(" ");
}
void draw_star(int x, int y)
{
	setcolor(6, 0);
	gotoxy(x, y);
	printf("*");
}
char cursor(int x, int y)
{
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

		return '\0';
	else
	{
		return buf[0];

	}
}
void score(int x, int y)
{
	gotoxy(105, 1);
	setcolor(12, 0);
	printf("Score : %d", t.curser);
}