#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <sstream>

using namespace std;
void gotoxy(int x, int y);
void printHeader();
bool signUp(string userName[], int userCount, string name);
string signIn(string userName[], string userPass[], string role[], string pas, string nam, int userCount);
string displayCusMenu(string productName[], string price[]);
void viewCollection(string userName[], string userPass[], string role[], int userCount, string productId[], string productName[], string price[]);
void placeOrder(string productId[], string productName[], string price[]);
string displayWorkerMenu();
void deleteProduct(int productSize, string productId[], string productName[], string price[]);
bool adminVer(string vCode);

int main()
{
    string name, pass, ro;
    string nam, pas, j = "0", cusJ = "0";

    int userCount = 0;
    int productSize=20;
    string userName[100];
    string userPass[100];
    string role[100];
    string productName[productSize];
    string productId[productSize];
    string price[productSize];
    
    productId[0] = "1";
    productId[1] = "2";
    productId[2] = "3";
    productId[3] = "4";
    productId[4] = "5";

    while (true)
    {
        system("cls");
        printHeader();
        string choice;
        cout << "Enter your choice:     1- Sign Up     2- Sign In      3- Exit \e[0m" << endl;
        cin >> choice;
        if (choice == "1")
        {
            string username;
            cout << "Enter User Name: ";
            cin >> username;
            string password;
            cout << "Enter your password: ";
            cin >> password;
            cout << "Enter your Role: ";

            if (signUp(userName, userCount, name))
            {
                cin >> role[userCount];
                userName[userCount] = username;
                userPass[userCount] = password;
                cout << "Successfull Sign Up";
                userCount++;
            }
            else
            {
                cout << "invalid Username\n Try Again.";
                getch();
            }
        }
        if (choice == "2")
        {

            cout << "Enter Username: ";
            cin >> nam;
            cout << "Enter Password: ";
            cin >> pas;

            j = signIn(userName, userPass, role, pas, nam, userCount);

            if (j == "custome0r" || j == "customer" || j == "Customer" || j == "CUSTOMER")
            {

                cusJ = displayCusMenu(productName, price);
                if (cusJ == "1")
                {
                    viewCollection(userName, userPass, role, userCount, productId, productName, price);
                }
                if (cusJ == "2")
                {
                    placeOrder(productId, productName, price);
                }
                if (cusJ == "3")
                {
                    
                }
            }
            if (j == "worker" || j == "Worker")
            {
                string wC=displayWorkerMenu();
                if(wC=="1")
                {
                    deleteProduct( productSize,  productId,productName,  price);
                }
            }
            if(j=="Admin"||j=="admin")
            {
                string vCode;
                cout<<"Enter vrification code: ";
                cin>> vCode;
                
            }
            if (j == "noMatch")
            {
                cout << "\e[1;31m";
                cout << " \t \" Invalid Credentials \" " << endl
                     << "     Press Enter key to Continue.";
                getch();
            }
        }

        if (choice == "3")
            break;
    }
}

bool signUp(string userName[], int userCount, string name)
{
    bool i = true;
    for (int x = 0; x < userCount; x++)
    {
        if (name == userName[x])
        {
            i = false;
            break;
        }
        else
        {
            i = true;
        }
    }
    return i;
}

string signIn(string userName[], string userPass[], string role[], string pas, string nam, int userCount)
{
    string no = "noMatch";
    string r;
    for (int x = 0; x < userCount; x++)
    {
        if (pas == userPass[x] && nam == userName[x])
        {
            r = role[x];
        }
        else
        {
            r = no;
        }
    }
    return r;
}

