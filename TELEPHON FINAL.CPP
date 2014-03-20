////////////////////////////////////////////////////////////////////////////
/////////////// TELEPHONE BILLING AND RECHARGE SYSTEM //////////////////////
///////////////////// Created: May 14, 2010 ////////////////////////////////
///////////////////// By : Hem Kr. Shrestha ////////////////////////////////
////////////////////////////////////////////////////////////////////////////


#include<iostream.h>
#include<fstream.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<iomanip.h>
#include<math.h>
#include<dos.h>

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class call_time						//for time duration
{ public:
  unsigned int hr,min,sec;
	call_time()
	{ hr=min=sec=0;
	 }
	void checktime();

};

//////////////////////////////////////////////////////////////////////////////
class phone						//for individual call
{	char number[15];
	float rate;
	float amount;
	float remamt;
	call_time tim;
	call_time dat_oc;
	call_time tim_oc;
    public:
	void getnum();
	int chknum();
	void gettim(int);
	int getmaxtime(float);
	void callcenter();
	float showbal();
	float getrate(){ return rate;}
	void addtofile()
	{	fstream file;
		struct time ti;
		gettime(&ti);
		struct date dt;
		getdate(&dt);
		tim_oc.hr=ti.ti_hour;
		tim_oc.min=ti.ti_min;
		tim_oc.sec=ti.ti_sec;
		dat_oc.hr=dt.da_year;
		dat_oc.min=dt.da_mon;
		dat_oc.sec=dt.da_day;
		file.open("CALL_REC.DAT",ios::out|ios::app);
		file.write((char*)this,sizeof(phone));
		file.close();
		//cout<<sizeof(phone);getch();
	}
	void readfromfile()
	{       int sn=1;
		fstream file;
		cout<<"\n\n SN\t NUMBER\t\tRATE    DURATION  AMOUNT     TIME       DATE\n";
		file.open("CALL_REC.DAT",ios::in);
		file.seekg(0,ios::beg);
		while(file.read((char*)this,sizeof(phone)))
		{      	cout<<endl<<setw(3)<<sn++<<setw(15)<<number<<setw(8)<<rate;
			cout<<"\t"<<tim.hr<<":"<<tim.min<<":"<<tim.sec<<setw(8)<<amount;
			cout<<"\t  "<<tim_oc.hr<<":"<<tim_oc.min<<":"<<tim_oc.sec;
			cout<<"  "<<dat_oc.hr<<"/"<<dat_oc.min<<"/"<<dat_oc.sec;
			if(sn%25==0){cout<<"\n Press Any Key To Continue....";getch();}

		}
		cout<<endl;
		file.close();
	}

};

/////////////////////////////////////////////////////////////////////////////////
class recharge
{       int sn;
	char pin[20];
	float amount;
	int access;
     public:
	int chkpin(char ph[]);
	void add2file(char ch[14],float amt,int serial);
	int getserial();
	void viewpin();

};
////////////////////////////////////////////////////////////////////////////////////
class balance
{	float bal;
     public:
	float getbal();
	void reducebal(float amount);
	void recharge(float amount);

};

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// SOUND ///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
class tone
{
public:
	void snd_ph_cut()
	{
		for(int i=0;i<5;i++)
		{  sound(1000);
		   delay(200);
		   nosound();
		   delay(200);
		}
	}
	void snd_key_press()
	{	sound(750);
		delay(200);
		nosound();
	}
	void ph_ring(int &x)
	{	if(x)
		{ sound(400);x=0;}
		else
		{ nosound();x=1;}
	}
};
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////         CLASS CALL_TIME            ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
	void call_time::checktime()
	  { if(sec>9)
	    {  sec=0;min++;
	      if(min>59)
	      {  min=0;hr++;
		  if(hr>59)hr=0;
	      }
	    }
	 }

///////////////////////////////////////////////////////////////////////////////////////////
//////////////////           CLASS BALANCE            ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
	float balance::getbal()                     //Shows Current Balances
	{       float value=100;
		fstream file;
		file.open("BALANCE.DAT",ios::in);
		if(!file.good())
		{ file.open("BALANCE.DAT",ios::out);
		  bal=100;
		  file.write((char*)this,sizeof(balance));
		}
		else
		{ file.seekg(0,ios::beg);
		  file.read((char*)this,sizeof(balance));
		  value=bal;
		}
		 file.close();
		return value;

	}
//////////////////////////////////////////////////////////////////////////////////////////
	void balance::reducebal(float amount)       //Reduces Call Charge
	{
		fstream file;
		file.open("BALANCE.DAT",ios::in);
		file.seekg(0,ios::beg);
		file.read((char*)this,sizeof(balance));
		//float b=bal;
		file.close();
		bal-=amount;
		file.open("BALANCE.DAT",ios::out);
		file.write((char*)this,sizeof(balance));
		file.close();
	}
