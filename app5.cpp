#include <iostream>
#include<conio.h>
using namespace std;
void printHeader();
void Login(int choice);
void displayCusMenu();
void  displayWorkerMenu();
string userName[100];
string userPass[100];
string role[100];
int userCount=0;

int main()
{
     while(true)
{
    system("cls");
    printHeader();
    cout <<  "Enter your choice:     1- Sign Up     2- Sign In      3- Exit"; 
    int choice;
    cin >> choice;
    Login( choice);
    if(choice==3)
    break;
}
}
void Login(int choice)
{ 
       
 
    if (choice==1)
    {
        cout << "Enter Username: " ;
        cin >> userName[userCount];
        cout << "Enter Password: ";
        cin >> userPass[userCount];
        cout<< "Enter Role(customer,worker or owner): ";
        cin>> role[userCount];
        userCount++;
        
    }
    if(choice==2)
    {
        string name,ro;
        string pass;
        cout << "Enter Username: " ;
        cin >> name;
        cout << "Enter Password: ";
        cin >> pass;
        cout<< "Enter your Role: ";
        cin>>ro;
        for(int x=0; x<userCount; x++)
        {   
            cout << userName[x] << " " << userPass[x] << endl;
            if(pass==userPass[x] && name==userName[x])
            {
            cout << "successful LOGIN.";
            if(role[x]=="customer")
            {
                displayCusMenu();
            }
           
            break;
            }
        }
            getch();
    }
     
 }

void  displayCusMenu()
{
    int cusChoice;
   int  viewChoice;
    cout << "Enter: " <<endl<<"     1 to view Men Collection"<<endl<<"      2 to view Women Collection";
    cin >> viewChoice;
    if (viewChoice==1)
    {
        cout << "1- Watches" << endl << "2- Belts" << endl << "3- Rings"<< endl;
        cin >> cusChoice;
    }
    if(viewChoice==2)
    {
         cout << "1- Watches" << endl << "2- Necklaces" << endl << "3- Rings"<< endl << "4- Earings"<< endl;
         cin>> cusChoice;
    }
}

/// @brief 
void  displayWorkerMenu()
{
    cout<< "Enter: ";


}

void printHeader() 
{
system ("color 80");
cout << endl;
cout << "               ##  #  ## ####  #    ###  ###  ##  ## ####    #####  ###               "<< endl;
cout << "                # # # #  #---  #   ##   #   # # ## # #---      #   #   #          "<< endl;
cout << "                 ## ##   ####  #### ###  ###  #    # ####      #    ###                         "<< endl;
cout<<endl;
cout<<endl;


cout << "  ####      ## ##     ## ##  #####   ####     ####    ####   ####   #   #####    #####         #####   ##      #  #######   #    ####  #####         " << endl;
cout << " ##  ##   ##        ##       ##      ##      ##      ##   ## #   #  #   #       ##             #       #  #    #     #      #   #      #               " << endl;
cout << " ######  ##        ##        #####     ##      ##    ##   ## ####   #   ####      ##           ####    #   #   #     #      #  #       ####         " << endl;
cout << " ##  ##   ##        ##       ##          ##      ##  ##   ## #  #   #   #           ##         #       #     # #     #      #   #      #              " << endl;
cout << " ##  ##     ## ##     ## ##  #####  #####    #####    ####   #   #  #   #####   #####          #####   #      ##     #      #    ####  #####   " << endl<< endl<< endl;
}