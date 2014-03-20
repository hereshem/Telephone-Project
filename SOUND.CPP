#include <dos.h>
#include<conio.h>
#include<stdio.h>
int main(void)
{
int i;
int fre=1000;
for(i=1;i<5;i++)//kbhit())
{   sound(fre);
   fre+=50;
   delay(200);
   nosound();
   //delay(200);
   if(kbhit())
   break;
   }               delay(100);
		   sound(fre+100);delay(100);sound(fre+100);
   nosound();
   return 0;
}