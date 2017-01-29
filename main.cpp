
//The following code has been written in Code::blocks 16.01

#include<iostream>
#include<map>
#include<string>
#include<ctime>
#include<stdio.h>
#include<stdlib.h>
#include"windows.h"
#include<utility>
#include<iomanip>
#include<vector>
#include<fstream>
using namespace std;

ostream & indian_rupee(ostream & output){
    output<<"\u20B9 ";
    return output;
   }

//Positioning Cursor Location on Output Window

void gotoxy(int x,int y){
COORD coord;
coord.X=x;
coord.Y=y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);

}

           /** Class NEW is responsible for the contents of Invoice
             * Class ITEMS is responsible for the contents of the Items list*/

class NEW; //predeclaration
class ITEMS{
string items;
//int item_id; Making this public is a temporary workaround for deleting items
//I want to incorporate deletion using destructors
int item_price;
map<int, pair<string,int> > mapitem;
pair<string,int> p;

public:
    int item_id;
    void update_item(string,int,int);
    void deleteitem(int);
    void displayitemlist(int);
    void updated_message();// A message when new item is inserted
    friend NEW;
};


void ITEMS::update_item(string a,int b,int i)
{
 p.first=items=a;
 p.second=item_price=b;
 item_id=i;
 mapitem[item_id]=p;
}

void ITEMS::deleteitem(int del){

    cout<<"Item "<<mapitem[del].first<<"id "<<del<<" Deleted !!!"<<endl;
    item_id=0;
    system("pause");
}

void ITEMS::displayitemlist(int num){

cout.setf(ios::left,ios::adjustfield);
cout<<setw(3)<<num<<" "<<setw(19)<<mapitem[num].first<<"\t"<<indian_rupee<<mapitem[num].second<<endl;
}

void ITEMS:: updated_message(){
        system("cls");
        int x=30,y=2;
        gotoxy(x,y++);
        cout<<"Item "<<items<<" updated!!! with id "<<item_id<<endl;
        gotoxy(x,y++);
        cout<<"To Enter more items press 'y' else press any other button ";
}

class NEW{

int id,sum;

pair<int,int> order;//pair of item_id and quantity
vector< pair<int,int> > order_list;//vector of the above pair
map<int,int> invoice_summary; //maps the invoice_id and total price

 public:
    void getdata(int,ITEMS[],int);
    void display(int,ITEMS[]);
    void generate_invoice(int,ITEMS[]);
};

void NEW::getdata(int fid,ITEMS C[],int id){
    system("cls");
     int x=35,y=2,buy,quantity;
     sum=0;
     gotoxy(x,y++);


    /**Displays Item list while creating invoice
      *so that user only enters the id instead of
      *typing the full name for generating the
      *invoice*/

    cout<<"Item List"<<endl;
    gotoxy(x,y++);
    cout.setf(ios::left,ios::adjustfield);
    cout<<"Id  "<<setw(19)<<"Item-Name"<<"\t"<<"Price"<<endl;
    for(int j=1;j<=fid;j++){
    gotoxy(x,y++);
    if(C[j].item_id)
    C[j].displayitemlist(j);}
    char ch='y';


    do{
    gotoxy(x,y++);
    cout<<"Enter id of the item ";
    cin>>buy;
    gotoxy(x,y++);
    cout<<"Enter Quantity ";
    cin>>quantity;

    sum+=C[buy].item_price*quantity;
    order.first=buy;
    order.second=quantity;
    order_list.push_back(order);

    gotoxy(x,y++);
    cout<<"To continue press y "<<endl;
    gotoxy(x,y++);
    cin>>ch;
    }while((ch=='y')||(ch=='Y'));


    invoice_summary[id]=sum;
    gotoxy(x,y++);
    cout<<"Total price "<<sum;
    gotoxy(x,y++);
    system("pause");
}

