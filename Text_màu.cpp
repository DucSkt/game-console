#include<iostream>
#include<windows.h>
using namespace std;
void textcolor(int x)
{
	HANDLE mau;
	mau=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}

int main()
{
		for(int i = 1; i <= 15; i++)
		{
		Sleep(100);
		textcolor(i);
		cout<<"\nsadj "<<i;
		}
	
	
}
