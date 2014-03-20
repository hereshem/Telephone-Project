#include<iostream.h>
#include<conio.h>
#include<dos.h>

class call_time								//for time duration
{ public:
  unsigned int hr,min,sec;
  call_time()
  { hr=min=sec=0;
  }
  void checktime()
  { if(sec>9)
    {  sec=0;min++;
       if(min>59)
       {  min=0;hr++;
	  if(hr>59)hr=0;
       }
    }
  }
};
void main()
{
  clrscr();
  call_time t;
  char ch;
    cout<<t.hr<<" : "<<t.min<<" : "<<t.sec;
  while(1)
  {
	cout<<"\b\b\b\b\b\b\b\b\b\b\b\b";
	cout<<t.hr<<" : "<<t.min<<" : "<<t.sec;
	delay(100);
	t.sec++;
	t.checktime();

    if(kbhit())
    {	ch=getch();
	if(ch==13) break;
    }
  }
  cout<<"\nCall Ended\n";
   cout<<t.hr<<" : "<<t.min<<" : "<<t.sec;
   getch();
}