//////////////////////////////////////////////////////////////////////////////////////////
	void balance::recharge(float amount)               //Recharge Account
	{
		fstream file;
		file.open("BALANCE.DAT",ios::in);
		file.seekg(0,ios::beg);
		file.read((char*)this,sizeof(balance));
		//int value=bal;
		file.close();
		//value+=amount;
		bal+=amount;
		file.open("BALANCE.DAT",ios::out);
		file.write((char*)this,sizeof(balance));
		file.close();
		cout<<"\n\n Recharge Success:\n\n Your total Balance is Rs "<<bal<<endl;

	}
/////////////////////////////////////////////////////////////////////////////////////////
////////////////////            CLASS RECHARGE           ////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
	int recharge::getserial()                  //returns Number of PIN Recorded
	{
		fstream file;
		int serial;
		file.open("RECHARGE.DAT",ios::in);
		if(file.good())
		{ file.seekg(0,ios::end);
		  int total=file.tellg();
		  serial=total/sizeof(recharge);
		}else
		serial=0;
		file.close();
		return serial;
	}
//////////////////////////////////////////////////////////////////////////////////////////
	void recharge::viewpin()        //shows PIN number from file
	{     	fstream file;
		file.open("RECHARGE.DAT",ios::in);
		cout<<"\n\n\   SN\t\tPIN\t\tAMOUNT\t\tSTATUS\n";
		while(file.read((char*)this,sizeof(recharge)))
		{
			cout<<endl<<setw(5)<<sn<<setw(20)<<pin<<setw(10)<<amount<<"\t\t";
			if(access==1)cout<<"USED";
			else cout<<"NOT USED";
			if(sn%25==0){cout<<"\n Press Any Key To Continue....";getch();}
		}
		cout<<endl;
		file.close();

	}
//////////////////////////////////////////////////////////////////////////////////////////
	void recharge::add2file(char ch[14],float amt,int serial)   //writes PIN Number in File
	{
	sn=serial;
	strcpy(pin,ch);
	amount=amt;
	access=0;
	fstream file;
	file.open("RECHARGE.DAT",ios::out|ios::app);
	file.write((char*)this,sizeof(recharge));
	file.close();

	}
///////////////////////////////////////////////////////////////////////////////////////////
	int recharge::chkpin(char ph[])         // checks pin from file and update it, return Found or Not
	{
		fstream file;
		file.open("RECHARGE.DAT",ios::in);
		file.seekg(0,ios::beg);
		int found=0;
		while (file.read((char*) this , sizeof(recharge)))
		{       if((strcmp(ph,pin))==0)
			{	if(access==0)
				{	found=amount;
					access=1;
					int location=file.tellg();
					location-=sizeof(recharge);
					file.close();
					file.open("RECHARGE.DAT",ios::out | ios::ate);
					file.seekp(location,ios::beg);
					file.write((char*) this , sizeof(recharge));
					file.close();
					cout<<endl<<setw(30)<<"Payment of Rs "<<amount<<" accepted.";
					 break;
				}
				else
				{	cout<<"\n Pin Number Already Used....";break;
				}
			}
		}
		file.close();
		return found;
	}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////        CLASS PHONE          //////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

	int phone::getmaxtime(float amt)        //Maximum Time call for Current Amount
	{	return (amt/rate);
	}
////////////////////////////////////////////////////////////////////////////////////
	float phone::showbal()
	{
		//cout<<"rate="<<rate<<endl;
		cout<<endl<<setw(40)<<"Time :"<<tim.min+1<<" Minutes"<<endl;
		amount=rate*float(tim.min+1);
		cout<<endl<<setw(40)<<"The Last call Charge is Rs "<<amount<<endl;
		//amount=amt;
		return amount;
	}
