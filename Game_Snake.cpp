#include<stdio.h>	
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<time.h>
#define Length	25
#define Width 	80

void gotoXY (int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void TextColor (int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , color);
}
void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;                  
	HANDLE	hConsoleOut;
	COORD	Home = {0,0};
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut,' ',csbiInfo.dwSize.X * csbiInfo.dwSize.Y,Home,&dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
}
enum Status{UP, DOWN, RIGHT, LEFT};
struct Dot
{
	int x, y;	
};
struct Snake
{
	int n;
	Dot d[50];
	int score = 0;
	Status st;
};
struct Food
{
	Dot toado;
};
void Background(Snake &snake)
{
	printf("############################################################        GAME SNAKE\n");
	printf("#                                                          #\n");
	printf("#                                                          #\n");
	printf("#                                                          #        Score: %d\n", snake.score);
	printf("#                                                          #\n");
	printf("#                                                          #\n");
	printf("#                                                          #	KEYBOARD\n");
	printf("#                                                          #	W = UP\n");
	printf("#                                                          #	A = LEFT\n");
	printf("#                                                          #	S = DOWN\n");
	printf("#                                                          #	D = RIGHT\n");
	printf("#                                                          #\n");
	printf("#                                                          #\n");
	printf("#                                                          #\n");
	printf("############################################################");
	
}
void Display(Snake snake, Food f)
{
	TextColor(9);
	Background(snake);
	gotoXY(f.toado.x, f.toado.y);
	TextColor(1 + rand() %10);
	putchar(246);
	gotoXY(67,1);
	printf("By: NGUYEN HUY");
	for(int i = 0; i < snake.n; i++)
	{
		TextColor(1 + rand() %10); // 1+ vi khong muon xuat hien 0(Black),  %10 la 10 mau` dau`.
		gotoXY(snake.d[i].x, snake.d[i].y);
		putchar(162);
	}
}
bool GameOver(Snake &snake)
{
	if(snake.d[0].x <= 0 || snake.d[0].x >= Width - 21 || snake.d[0].y <= 0 || snake.d[0].y >= Length - 11)  return 0; // Cham bien thi thua
	for(int i = 1; i < snake.n; i++)	//CHo i chay tu 1. Tu cham chinh minh thi thua 
	{
		if(snake.d[0].x == snake.d[i].x && snake.d[0].y == snake.d[i].y)
		{
			return 0;
		}
	}
	return 1;
}
void Move_Control(Snake &snake)
{
	if(kbhit())
	{
		char key = getch();
		if(key == 'A' || key == 'a') 	snake.st = LEFT;
		else if(key == 'D'|| key == 'd') snake.st = RIGHT;
		else if(key == 'W'|| key == 'w') snake.st = UP;
		else if(key == 'S'|| key == 's') snake.st = DOWN;
	}
	if(snake.st == LEFT)		snake.d[0].x--;
	else if(snake.st == RIGHT)	snake.d[0].x++;
	else if(snake.st == UP)		snake.d[0].y--;
	else if(snake.st == DOWN)	snake.d[0].y++;
}
void TouchFood(Snake &snake, Food &f, int &speed)
{
	if(snake.d[0].x == f.toado.x && snake.d[0].y == f.toado.y)
	{
		putchar(7) ; // phat am thanh trong ASCII
		snake.n++;
		srand(time(NULL));
		f.toado.x = 1 + rand() % (Width-22);
		f.toado.y = 1+ rand() % (Length-12);
		snake.score += 10;
		if(speed == 100)
		{
			return;
		}else{
			speed = speed-10;
		}
	}
}

int main()
{
	int speed = 200;
	Snake snake; Food f;
	snake.d[0].x = 15;
	snake.d[0].y = 7;
	snake.st = RIGHT;
	snake.n = 2;
	f.toado.x = 15;
	f.toado.y = 5;
	while(GameOver(snake))
	{
		clrscr();
		Display(snake, f);
		for(int i = snake.n - 1; i > 0; i--)
		{
			snake.d[i] = snake.d[i-1];
		}
		TouchFood(snake,f,speed);
		Move_Control(snake);
		Sleep(speed);
	}
	gotoXY(15,15);
	printf("GAME OVER\n\nTong diem: %d\n", snake.score);
	while(getch() != 13)
	{
		printf("\nPress ENTER button to exit Program. ");
	}
	

}
