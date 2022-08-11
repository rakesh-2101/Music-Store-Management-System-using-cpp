#include<iostream>
#include<cstdio>
#include<fstream>

using namespace std;

class music 
{
	int itemno;
	char category[50];
	char name[50];
	char artist[50];
	float price;
	int quantity;
	
public:
	void getdata()
	{
		cout << "\nPlease enter the item no.:\t";
		cin >>itemno;
		cout << "\nPlease enter the category of music:\t";
		cin >>category;
		cout << "\nPlease enter the name of music:\t";
		cin >>name;
		cout << "\nPlease enter the artist name of music:\t";
		cin >>artist;
		cout << "\nPlease enter the price of music:\t";
		cin >>price;
		cout << "\nPlease enter the quantity:\t";
		cin >>quantity;
		
	}
	
	
	void showdata()
	{
		cout <<"\n";
		cout << "Item No. : " <<itemno <<endl;
		cout << "Category :" <<category <<endl;
		cout << "Name of Music :" <<name <<endl;
		cout << "Artist Name :" <<artist <<endl;
		cout << "Price :" <<price <<endl;
		cout << "Quantity :" <<quantity <<endl;
	}
	
	
	int retitemno()
	{
		return itemno;
	}
	
	char* retcategory()
	{
		return category;
	}
	
	char* retname()
	{
		return name;
	}
	
	char* retartist()
	{
		return artist;
	}
	
	float retprice()
	{
		return price;
	}
	
	int retquantity()
	{
		return quantity;
	}
};

fstream f;
music m;

void write_to_file()
{
	f.open("musicstore.dat",ios::out|ios::app);
	m.getdata();
	f.write((char*)&m,sizeof(m));
	f.close();
	cout <<"Item has been inserted" <<endl;
	
}

void dispaly_all()
{
	cout << "******************************************************************ALL RECORDS*************************************************************************************\n";
	f.open("musicstore.dat",ios::in);
	while(f.read((char*)&m,sizeof(m)))
	{
		m.showdata();
		cout <<"\n\n";
		
	}
	
	f.close();
}


void display_sp(int n)
{
	int flag=0;
	f.open("musicstore.dat",ios::in);
	while(f.read((char*)&m,sizeof(m)))
	{
		if(m.retitemno()==n)
		{
			m.showdata();
			flag=1;
		}
	}
	f.close();
	if(flag==0)
	    cout <<"\n\nRecord does not exist\n\n";
}


void modify()
{
	cout << "******************************************************************MODIFY RECORD*************************************************************************************\n";
	int no,found=0;
	cout <<"\n\nPlease enter the item no. to modify\t";
	cin>>no;
	f.open("musicstore.dat",ios::in|ios::out);
	while(f.read((char*)&m,sizeof(m)) && found==0)
	{
		if(m.retitemno()==no)
		{
			m.showdata();
			cout <<"\nPlease enter the new details of the item\n"<<endl;
			m.getdata();
			int pos=-1*((int)sizeof(m));
			f.seekp(pos,ios::cur);
			f.write((char*)&m,sizeof(m));
			cout <<"\n\nRecord Updated";
			found=1;
		}
	}
	f.close();
	
	if(found==0)
	 {
	 	cout <<"\n\nRecord not found";
	 	
	  } 
	
}


void deleterec()
{
	
	int no;
	cout << "***************************************************************DELETE RECORD*************************************************************************************\n";
	cout <<"\n\nPlease enter the item no. of the item you want to delete\t";
	cin>>no;
	f.open("musicstore.dat",ios::in|ios::out);
	fstream f2;
	f2.open("temp.dat",ios::out);
	f.seekg(0,ios::beg);
	while(f.read((char*)&m,sizeof(m)))
	{
		if(m.retitemno()!=no)
		{
			f2.write((char*)&m,sizeof(m));
		}
	}
	
	f2.close();
	f.close();
	remove("musicstore.dat");
	rename("temp.dat","musicstore.dat");
	cout <<"\n\nRecord Deleted";
	
	
}