///////////////////////////////////////////////////////////////////////////////////////////
void phone::getnum()                      //input number
{       clrscr();
	cout<<endl<<endl<<setw(40)<<"Call 2632 for Customer Care Center:"<<endl<<endl<<setw(40)<<"Enter a Telephone Number:";
	//cin>>number;
	char c;
	int index=0;
	tone t;
	while((c=getch())!=13)
	{	if (c>='0'&&c<='9')
		{ number[index++]=c;
		  t.snd_key_press();
		  cout<<c;
		}
		if(c==8)
		{ index--;
		  if(index<0)
		  index=0;
		  else
		  cout<<"\b \b";
		}
		if(c==27)
		{ strcpy(number,"esc");
		  index=4;break;
		}
	}
	number[index]='\0';
	//cout<<endl<<number<<endl;
}
/////////////////////////////////////////////////////////////////////////////////////////
void phone::gettim(int t)
{
  char ch;
  int ringvar=1;
  tone ton;
  cout<<"\n Time Starts...\n\n";
    cout<<tim.hr<<" : "<<tim.min<<" : "<<tim.sec;
  while(1)
  {
	cout<<"\b\b\b\b\b\b\b\b\b\b\b\b";
	cout<<tim.hr<<" : "<<tim.min<<" : "<<tim.sec;
	delay(100);
	if(tim.min%2==0&&tim.sec==0) ton.ph_ring(ringvar);
	tim.sec++;
	tim.checktime();

	if(tim.min>t-1){tim.min--; break; }

    if(kbhit())
    {	ch=getch();
	if(ch==13) break;
    }
  }

  cout<<"\n\n Call Ended...\n\n";
  ton.snd_ph_cut();
   //cout<<tim.hr<<" : "<<tim.min<<" : "<<tim.sec;
   //getch();
}


////////////////////////////////////////////////////////////////////////////////////
void phone::callcenter()              //callcenter
{
	cout<<"\n\n\t\t1. Balance Inquiry\n\t\t2. Recharge\n\t\t3. View Pin\n\t\t4. Create Pin\n\t\t5. Change Password\n\t\t6. Balance Transfer\n\t\t7. View History\n\t\t8. Exit Menu";
	cout<<"\n\n\t Enter Your Choice : ";
	char choice;
	choice=getche();
	while(!(choice>'0'&&choice<='8'))
	{ if(choice==27)return;
	  cout<<"\b \b";
	  choice=getche();
	}
	tone t;
	t.snd_key_press();
	switch (choice)
	{	case '1':
			balance b;
			cout<<endl<<endl<<setw(40)<<"Your Account Balance is Rs "<<b.getbal()<<endl;
			break;
		case '2':

			char num[20];
			cout<<endl<<endl<<endl<<setw(40)<<"Enter 13 Digits Pin Number :";
			//cin>>num;
	char c;
	int index=0;
	tone t;
	while((c=getch())!=13)
	{	if (c>='0'&&c<='9')
		{ num[index++]=c;
		  t.snd_key_press();
		  cout<<c;
		}
		if(c==8)
		{ index--;
		  if(index<0)
		  index=0;
		  else
		  cout<<"\b \b";
		}
		if(c==27)
		{ callcenter();
		}
	}
	num[index]='\0';


			int l=strlen(num);
			if(l!=13)
				cout<<endl<<endl<<setw(40)<<"Invalid Pin Number...\n";
			else
			{	recharge r;
				float amount=r.chkpin(num);
				if(amount)
				{	balance b;
					b.recharge(amount);
				}
			}
			break;
		case '3':
			recharge r;
			r.viewpin();
			break;
		case '4':
{	cout<<endl<<endl<<setw(40)<<"Enter the Number of Cards:";
	int num;
	char pinum[14];
	int am;
	cin>>num;
	tone t;
	t.snd_key_press();
	cout<<endl<<endl<<endl<<setw(40)<<"Enter Amount of Recharge Card:";
	cin>>am;
	t.snd_key_press();
	cout<<endl<<endl<<setw(40)<<"SURE?? :(y/n) :";
	char ch;
	cin>>ch;
	t.snd_key_press();
     if(ch=='y')
     {  recharge r;
	int serial= r.getserial()+1;
	randomize();
	cout<<endl<<endl;
	for(int i=0;i<num;i++)
	{

		for(int j=0;j<13;j++)
			pinum[j]=char(rand()%10+48);
		pinum[j]='\0';

		r.add2file(pinum,am,serial++);
		cout<<i+1<<"\t"<<pinum<<"\t"<<am<<endl;
	}
	cout<<"\n\n File Created Successfully......\n";
      }
      else
       cout<<"\n\n Action Cancelled....\n";
       break;
}
		case '5':
		case '6':
		case '8':
		break;
		case '7':
		readfromfile();
		break;
		default:
			cout<<"\n Invalid Input....\n";

	}

}

