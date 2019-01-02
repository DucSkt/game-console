#include<stdio.h>
#include<conio.h>
#include<windows.h>

#define Width  70
#define	Length 20

int dem = 0, diem = 0;

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
enum Status{LEFT, RIGHT};

struct ToaDo
{
	int x,y;
};
struct Bird
{
	ToaDo td;
	char chim[3][3];
	
	void KhoiTao();
	void Display();
	void Control();
};

void Bird::KhoiTao()
{
	td.x = 10;
	td.y = 10;
	
	chim[1][0] = chim[1][2] = '='; chim[0][1] = ')';  chim[0][2]= ' '; chim[0][0] =' ';
	chim[1][1] = '*'; chim[2][1] = '>';
}
void Background()
{	TextColor(11);
	printf("######################################################################\n");
	printf("#                                                                    #\n");
	printf("#                                                                    #\n");
	printf("#                                                                    #\n");
	printf("#                                                                    #\n");
	printf("#                                                                    #\n");
	printf("#                                                                    #\n");
	printf("#                                                                    #\n");
	printf("#                                                                    #\n");
	printf("#                                                                    #\n");
	printf("#                                                                    #\n");
	printf("#                                                                    #\n");
	printf("#                                                                    #\n");
	printf("#                                                                    #\n");
	printf("#                                                                    #\n");
	printf("#                                                                    #\n");
	printf("#                                                                    #\n");
	printf("#                                                                    #\n");
	printf("#                                                                    #\n");
	printf("######################################################################\n");	
}
void Bird::Display()
{
	Background(); // Hinh nen
	TextColor(rand()% 15 + 1);
	for(int dong = -1; dong <= 1; dong++)
	{
		for(int cot = -1; cot <= 1; cot++)
		{
			int x = dong + td.x;
			int y = cot +  td.y;
			gotoXY(x,y);
			putchar(chim[dong+1][cot+1]); // +1 vi trong mang chi co 0 1 2
		}
	}
}

void Bird::Control()
{
	if(kbhit())
	{
		int key = getch();
		if(key == 32)
		{
			td.y--;
		}
	}else{
		td.y++;
	}
}

struct Column
{
	int h, w, d; 	// h = height	w = width	d = disstance
	ToaDo td;
	Column()
	{
		w = 5;
		td.x = 66;
	}
	void Move()
	{
		td.x--;
		if(td.x == 5)
		{
			diem++;
			putchar(7); // ham keu tieng pip pip
		}
		if(td.x == 2)
		{
			td.x = 69;
		}	
	}
	void Setcolumn(int height, int distance)
	{
		h = height; d = distance;
	}
	void Display();
};

void Column::Display()
{
	TextColor(10);
	for(int i = td.x; i < td.x+w; i++)
	{
		for(int j = 1; j < Length-1; j++)
		{
			if((j < h || j > h+d) && td.x <= 65)
			{
					gotoXY(i,j);
					putchar(35);
			}
		}
	}
}

void move(Column cl[5])	// ham con cuc bo
{
	dem++;
	cl[1].Display();
	cl[1].Move();
	if(dem >= 17)
	{
		cl[2].Display();
		cl[2].Move();
	}
	if(dem >= 34)
	{
		cl[3].Display();
		cl[3].Move();
	}
	if(dem >= 51)
	{
		cl[4].Display();
		cl[4].Move();
	}
	if(dem >= 68)
	{
		cl[5].Display();
		cl[5].Move();
	}

}
void SCORE()
{
	TextColor(12);
	gotoXY(1,21);
	printf("Score: %d\n",diem);
	gotoXY(72, 1);
	printf("By: Nguyen Huy\n");
}
int main()
{
	Bird bird;
	Column cl[6];
	cl[1].Setcolumn(8,5);
	cl[2].Setcolumn(6,7);
	cl[3].Setcolumn(5,5);
	cl[4].Setcolumn(5,6);
	cl[5].Setcolumn(6,5);
	bird.KhoiTao();
	while(1)
	{
		clrscr();
		bird.Display();
		move(cl);
		bird.Control();
		SCORE();
		Sleep(300);
	}
	
}