//Displays invoice in the Window
void NEW::display(int id, ITEMS C[]){
   system("cls");
   int x=10,y=2;

   gotoxy(x,y++);
   cout<<"INVOICE";
   y+=2;
   gotoxy(x,y++);
   cout<<"S.No \t"<<setw(15)<<"Product-id "<<setw(20)<<"Item-name"<<setw(20)<<"Quantity"<<setw(20)<<"Price"<<setw(20)<<"Total"<<endl;
   for(unsigned int i=0;i<order_list.size();++i){
   gotoxy(x,y++);
   cout.setf(ios::left,ios::adjustfield);
   cout<<i+1<<"\t"<<setw(15)<<C[order_list[i].first].item_id<<setw(20)<<C[order_list[i].first].items<<setw(20)<<order_list[i].second<<setw(20)<<C[order_list[i].first].item_price<<setw(20)<<(order_list[i].second)*(C[order_list[i].first].item_price)<<endl;
   }
   y+=2;
   gotoxy(45,y++);
   cout<<"Total: "<<indian_rupee<<sum<<endl;
   gotoxy(x,y++);
   system("pause");
}

//Generates invoice in text format
void NEW::generate_invoice(int id,ITEMS C[]){
      ofstream file;
      file.open("Invoice.TXT",ios::ate|ios::trunc|ios::out);
      file<<"\t\t\t\tINVOICE"<<endl<<endl;

      time_t current=time(0);
      file<<"\t\t\t"<<ctime(&current)<<endl<<endl;

      file.setf(ios::left,ios::adjustfield);
      file<<"S.No \t"<<setw(15)<<"Product-id "<<setw(20)<<"Item-name"<<setw(20)<<"Quantity"<<setw(20)<<"Price"<<setw(20)<<"Net Price of item"<<endl<<endl;

   for(unsigned int i=0;i<order_list.size();++i){
   file.setf(ios::left,ios::adjustfield);
   file<<i+1<<"\t"<<setw(15)<<C[order_list[i].first].item_id<<setw(20)<<C[order_list[i].first].items<<setw(20)<<order_list[i].second<<indian_rupee<<setw(20)<<C[order_list[i].first].item_price<<indian_rupee<<setw(20)<<(order_list[i].second)*(C[order_list[i].first].item_price)<<endl;
   }

   file<<endl<<endl<<"\t\t\t\t\t\t\t\t\tTotal: "<<indian_rupee<<sum<<endl<<endl;
   file<<"Terms and Conditions"<<endl;
      file<<"1. All disputes are to be solved within the jurisdiction of Delhi"<<endl;
      file<<"2. Defective items need to be returned within 3 days of purchase"<<endl;

      file.close();
}


