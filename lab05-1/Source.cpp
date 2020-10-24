#include<stdio.h>
#include<windows.h>
#include<conio.h>
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void draw_ship(int x, int y)
{
	gotoxy(x, y); 
	setcolor(2,4);
	printf(" <-0-> ");
}
void erase_ship(int x, int y) {
	gotoxy(x, y);
	setcolor(2, 0);
	printf("       ");
}
void draw_bullet(int x,int y){

	gotoxy(x, y);
	printf("|");
}
void erase_bullet(int x, int y)
{
	gotoxy(x, y);
	printf("     ");
}
int bulletStatus[5] = { 0,0,0,0,0 };
int bulletX[5] = { 0,0,0,0,0 };
int bulletY[5] = { 0,0,0,0,0 };
int main()
{
	char ch = ' ',direct = 's', shoot = 'f', bulletDirect, bulletDirectX, bulletLimit = 0;
	int x = 38, y = 20, m{};
	setcursor(0);
	draw_ship(x, y);
	do {
		if (_kbhit()) 
		{
			ch = _getch();
			if (ch == 'a') { m = -1; }
			if (ch == 's') { m =  0; }
			if (ch == 'd') { m =  1; }
			if (ch == 'e') {
				if (bulletLimit < 5)
				{


					int i;
					for (i = 0; i < 5; i++)
					{
						if (bulletStatus[i] == 0) {
							bulletLimit++;
							bulletStatus[i] = 1;
							bulletX[i] = x;
							bulletY[i] = y - 2;
							break;
						}
					}
					shoot = 't';


				}
			}
			fflush(stdin);
		}
		Sleep(100);
		if(m==-1)
		{
			if (x <= 0)
			{
				x = 1;
			}
		erase_ship(x, y);
		draw_ship(--x, y);
		}
		if (m == 1) 
		{
			if (x >= 74) 
			{
				x = 74;
			}
			erase_ship(x, y);
			draw_ship(++x, y);
		}
		if (m==0)
		{
			draw_ship(x, y);
		}
		if (shoot == 't')
		{
			for (int i = 0; i < 5; i++)
			{
				if (bulletY[i] <= -1) {
					bulletLimit--;
					if (bulletLimit < 0) {
						bulletLimit = 0;
					}
					setcolor(0, 0);
					erase_bullet(bulletX[i] + 1, bulletY[i] + 1);
					bulletStatus[i] = 0;
				}
				else
				{
					setcolor(0, 0);
					erase_bullet(bulletX[i] + 1, bulletY[i] + 1);
					Sleep(1);
					setcolor(2, 4);
					draw_bullet(bulletX[i] + 3, bulletY[i]);
					bulletY[i] = bulletY[i] - 1;
				}
			}

		}
		
	} while (ch != 'x');
		return 0;
}