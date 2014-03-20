#include<stdio.h>
#include<conio.h>
void main()
{
	char ch;
	clrscr();
	printf("\n\n Press 'q' to Quit :");
	while((ch=getch())!='q')
	{	if(ch!=0)
		printf("\n ASCII Value of %c = %d ",ch,ch);
		else
		{ ch=getch();
		  printf("\n EXTENDED Value = %d ",ch);
		}
	}
}