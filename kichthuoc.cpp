#include <stdio.h>
void hoanvi(int a, int b)
{
	int temp=a;
	a=b;
	b=temp;
	printf("kq la %d %d", a, b);
}
int main()
{
	int x,y;
	printf("nhap x,y");
	scanf("%d%d",&x,&y);
	hoanvi(x,y);
}