int main()
{   NEW N[100];
    ITEMS C[100];
    //Here id resembles the invoice id
    //     fid resembles the id for the items
    int id=0,fid=0;
    int x,y,ch;


    do{
      system("cls");
        x=35,y=2;
     gotoxy(x,y++);
    cout<<"Invoice Generator system"<<" "<<endl;
    gotoxy(x,y++);
    cout<<"1. Create Invoice"<<endl;
    gotoxy(x,y++);
    cout<<"2. Display Invoice"<<endl;
    gotoxy(x,y++);
    cout<<"3. Generate Invoice"<<endl;
    gotoxy(x,y++);
    cout<<"4. Item-list Menu"<<endl;
    gotoxy(x,y++);
    cout<<"5. Exit"<<endl;
    gotoxy(x,y++);



    cin>>ch;

        switch(ch)
        {
            case 1: {
                     id++;
                     N[id].getdata(fid,C,id);
                    }
                    break;
            case 2:{
                      int i;
                      system("cls");
                      x=30,y=2;
                      gotoxy(x,y++);
                      cout<<"Enter invoice id"<<endl;
                      gotoxy(x,y++);
                      cin>>i;
                      N[i].display(i,C);
                    }
                   break;
            case 3:{
                      int i;
                      system("cls");
                      x=30,y=2;
                      gotoxy(x,y++);
                      cout<<"Enter invoice id"<<endl;
                      gotoxy(x,y++);
                      cin>>i;
                      N[i].generate_invoice(i,C);
                       }
                   break;
            case 4:{ system("cls");
                      x=20,y=2;
                      int item_ch;
                      gotoxy(x,y++);
                     cout<<"1. Display Item-list"<<endl;
                     gotoxy(x,y++);
                     cout<<"2. Insert new items"<<endl;
                     gotoxy(x,y++);
                     cout<<"3. Delete items"<<endl;
                     gotoxy(x,y++);
                     cin>>item_ch;

                     /** My file handling here is pretty messed up

                       * I want the Items list
                       * to be stored in an external file so that
                       * I can retrieve it for generating the invoice.

                       * I am unable to do so as I my program stops
                       * functioning when I do so(that's the reason why
                       * I introduced ios::trunc filemode on line 329 )

                       * With the current code I have to create Item list
                       * i.e. inserting all the items again
                       * for each time I run the program so as to generate
                       * the invoice

                       */

                     if(item_ch==1)
                    {    system("cls");
                            x=30,y=2;
                               gotoxy(x,y++);


                               if(fid==0)
                                {cout<<" Item List is empty "<<endl;
                                system("pause");}
                               else
                               {

                              cout<<"Item List is"<<endl;
                              gotoxy(x,y++);
                              cout.setf(ios::left,ios::adjustfield);
                              cout<<"Id  "<<setw(19)<<setfill(' ')<<"Item-Name"<<"\tPrice"<<endl;
                            fstream fil;
                            fil.open("Items.TXT",ios::in);


                                for(int j=1;j<=fid;j++){
                                fil.read((char*)&C[j],sizeof(C[j]));

                                gotoxy(x,y++);
                                if(C[j].item_id)
                                 C[j].displayitemlist(j);}

                              fil.close();
                              gotoxy(x,y++);
                              system("pause");
                        }

                     }

                     if(item_ch==2){

                              char new_ch='y';
                              fstream fil;

                              do{
                            system("cls");
                              x=30,y=2;
                                string new_name;
                                int price;
                                fid++;
                              fil.open("Items.TXT",ios::app|ios::ate|ios::trunc|ios::out);

                              gotoxy(x,y++);
                              cout<<"Enter New Item Name ";
                              cin>>new_name;

                              gotoxy(x,y++);
                              cout<<"Enter Price in Rupees ";
                              cin>>price;

                              C[fid].update_item(new_name,price,fid);

                              C[fid].updated_message();
                              cin>>new_ch;

                              fil.write((char*)&C[fid],sizeof(C[fid]));//input the contents
                              fil.close();

                              }while((new_ch=='y')||(new_ch=='Y'));
}
                              else if(item_ch==3){
                                system("cls");
                                x=30,y=2;
                                int del_prod_id;
                                gotoxy(x,y++);
                                cout<<"Enter product id ";
                                cin>>del_prod_id;
                                if(fid==0){
                                    cout<<"Empty Item list"<<endl;
                                    system("pause");

                                }else if(del_prod_id>fid){
                                    cout<<"Invalid product id "<<endl;
                                    system("pause");

                                }else{
                                  C[del_prod_id].deleteitem(del_prod_id);

                                }

                              }else
                              cout<<"Invalid Choice"<<endl;
                   }
                   break;

            case 5:
                     char exitproj;
                     system("cls");
                     x=40,y=5;
                     gotoxy(x,y++);
                     cout<<"Are you sure you want to exit "<<endl;
                     gotoxy(x,y++);
                     cout<<"Press 'y' for yes"<<endl;
                     gotoxy(x,y++);
                     cin>>exitproj;
                     if(exitproj=='y')
                        exit(0);
                     else
                        ch=0;


                      break;
            default: cout<<"Invalid Choice Press again to continue"<<endl;
                     break;
        }
     }while(ch!=5);

return 0;
}