void menu()
{
	f.open("musicstore.dat",ios::in);
	if(!f)
	{
		cout <<"ERROR!!! FILE COULD NOT OPEN\n\n\n Go To Admin menu to create file";
		cout <<"\n\nProgram is closing ....";
		exit(0);
	}
	
	
	cout <<"\n\n\t\t ITEM MENU\n\n";
	cout <<"*****************************************************\n";
	cout <<"ITEM NO.\t\tNAME\t\t\tPRICE\n";
	cout <<"******************************************************\n";
	
	
	while(f.read((char*)&m,sizeof(m)))
	{
		cout <<m.retitemno()<<"\t\t\t"<<m.retname()<<"\t\t\t"<<m.retprice()<<endl;
	}
	
	f.close();
}

void admin_menu()
{   

    while(1){
	
	char ch1;
cout << "\n\n***************************************************************ADMIN RECORD*************************************************************************************\n";
	cout << "1.ADD ITEM" << endl;
	cout << "2.DISPLAY ALL ITEM" <<endl;
	cout << "3.FIND ITEM" << endl;
	cout << "4.MODIFY ITEM" <<endl;
	cout << "5.DELETE ITEM" <<endl;
	cout << "6.BACK TO MAIN MENU" <<endl;
	cout << "7.QUIT ADMIN MENU" <<endl<<endl;
	cout << "Please Enter Your Choice (1-7):\t";
	cin >>ch1;
	switch(ch1)
     {
		case '1' : write_to_file();
		            break;
		            
		case '2' : dispaly_all();
		           break;
		           
		case '3' : int num;
		           cout << "*********************************************************DISPLAYING SPECIFIC RECORD****************************************************************\n";
		           cout << "\n\nPlease enter the Item No.\t";
		           cin>>num;
		           display_sp(num);
		           break;
		           
		case '4' : modify();
		           break;
		           
		case '5' : deleterec();
		           break;
		           
		case '6' : menu();
		           break;
		           
		           
	    default : exit(0);
		           break;	           
	
	 }
	
	
    }
	
}


void place_order()
{
	int order_arr[50],quan[50],c=0;
	float amt,total=0;
	char ch='Y';
	menu();
	cout <<"\n******************************************";
	cout <<"\n  PLACE YOUR ORDER";
	cout <<"\n******************************************\n";
	do
	{
		cout <<"\n\nEnter the Item No. of item:\t";
		cin>>order_arr[c];
		cout <<"\nEnter the Quantity:\t";
		cin>>quan[c];
		c++;
		cout <<"\nDo You Want To Order Another Item ? (y/n)\t";
		cin>>ch;
		
	}while(ch=='y' ||ch=='Y');
	cout <<"\n\nThank You For Placing The Order";
	cout <<"\n\n**********************************************************INVOICE***********************************************\n";
	cout <<"\nItem No.\tName\tQuantity\tPrice\tAmount\n";
	for(int i=0;i<=c;i++)
	{
		f.open("musicstore.dat",ios::in);
		f.read((char*)&m,sizeof(m));
		while(!f.eof())
		{
			if(m.retitemno()==order_arr[i])
			{
			    if(m.retquantity()==0||quan[i]>m.retquantity())
				   cout <<"\nInvalid Quantity";
				   
				else
				{
				   amt=m.retprice()*quan[i];
				   cout <<"\n"<<order_arr[i]<<"\t"<<m.retname()<<"\t"<<quan[i]<<"\t"<<m.retprice()<<"\t"<<amt;
				   total+=amt;
				   	
				}	
			}
			
			f.read((char*)&m,sizeof(m));
		}
		
		f.close();
		
		
	}
	
	
	cout <<"\n\n\tTOTAL = "<<total;
}


int main() {
	
	char ch;
    cout << "\t\t\t\t\t\t\t\t\t\t\tWelcome To Music Store" << endl << endl;
   cout << "***************************************************************MAIN MENU*************************************************************************************\n";
    cout << "1.ADMINISTRATOR" << endl;
    cout << "2.CUSTOMER" << endl;
    cout << "3.EXIT" << endl;
   
    cout << "Please select your option (1-3):\t";
    cin >>ch;
    switch(ch)
    {
    	case '1' : admin_menu();
    	            break;
    	            
    	case '2' : place_order();
    	            break;
    	            
    	case '3' : exit(0);
    	            break;
	}
	return 0;
}
