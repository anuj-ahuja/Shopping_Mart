#include<iostream.h>
#include<conio.h>
#include<process.h>
#include<fstream.h>
#include<string.h>
#include<stdio.h>
#include<dos.h>
fstream ufile,afile,file,ofile; //ufile-for user
			  //afile-for administrator
			  //file-temp file used in deleletion function
			  //ofile - to store orders

class user
{
char name[30],email[20],gender,add[50],type[20];
int ph;
public:
void signup()
{cout<<"ENTER NAME";
cin>>name;
cout<<"ENTER EMAIL";
cin>>email;
cout<"ENTER GENDER";
cin>>gender;
cout<<"ENTER ADDRESS";
cin>>add;
}
void displayu()
{cout<<name<<"  "<<email<<"  "<<gender<<"   "<<add<<endl;}
void signin();
int rettype();
int retname(char z[])
{
if(strcmpi(name,z)==0)
return 1;
else
return -1;
}

}u;


class admin
{
char namep[20],descp[50],type[15],pass[20],discount[20];
int price,pcode;
public:
void enterp()
{
cout<<"ENTER PRODUCT CODE\n";
cin>>pcode;
cout<<"ENTER  BRAND NAME\n ";
cin>>namep;
cout<<"ENTER COLOUR OF PRODUCT\n";
cin>>descp;
cout<<"ENTER PRICE OF PRODUCT\n";
cin>>price;
cout<<"ENTER TYPE OF PRODUCT\n";
cin>>type;
cout<<"ENTER DISCOUNT ON PRODUCT\n";
cin>>discount;
}
void displayp()
{
cout<<pcode<<"        "<<namep<<"       "<<descp<<"        "<<type<<"        "<<price<<"       "<<discount<<endl;
}
int retnamep(char m[])                    //for user and admin
{
if(strcmp(namep,m)==0)
return 1;
else
return -1;
}
int retdescp(char d[])                    //for user
{
if(strcmp(descp,d)==0)
return 1;
else
return -1;
}
int rettype(char t[])                    //for user
{
if(strcmp(type,t)==0)
return 1;
else
return -1;
}
int retpricep(int p)                    //for admin
{
if(price==p)
return 1;
else
return -1;
}
int retpcode(int p)                   //for admin
{
if(pcode==p)
return 1;
else
return -1;
}
int retprice()
{
return price;
}

}a;



void aread()      //to read admistrator data
{
clrscr();
afile.open("admi.dat",ios::in);
while(!afile.eof())
{
afile.read((char*)&a,sizeof(a));
if(afile.eof())break;
a.displayp();
}
afile.close();
}

void awrite()          //to write admin data
{
afile.open("admi.dat",ios::app);
a.enterp();
afile.write((char*)&a,sizeof(a));
afile.close();
}
void modify()             //to modify admin data
	 {  clrscr();
	 afile.open("admi.dat",ios::out|ios::in);
	   int i=0,n;
	   char m[20];
	   cout<<"ENTER DATA TO BE MODIFIED\nENTER NAME";
	   cin>>m;
	   cout<<"ENTER CODE";
	   cin>>n;
	   while(!afile.eof())
	   { afile.read((char*)&a,sizeof(a));
	   i++;
	   if(afile.eof()) break;
	   if(a.retnamep(m)==1&&a.retpcode(n)==1)
	   {cout<<"\nENTER DATA FOR MODIFICATION\n";
	   a.enterp();
	   afile.seekg((i-1)*sizeof(a),ios::beg);
	   afile.write((char*)&a,sizeof(a));
	   }
	    else
	   cout<<"NOT FOUND";
	   }afile.close();
	   }


void cancel()                  //to delete data
{          clrscr();
 afile.open("admi.dat",ios::in);
	  file.open("tem.dat",ios::out);
	   char m[20],p,c;
	   cout<<"\nENTER PROCUCT CODE TO BE CANCELLED\n";
	   cin>>c;
	    cout<<"\nENTER NAME OF PRODUCT TO BE CANCELLED\n";
	   cin>>m;
	    cout<<"\nENTER PRICE OF PRODUCTE TO BE CANCELLED\n";
	   cin>>p;

	   while(!afile.eof())
	   {
	   afile.read((char*)&a,sizeof(a));
	   if(afile.eof()) break;
	   if(a.retnamep(m)!=1&&a.retpricep(p)!=1&&a.retpcode(c)!=1)
			   file.write((char*)&a,sizeof(a));
	   }
	   afile.close();
	   file.close();
	   remove("admi.dat");
	   rename("tem.dat","admi.dat");
		   }

void uwrite()          //to write user data
{
ufile.open("user.dat",ios::app);
u.signup();
ufile.write((char*)&u,sizeof(u));
ufile.close();
}

void orderead()            //to read data from order file
{
   clrscr();
ofile.open("order.dat",ios::in);
while(!ofile.eof())
{
 ofile.read((char*)&a,sizeof(a));
 if(ofile.eof())break;
 ofile.read((char*)&u,sizeof(u));
  if(ofile.eof())break;
  a.displayp();
 u.displayu();
}
ofile.close();
}