string displayCusMenu(string productName[], string price[])
{
    string viewChoice;

    productName[0] = "Glasses";
    price[0] = "750";
    productName[1] = "Watches";
    price[1] = "230";
    productName[2] = "Rings";
    price[2] = "730";
    productName[3] = "Scarf";
    price[3] = "320";
    productName[4] = "Belts";
    price[4] = "730";

    cout << "Enter: " << endl
         << "     1 to view Collection" << endl
         << "     2 to place Order" << endl
         << "     3 to delete account" << endl
         << "     4 to give Customer Review\n\n";

    cin >> viewChoice;
    return viewChoice;
}
void viewCollection(string userName[], string userPass[], string role[], int userCount, string productId[], string productName[], string price[])
{

    cout << "Product ID\t\t\t\tProduct name\t\t\t\tProduct Price\n\n";
    for (int x = 0; x < 20; x++)
    {
        cout << x << "\t\t\t\t\t" << productName[x] << "\t\t\t\t\t" << price[x] << endl;
    }
    getch();
}
void placeOrder(string productId[], string productName[], string price[])
{
    while (true)
    {
        string orderId, discountCode = "0", orderChoice;
        int orderCount = 0;
        cout << "Enter the product ID (1 to 20): ";
        cin >> orderId;
        int k = stoi(orderId);
        int DPrice = stoi(price[k]);
        cout << "Enter discount code (if you have any): ";
        cin >> discountCode;
        if (discountCode == "code1")
        {
            DPrice = DPrice / 2;
        }
        cout << "Order Summary: \n";
        cout << "Product Id: " << orderId << endl;
        cout << "Product Name: " << productName[k] << endl;
        cout << "Product Price: " << DPrice << endl;
        cout << "Enter 1 to Confirm your Order or 2 to exit: " << endl;
        cin >> orderChoice;
        if (orderChoice == "1")
        {
            cout << "Your Order has been placed \n Thank you!";
            getch();
            orderCount++;

            break;
        }
        if (orderChoice == "2")
        {
            break;
        }
    }
}
void deleteProduct(int productSize, string productId[], string productName[], string price[])
{
   
         int t_id, found = 0;
       
        cout << "\n\n ENTER Product ID FOR DELETE -> ";
        cin >> t_id;
       for (int a = 0; a < productSize; a++)
        {
             int pI= stoi(productId[a]);
            if (t_id == pI)

            {

                for (int k = a; k < 20; k++)
                {
                    productId[k] = productId[k + 1];
                    productName[k] = productName[k+1];
                   price[k] = price[k+1];
                }

                productSize--;
                cout << "\n\n *** RECORD DELETE SUCCESSFULLY **";
            }
            found++;
        }
        if (found == 0)
        {
            cout<<"No match";
        }
    }

    string displayWorkerMenu()
    {
        string workerChoice;
        cout << "Enter:      1 Delete Product       2 to view Collection        ";
        cin >> workerChoice;
        return workerChoice;
    }

    bool adminVer(string vCode)
    {
        
    }

    void printHeader()
    {
        cout << endl;
        cout << "\e[1;33m \t__        __   _                               _____  " << endl;
        cout << "\t\\ \\      / /__| | ___ ___  _ __ ___   ___     |_   _|__ " << endl;
        cout << "\t \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\      | |/ _ \\ " << endl;
        cout << "\t  \\ V  V /  __/ | (_| (_) | | | | | |  __/      | | (_) |" << endl;
        cout << "\t   \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|      |_|\\___/ " << endl;
        cout << endl;
        cout << endl;

        cout << "\e[0;35m  ####      ## ##     ## ##  #####   ####     ####    ####   ####   #   #####    #####         #####   ##      #  #######   #    ####  #####         " << endl;
        cout << " ##  ##   ##        ##       ##      ##      ##      ##   ## #   #  #   #       ##             #       #  #    #     #      #   #      #               " << endl;
        cout << " ######  ##        ##        #####     ##      ##    ##   ## ####   #   ####      ##           ####    #   #   #     #      #  #       ####         " << endl;
        cout << " ##  ##   ##        ##       ##          ##      ##  ##   ## #  #   #   #           ##         #       #     # #     #      #   #      #              " << endl;
        cout << " ##  ##     ## ##     ## ##  #####  #####    #####    ####   #   #  #   #####   #####          #####   #      ##     #      #    ####  #####  \e[0;36m " << endl
             << endl
             << endl;
    }