////////////////////////////////////////////////////////////////////////////////////////////
int phone::chknum()                 //checks number and fixes rates
{       int flag=0;

	if((strcmp(number,"2632"))==0)
	{	flag=10;
		callcenter();
	}
	else if((strcmp(number,"esc"))==0) return 100;
	else
   {	int len=strlen(number);
	if(len<7)
	{
		cout<<"\n\n The number must be of at least 7 digits: ";
	}
	else if(len==7)
	{       cout<<"\n\n Local Call:\n Rate = Rs 2/min: "<<endl;
		rate=2;
	     flag=1;
	}
	else if(len==9)
	{       if (number[0]=='0')
		{
			cout<<"\n\n STD Call:\n Rate = Rs 5/min: "<<endl;
			rate=5;			// check for STD call;
			flag=1;
		}
		else
		cout<<"\n STD number must begin with '0'.... "<<endl;

	}
	else if(len>10)
	{       if(number[0]=='0'&&number[1]=='0')
		{ cout<<"\n\n ISD Call:\n Rate = Rs 20/min: "<<endl;
		  rate=20;		//check gor ISD call
		  flag=1;
		}
		else
		cout<<"\n ISD number must begin with '00' :"<<endl;
	}
	else if(len==10)
	{       if(number[0]=='9')
		{ if(number[1]=='8'&&number[2]=='0')
		  { cout<<"\n\n NCELL Mobile Call:\n Rate = Rs 4/min: "<<endl;
		    rate=4;		//check for Mobile call
		    flag=1;
		  }
		  else if(number[1]=='8'||number[2]=='4')
		  { cout<<"\n\n NTC Mobile Call:\n Rate = Rs 2/min: "<<endl;
		    rate=2;		//check for Mobile call
		    flag=1;
		  }
		  else
		  { cout<<"\n\n Other Mobile Call:\n Rate = Rs 3/min: "<<endl;
		    rate=3;		//check for Mobile call
		    flag=1;
		  }
		}
		else
		cout<<"\n Mobile Number must start with '9' : ";


	}
    }
	return flag;


}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void splashscreen()
{	int i,j,k,powr,st;
	int logo[3][45]={ { 0, 1,63, 1, 1, 0,63,37,37,37, 0,63,32,32, 0,63,37,37,37, 0,63, 9, 9, 6, 0,63, 4, 4,63, 0,30,33,33,30, 0,63, 4, 8,63, 0,63,37,37,37, 0},
			  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,63,37,37,26, 0,63, 0,63,32,32, 0,63,32,32, 0,63, 0,63, 4, 8,63, 0,30,33,37,61, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			  { 0, 0, 0, 0, 0, 0, 0,34,37,37,25, 0, 3, 4,56, 4, 3, 0,34,37,37,25, 0, 1,63, 1, 1, 0,63,37,37,37, 0,63, 2,12, 2,63, 0, 0, 0, 0, 0, 0, 0}
			};
	cout<<endl<<"\tTELEPHONE BILLING SYSTEM"<<endl;
	for(k=0;k<3;k++)
	for(i=0;i<7;i++)
	{ for(j=0;j<45;j++)
	  {	st=logo[k][j];
		powr=pow(2,i);
		if(((st%(powr*2))/powr)==1)
			cout<<"#";
		else
			cout<<" ";
	  }
	  cout<<endl;
	}
	cout<<"Created By:\t1) Hem Kr. Shrestha (065/BEX/26)\n\t\t2) Bijay Kr. Gupta  (065/BEX/32)\n\t\t3) Shreeja Shrestha (065/BEX/13)\n\t\t4) Sumel Maharjan   (065/BEX/25)";
	cout<<"\tPress Any Key.....";
	getch();
}
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
void byebyescreen()
{
	 clrscr();
	 cout<<"\n\n\n\n\n\t\tThanks for Visiting.....";
	 getch();
}
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
void menuscreen()
{
	recharge r;
	balance ba;
	char c='y';
	clrscr();
   while(c!=27)
   {       //clrscr();
	cout<<endl<<endl<<endl;
	phone p;
	tone ton;
	p.getnum();		       // Get Number
	int valid=p.chknum();
	if(valid==0)                    // Check Number & fix rate
		cout<<endl<<setw(40)<<"Invalid Number Input....";

	else if(valid==1)
	{
		float t_bal=ba.getbal();
		cout<<endl<<setw(40)<<"Your balance is Rs "<<t_bal<<endl;

		//cout<<t_bal<<endl;
		if(t_bal>p.getrate())           // Check Balance
		{               int max=p.getmaxtime(t_bal);
				p.gettim(max);               		// Get Call Time

				int currcall=p.showbal();			// Display Last call n Remaining Amount
				//cout<<"last call="<<currcall<<endl;
				ba.reducebal(currcall);
				//cout<<ba.getbal();
				cout<<endl<<setw(40)<<"The Remaining Balance is Rs "<<t_bal-currcall;
				p.addtofile();
		}
		else
		{ ton.snd_ph_cut();	cout<<endl<<setw(40)<<"Not Sufficient Balance.\n Please Recharge Your Account:";
		}
	}
	else if(valid==100)break;
	cout<<"\n\n\t\t\t Press Any Key To Continue..... ";
	//cin>>c;
	c=getch();
   }

}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
int main()
{	clrscr();
	splashscreen();
	menuscreen();
	byebyescreen();
	return 0;
}




