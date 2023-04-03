#include <iostream>
#include <iomanip>
#include <conio.h>
#include <stdio.h>
#include <string>
#include <ctime>
using namespace std;

void header(void);
void menu(void);
void date(void);
void additional(void);
void head2(void);
void display(int);
void booking(void);
void cancel(void);
void displayall(void);
int main(void);
bool ifvaliddate(int,int,int);
void error(void);

int n = 0;
struct reservation
{
  string name,roomtype;
  int  id,typenumber,number, dd1, mm1, yy1,dd2, mm2, yy2, days, price, phone_number,cancel;
} room[100];


void header()
{
	cout << "\t\t+=======================================================+\n\t\t|\t\t\t\t\t\t\t|\n";
  	cout << "\t\t|\t\t   Resort Booking System\t\t|\n\t\t|\t\t\t\t\t\t\t|\n";
  	cout << "\t\t+=======================================================+\n\n\n";
}
void head2() 
{
	 cout << "\n\t+-----------------------------------------------------------------------------------------------+" << endl;
	 cout << "\t|  Booking ID\t|    Room type\t|    Check in\t|      Days\t|  No of Rooms\t|    Price\t|" << endl;
	cout << "\t+-----------------------------------------------------------------------------------------------+" << endl;

}

void display(int x)
{
	cout<<"\t|       "<<room[x].id<<"\t|      "<<room[x].roomtype<<"\t|    "<<room[x].dd1<<"/"<<room[x].mm1<<"/"<<room[x].yy1<<"\t|       "<<room[x].days<<"\t|       "<<room[x].number<<"\t|    "<<room[x].price<<"\t|";
	cout << "\n\t+-----------------------------------------------------------------------------------------------+" << endl;
}
  
void menu ()
{
  	cout << "\t\t\t1) Booking" << endl;
  	cout << "\t\t\t2) Display all records" << endl;
  	cout << "\t\t\t3) Cancellation" << endl;
  	cout << "\t\t\t4) For additionalal services" << endl;
  	cout << "\t\t\t5) Exit" << endl;
  	cout << "\n\t\t\tEnter your choice....";
}


void date ()
{   
	int i;
    int difference;
    struct tm a = {0,0,0,room[n].dd1,room[n].mm1-1,room[n].yy1-1900};
    struct tm b = {0,0,0,room[n].dd2,room[n].mm2-1,room[n].yy2-1900}; //104 = 2004
    time_t x = mktime(&a);
    time_t y = mktime(&b);
    
    if ( x != (std::time_t)(-1) && y != (std::time_t)(-1) )
    {
        double difference = difftime(y, x) / (60 * 60*24);
        
        room[n].days=difference;
    }

}

bool ifvaliddate(int d, int m, int y)
{
    if (y > 2030 || y < 2022)
    	return false;
    if (m < 1 || m > 12)
    	return false;
    if (d < 1 || d > 31)
    	return false;
    if (m == 2)	//february
    {
        if ( ((y % 4 == 0)&&(y % 100 != 0)) || (y % 400 == 0) )
        	return (d <= 29);
        else
        	return (d <= 28);
    }
    if (m == 4 || m == 6 || m == 9 || m == 11)
        return (d <= 30);
 
    return true;
}

void additional()
{
 	int i=0,total=0;
 	system("cls");
	header();
	string cancel;
	double bed,num,num1;
	cout<<"\n\t\tEnter your booking id ... ";
	cin>>i;
	if(i> 0 && i<=n+1){
	
	cout<<"\n\t\tNo. of extra bed(1 bed = 100rs/night) ... ";
	cin>>bed;
	cout<<endl;
	cout<<"\t\tOther Activities :"<<endl;
	cout<<"\t\t\t1) Arcade (50rs/person)"<<endl;
	cout<<"\t\t\t2) Swimming (50rs/person)"<<endl;
	cout<<"\t\t\t3) Horse Riding (100rs/person)"<<endl;
	cout<<"\tSelect your choice .... ";
	cin>>num;
	cout<<"\tSelect number of people .... ";
	cin>>num1;
	cout<<endl;
	cout<<"\tDo you want free cancellation policy? (100rs) (yes/no) .... " ;
	cin>>cancel;
	cout<<endl;
	
	bed=bed*100*room[n].days;
	if(num==1 || num==2){
		num=num*50*room[n].days*num1;
	}else if(num==3){
		num=num*100*room[n].days*num1;
	}
	if(cancel=="yes")
    {total+=100;
	room[i-1].cancel=1;}//price one night??
    else if ( cancel=="no")
    {total+=0;}
}
else{
	cout<<"\n\t\tThe id is invalid";
	getch();
	system("cls");
   	main();
}

	total=total+bed+num;
	room[i-1].price+=total;
	cout<<"\n\n";
	head2();
    display(i-1);
	getch();
	system("cls");
   	main();
}