void usersearch()            //for user to search products
{clrscr();
int nop,bill=0;
char m[50],t[50],d[20],c,z[20];
cout<<"ENTER BRAND NAME OF PRODUCT\n";
cin>>m;
cout<<"ENTER TYPE OF PRODUCT\n";
cin>>t;
cout<<"ENTER COLOUR OF PRODUCT\n";
cin>>d;
cout<<"PLEASE ENTER YOUR NAME FOR SECURITY\n";
cin>>z;
afile.open("admi.dat",ios::in);
ofile.open("order.dat",ios::app);
ufile.open("user.dat",ios::in);
while(!afile.eof()&&!ofile.eof())

{
afile.read((char*)&a,sizeof(a));
if(afile.eof())break;
ufile.read((char*)&u,sizeof(u));
if(ufile.eof())break;
if(a.retnamep(m)==1&&a.rettype(t)==1&&a.retdescp(d)==1&&u.retname(z)==1)
{
a.displayp();
cout<<"ENTER QUANTITY\n";
cin>>nop;
bill=nop*a.retprice();
cout<<"BILL ="<<bill;
cout<<"\nPRESS 'B' TO ORDER PRODUCT or PRESS 'R'TO RETURN TO MAIN MENU \n";
cin>>c;
if(c=='B'||c=='b')
{
ofile.write((char*)&a,sizeof(a));
ofile.write((char*)&u,sizeof(u));
cout<<"THANK YOU\n\n";      }
else if(c=='R'||c=='r')
return;


}}
afile.close();
ofile.close();
ufile.close();
}


void amenu()                //administrator menu
{
clrscr();
textbackground(MAGENTA);
char choice;
do
{
cout<<"\n\n\n1.ENTER NEW PRODUCTS\n2.DISPLAY PRODUCTS\n3.MODIFY\n4.DELETE\n5.DISPLAY ORDERS\n6.RETURN TO MAIN MENU";
cout<<"\nENTER CHOICE\n";
cin>>choice;
switch(choice)
{
case '1':awrite();
	 clrscr();
	 break;
case '2':aread();
	 break;
case '3':modify();
	 clrscr();
	 break;
case '4':cancel();
	 clrscr();
	 break;
case '5':orderead();
	 break;
case '6':clrscr();
	 return;

}}while(choice!='6');
}






void userm()            //user menu
{
clrscr();
textbackground(RED);
char cho;
do
{
cout<<"1.ENTER DETAILS\n2.SEARCH PRODUCT\n3.EXIT\nENTER CHOICE";
cin>>cho;
switch(cho)
{
case '1':uwrite();
	 break;
case '2':usersearch();
	 break;
case '3':exit(0);
}}
while(cho!='3');
}

void loading()                  //loading bar
{             int k=0;
	gotoxy(35,15);
	cprintf("LOADING PLEASE WAIT");
	gotoxy(34,16);
	cprintf("*************");
	gotoxy(34,18);
	cprintf("*************");
	gotoxy(34,17);
	cprintf("*");
	gotoxy(46,17);
	cprintf("*");
	gotoxy(35,17);
	for(k=0;k<10;k++)
	{cprintf("|");
	delay(100);
	}
}


void main()
{          clrscr();

admin a;
user s;
int i=0,k;
char ch,x,pass[20],p[]={"cbj"};
fstream ufile,afile;
do
{ clrscr();
gotoxy(8,7);cprintf("---------------");
gotoxy(7,8);cprintf("|");
gotoxy(7,9);cprintf("|");
gotoxy(7,10);cprintf("|");
gotoxy(7,11);cprintf("|");
gotoxy(8,11);cprintf("--------------");
gotoxy(22,8);cprintf("|");
gotoxy(22,9);cprintf("|");
gotoxy(22,10);cprintf("|");
gotoxy(22,11);cprintf("|");
gotoxy(8,8);cprintf("FLAT 50%");
gotoxy(8,9);cprintf("ON ALL ");
gotoxy(8,10);cprintf("NIKE PRODUCTS");

gotoxy(67,7);cprintf("----------");
gotoxy(66,8);cprintf("|");
gotoxy(66,9);cprintf("|");
gotoxy(66,10);cprintf("|");
gotoxy(67,11);cprintf("----------");
gotoxy(77,8);cprintf("|");
gotoxy(77,9);cprintf("|");
gotoxy(77,10);cprintf("|");
gotoxy(67,8);cprintf("GET CASH");
gotoxy(67,9);cprintf("BACK OF ");
gotoxy(67,10);cprintf("11%");

gotoxy(35,20);cprintf("---------------");
gotoxy(34,21);cprintf("|");
gotoxy(34,22);cprintf("|");
gotoxy(34,23);cprintf("|");
gotoxy(35,24);cprintf("---------------");
gotoxy(50,21);cprintf("|");
gotoxy(50,22);cprintf("|");
gotoxy(50,23);cprintf("|");
gotoxy(35,21);cprintf("GET Rs.1000");
gotoxy(35,22);cprintf("DISCOUNT ON ");
gotoxy(35,23);cprintf("FIRST PURCHASE");

gotoxy(30,7);
textbackground(BLUE);
textcolor(GREEN);
cprintf("WELCOME TO THE SHOPPPING MART");

gotoxy(35,10);
cprintf("1.ADMINTRATOR");
gotoxy(35,11);
cprintf("2.USER");
gotoxy(35,12);
cprintf("3.EXIT");
gotoxy(35,13);
cprintf("ENTER CHOICE");
cout<<endl;
gotoxy(35,14);
cin>>ch;
switch(ch)
{
case '1':clrscr();
	 cout<<"enter password\n";
	 do
	 {
	 x=getch();
	 cout<<"*";
	 pass[i]=x;
	 i++;
	 }
	 while(x!=13);
	 pass[i-1]='\0';
	 if(strcmp(pass,"anuj")==0)

	 {cout<<"\n\ncorrect password";
	 cout<<"\n\nwelcome";
	 delay(1000);
	 amenu();
	 }
	 else
	 cout<<"wrong password";
	 break;

case '2':loading();
	 userm();
	 break;
case '3':exit(0);
	 break;
}}
while(ch!='3');
getch();
}