#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#define Width  80
#define Length 25
#define WidthRoad 20

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

struct ToaDo
{
	int y, x;
};
struct HinhDang
{
	char a[3][3];
	
};
struct Xe
{
	ToaDo td;
	HinhDang hd;
};
struct VatCan
{
	ToaDo td;
	HinhDang hd;
};

void KhoiTao(Xe &xe, VatCan &vc)											
{	
	// Khoi tao chiec xe														
	#define shape xe.hd.a 										
	xe.td.x = (WidthRoad-1)/2;
	xe.td.y = Length-2;
	shape[0][0] = shape[0][2] = shape[2][0] = shape[2][2] = putchar(216); shape[1][0] = '^'; shape[1][1] = '|';
	// Khoi tao vat can
	#define shapevc vc.hd.a
	vc.td.x = 2;
	vc.td.y = 2;
	shapevc[0][0] = shapevc[0][2] = shapevc[2][0] = shapevc[2][2] = putchar(149); shapevc[1][1] ='X';
}
void Background()
{
	TextColor(1 + rand() %10);
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
	printf("#                  #\n");
}
void Display(Xe xe, VatCan vc)
{
	Background();
	TextColor(9);
	// hein thi cho chiec xe
	for(int dong = -1; dong <= 1; dong++)
	{
		for(int cot = -1; cot <= 1; cot++)
		{
			int x = dong + xe.td.x;
			int y = cot + xe.td.y;
			
			gotoXY(x,y);
			putchar(xe.hd.a[dong+1][cot+1]);
		}
	}
	// hien thi cho vat can
		TextColor(12);
		for(int dong = -1; dong <= 1; dong++)
	{
		for(int cot = -1; cot <= 1; cot++)
		{
			int x = dong + vc.td.x;
			int y = cot + vc.td.y;
			
			gotoXY(x,y);
			putchar(vc.hd.a[dong+1][cot+1]);
		}
	}
	
}

void Control(Xe &xe, VatCan &vc)
{
	srand(time(NULL));
	vc.td.y++;
	if(vc.td.y == Length+1)
	{
		vc.td.y = 2; // dong nay la cho vat can quay lai ban dau
		vc.td.x = 2 + rand()%(WidthRoad-4);	// sinh so ngau nhien cho vat can ra cho khac
	}
	if(kbhit())
	{
		int key = getch();
		if((key == 'A' || key == 'a') && xe.td.x >2) xe.td.x--; // khong cho dung vao gioi han duong dua ben trai
		if((key == 'D' || key == 'd')&&xe.td.x <WidthRoad-3) xe.td.x++;
	}
}
void Touch(Xe &xe, VatCan &vc)
{
	if( (abs(xe.td.x-vc.td.x) <= 2) && (abs(xe.td.y-vc.td.y <= 2) ) )
	{
		printf("Ban da thua");
	}
}
int main()
{
	Xe xe; VatCan vc;
	KhoiTao(xe,vc);
	while(1)
	{
			clrscr();
			Touch(xe,vc);
			Display(xe,vc);
			Control(xe,vc);
			Sleep(100);
	}

	
}