void booking ()
{
    system("cls");
	header();
	int p=0;																							//dummy variable
    cout << "\t\t\tEnter your first name .... ";
    cin>>room[n].name;																					//It takes only single word as name
    cout << "\n\t\t\tEnter the check in date (dd mm yyyy) .... ";
    cin >> room[n].dd1 >> room[n].mm1 >> room[n].yy1;
    if(!(ifvaliddate(room[n].dd1,room[n].mm1,room[n].yy1))) error();
    
    cout << "\n\t\t\tEnter the check out date (dd mm yyyy) .... ";
    cin >> room[n].dd2 >> room[n].mm2 >> room[n].yy2;
    if(!(ifvaliddate(room[n].dd2,room[n].mm2,room[n].yy2))) error();
    
    date();
   
    cout << "\n\t\t\tTypes of Rooms : ";
    cout << "\n\t\t\t1) Basic type   (850 rs/day)";
    cout << "\n\t\t\t2) Suite type   (1770 rs/day)";
    cout << "\n\t\t\t3) Elite type   (2690) rs/day)";
    cout << "\n\n\t\t\tSelect your choice .... ";
    
    cin >> room[n].typenumber;
    if(room[n].typenumber!=1 && room[n].typenumber!=2 && room[n].typenumber!=3) error();
    
    cout << "\n\t\t\tEnter number of Rooms required .... ";
    cin >> room[n].number;
    if(room[n].number<1 || room[n].number>100) error();
    
    cout << "\n\n\t\t\t  ***  Your Room Has Been Booked   ***";
    room[n].id=n+1;
    if(room[n].typenumber==1)
    {
    	room[n].price+=room[n].days*room[n].number*850;
    	room[n].roomtype = "Basic";
	}
    else if(room[n].typenumber==2)
    {
    	room[n].price+=room[n].days*room[n].number*1770;
    	room[n].roomtype = "Suite";
	}
    else if(room[n].typenumber==3)
    {
    	room[n].price+=room[n].days*room[n].number*2690;
    	room[n].roomtype = "Elite";
	}
	else
    {
		cout<<"+++++++++++++++++++++++++++++++++++ ERROR ++++++++++++++++++++++++++++++++++";
		getch();
	system("cls");
   	main();
	}
	
    getch();
    system("cls");
    header();
    head2();
    display(n);
    getch();
    n++;
    system("cls");
    main();
  }
  
void cancel()
{
	system("cls");
	header();
	int one;
	cout<<"\t\tCancelation Process :\n\n";
	cout<<"\t\tPlease enter your booking id ....";
	cin>>one;
	room[one-1].days=0;
	if(room[one-1].cancel==1){
		cout<<"\t\tNo Cancelation charges..."<<endl;
	}else{
		int charges;
		cout<<"\t\tCancelation charges : 500rs/room";
		charges=room[one-1].number*500;
		cout<<"Total : "<<charges<<endl;
	}
   	cout << "\n\n\t\t\t  ***  Your booking has been canceled   ***";
   	getch();
   	system("cls");
   	main();
}

void displayall()
{
  	system("cls");
    header();
	head2();
	for(int i=0; i!=n;i++)
		if(room[i].days!=0)
			display(i);
	getch();
	system("cls");
	main();
	
}

void error(void)
{
	cout<<"\n\n\t\t\t++++++++++++++----------- INPUT ERROR -----------++++++++++++++";
	exit(0);
}

int main()
{
    int ch;

	header();
	menu();
	cin>>ch;
	
	switch(ch)
	{
		case 1:
	    	booking();
	    	break;

	  	case 2:
	    	displayall();
			break;

	  	case 3:
	    	cancel();
	    	break;

	  	case 4:
			additional();
	    	break;
		case 5:
			cout << "\n\n\t\tThank you .... Visit again...." << endl;
			exit(0);
	    	break;
	}
   	return 0;

  }

  // Uploaded and connected to github

