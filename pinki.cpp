#include <iostream> // library files
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

int orderCount = 0;
void productDetails(string productId[],string productName[] , string price[], int totalProducts);

string parseData(string line, int field);
void writeData(string userName[], string userPass[], string role[], int userCount);
void loadUserData(string userName[], string userPass[], string role[], int &userCount);
void loadProductData( string productId[],string productName[] , string price[], int totalProducts);
void writeProductData(string productId[],string productName[] , string price[], int totalProducts);

void gotoxy(int x, int y);
// HeaderSection
void welcomeHeader();
void header();           // prints Home page header
void signUpHeader();     // prints Sign Up page header
void signInHeader();     // print Sign In page Header
void collectionHeader(); // print collection page Header
void glasses();          // for making interface of Collection menu attractive

string getName();
string getPass();
bool nameCheck(string userName[], int userCount, string username, string ro); // checks if the user name already exists
bool passValid(string p);
string roleReturn(string userName[], string userPass[], string role[], string nam, string p, int userCount);
int IDreturn(string userName[], string userPass[], string role[], int userCount, string nameToCheck, string passToCheck);

string displayCusMenu(string productName[], string price[]); // CustomerSection
void viewCollection(string userName[], string userPass[], int userCount, string productId[], string productName[], string price[]);
void placeOrder(string productId[], string productName[], string price[]);
void customerReview(string cusR[], int reviewNo, int r);
void changePass(string userName[], string userPass[], int userCount, string nameToCheck, string role[]);

string displayWorkerMenu(); // WorkerSection
void deleteProduct(int totalProducts, string productId[], string productName[], string price[]);
void ordersPlaced();
void cusDetail(string userName[], string userPass[], string role[], int userCount);

bool ownerCheck(string inCode, string vCode); // AdminSection
string displayAdminMenu();
void workerDetail(string userName[], string userPass[], string role[], int userCount);
string changeVerCode(string vCode, string inCode);

int main()
{
    string name, nameToCheck = "o", pass, ro, p;
    string nam, pas, j = "0", cusChoice = "0";
    string inCode;
    string vCode = "admin"; // admin verification code

    int userCount = 0, r = 0;
    int totalProducts = 20;
    int reviewNo = 100;

    string userName[100];
    string userPass[100];
    string role[100];
    string productName[totalProducts];
    string productId[totalProducts];
    string price[totalProducts];
    string cusR[reviewNo];
    productDetails( productId, productName ,  price,  totalProducts);
    string line;
    int field;
    loadUserData(userName, userPass, role, userCount);
    
    loadProductData( productId, productName, price, totalProducts);

    
    while (true)
    {
        system("cls");
        welcomeHeader();
        header();
        string choice; // choice is the very first option selected by user determining if he want to sign up, sign in or exit
        string username;
        cout << "\t\tEnter your choice:     1- Sign Up     2- Sign In      3- Exit \e[0m" << endl;
        cin >> choice;
        if (choice == "1") // signUp
        {

            system("cls");
            signUpHeader();
            while (true) /*check if user name already exists*/
            {
                username = getName();
                if (nameCheck(userName, userCount, username, ro))
                {
                    break;
                }
                else
                {
                    cout << "\e[1;31m";
                    cout << "This user name already exists. Try again." << endl;
                    cout << "\e[0m";
                }
            }

            while (true) // password validation
            {
                p = getPass();
                if (passValid(p))
                {
                    break;
                }
                else
                {
                    cout << "\e[1;31m";
                    cout << "Invalid password\n";
                    cout << "\e[0m";
                }
            }

            cout << "Enter your Role (Customer, Worker or Admin): ";
            cin >> ro;

            role[userCount] = ro;
            userName[userCount] = username;
            userPass[userCount] = p;
            cout << "Successfull Sign Up";
            userCount++;
            writeData(userName, userPass, role, userCount);
            getch();
        }
        else if (choice == "2") // signIn
        {
            system("cls");
            signInHeader();

            cout << "Enter Username: ";
            cin >> nam;
            cout << "Enter Password: ";
            cin >> pas;

            /*j equals role returned by signIn function*/
            int a = IDreturn(userName, userPass, role, userCount, nam, pas);
            j = role[a];

            if (j == "custome0r" || j == "customer" || j == "Customer" || j == "CUSTOMER")
            {
                while (true)
                {
                    cusChoice = displayCusMenu(productName, price);
                    if (cusChoice == "1")
                    {
                        while (true)
                        {
                            char exit;
                            system("cls");
                            collectionHeader();
                            viewCollection(userName, userPass, userCount, productId, productName, price);
                            cout << "Enter 0 to go back   ";
                            cin >> exit;
                            if (exit == '0')
                                break;
                        }
                    }
                    if (cusChoice == "2")
                    {
                        placeOrder(productId, productName, price);
                    }
                    if (cusChoice == "3")
                    {
                        customerReview(cusR, reviewNo, r);
                    }
                    if (cusChoice == "4")
                    {
                        changePass(userName, userPass, userCount, nameToCheck, role);
                        writeData(userName, userPass, role, userCount);
                    }
                    if (cusChoice == "5")
                    {
                        break;
                    }
                }
            }
            else if (j == "worker" || j == "Worker")
            {
                string workerChoice = displayWorkerMenu();
                if (workerChoice == "1")
                {
                    deleteProduct(totalProducts, productId, productName, price);
                }
                if (workerChoice == "2")
                {
                     while (true)
                        {
                            system("cls");
                            collectionHeader();
                            char ex;
                            viewCollection(userName, userPass, userCount, productId, productName, price);
                            cout << "Enter 0 to go back   ";
                            cin >> ex;
                            if (ex == '0')
                                break;
                        }
                }
                if (workerChoice == "3")
                {
                    cusDetail(userName, userPass, role, userCount);
                }
            }
            else if (j == "Admin" || j == "admin")
            {

                cout << "Enter Verification Code: ";
                cin >> inCode;
                if (ownerCheck(inCode, vCode))
                {
                    string adminchoice = displayAdminMenu();
                    if (adminchoice == "1")
                    {
                        while (true)
                        { 
                            system("cls");
                            collectionHeader();
                            char ex;
                            viewCollection(userName, userPass, userCount, productId, productName, price);
                            cout << "Enter 0 to go back   ";
                            cin >> ex;
                            if (ex == '0')
                                break;
                        }
                    }
                    else if (adminchoice == "2")
                    {
                        deleteProduct(totalProducts, productId, productName, price);
                        writeProductData( productId, productName ,  price,  totalProducts);

                    }
                    else if (adminchoice == "3")
                    {
                        ordersPlaced();
                    }
                    else if (adminchoice == "4")
                    {
                        workerDetail(userName, userPass, role, userCount);
                    }
                    else if (adminchoice == "5")
                    {
                        vCode = changeVerCode(vCode, inCode);
                    }

                    else
                    {
                        cout << "Invalid Option.";
                        getch();
                    }
                }
                else
                {
                    cout << "\e[1;31m";
                    cout << "Wrong Credentials! \n TRY AGAIN \n\n";
                    cout << "press any key to continue";
                    getch;
                }
            }
            else
            {
                cout << "\e[1;31m";
                cout << " \t \" Invalid Credentials \" " << endl
                     << "     Press Enter key to Continue.";
                getch();
            }
        }

        else if (choice == "3") // exit
        {
            break;
        }
        else
        {
            cout << "Invalid input";
        }
    }
}
string getName()
{
    string name;
    cout << "Enter your name: ";
    getline(cin >> ws, name);
    return name;
}
string getPass()
{
    string pass;
    char ch;
    cout << "Enter your password (must be six to 14 characters long):  ";

    while (true)
    {
        ch = _getch(); // Read a single character without displaying it
        if (ch == 13)  // Check for Enter key
            break;
        else if (ch == 8) // Check for Backspace key
        {
            if (!pass.empty())
            {
                cout << "\b \b"; // Move the cursor back, erase the character, move back again
                pass.pop_back(); // Remove the last character from the password
            }
        }
        else
        {
            pass += ch;  // Append the character to the password
            cout << '*'; // Display '*' for each character
        }
    }

    cout << endl
         << "Password entered: " << pass << endl;

    return pass;
}

bool nameCheck(string userName[], int userCount, string username, string ro)
{
    bool i = true;
    for (int x = 0; x < userCount; x++)
    {
        if (username == userName[x])
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
bool passValid(string p)
{
    bool pC = false;
    int pLength = p.length();
    if (pLength > 5 && pLength < 15)
    {
        pC = true;
    }
    return pC;
}

/// @brief
/// @param userName
/// @param userPass
/// @param role
/// @param pas
/// @param nam
/// @param userCount
/// @param ro
/// @return
string roleReturn(string userName[], string userPass[], string role[], string nam, string p, int userCount) // returnsRole
{
    string no = "noMatch";
    string r;

    for (int x = 0; x < userCount; x++)
    {
        if (nam == userName[x] && p == userPass[x])
        {
            r = role[x];
            break;
        }
        else
        {
            r = no;
        }
    }
    return r;
}
int IDreturn(string userName[], string userPass[], string role[], int userCount, string nameToCheck, string passToCheck)
{
    int r;

    for (int x = 0; x < userCount; x++)
    {

        if (nameToCheck == userName[x] && passToCheck == userPass[x])
        {
            r = x;
            break;
        }
        else
        {
            r = -1;
        }
    }
    return r;
}

string displayCusMenu(string productName[], string price[])
{
    string viewChoice;

        system("cls");
    cout << endl
         << endl;
    cout << "\e[1;33m";
    cout << "\t~~~~~~~~~~~~~~~~~~~~\n\n";
    cout << "\t***CUSTOMER MENU***" << endl << endl;
    cout << "\t~~~~~~~~~~~~~~~~~~~~\n\n\n";
    cout << "\tEnter: " << endl
         << "         1 to view Collection" << endl
         << "         2 to place Order" << endl
         << "         3 to give Customer Review" << endl
         << "         4 to reset password\n"
         << "         5 to EXIT\n\n         ";

    cin >> viewChoice;
    return viewChoice;
}
void viewCollection(string userName[], string userPass[], int userCount, string productId[], string productName[], string price[])
{
    system("cls");
    collectionHeader();
    glasses();
    cout << "Product ID\t\t\t\tProduct name\t\t\t\tProduct Price\n\n";
    for (int x = 0; x < 20; x++)
    {
        cout << x << "\t\t\t\t\t" << productName[x] << "\t\t\t\t\t" << price[x] << endl;
    }
}
void placeOrder(string productId[], string productName[], string price[])
{
    while (true)
    {
        string orderId, discountCode = "0", orderChoice;

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
            cout << "Your Order has been placed \n Thank you!\n\n";
            orderCount++;
            cout << "your order ID is: " << orderCount;
            getch();
            break;
        }
        if (orderChoice == "2")
        {
            break;
        }
    }
}
void changePass(string userName[], string userPass[], int userCount, string nameToCheck, string role[])
{
    string pass;
    string currentPass;
    string n;
    cout << "Enter your name: ";
    cin >> n;
    cout << "Enter your current password: ";
    cin >> currentPass;
    int idx = IDreturn(userName, userPass, role, userCount, n, currentPass);
    if (currentPass == userPass[idx])
    {
        while (true)
        {

            cout << "Enter New password: ";
            cin >> pass;
            if (passValid(pass) == true)
            {
                userPass[idx] = pass;
                cout << "password updated successfully\nPress any key to continue.";
                cout << "\e[0m";
                getch();
                break;
            }
            else
            {
                cout << "\e[1;31m";
                cout << "Invalid password\n";
                cout << "\e[0m";
            }
        }
    }
    else
    {
        cout << "\e[1;31m";
        cout << "Password did not match.\nPress any key to continue.";
        cout << "\e[0m";
        getch();
    }
}
void deleteProduct(int totalProducts, string productId[], string productName[], string price[])
{

    int found = 0;
    string t_id = "0";
    cout << "\n\n ENTER Product ID TO DELETE -> ";
    cin >> t_id;
    for (int a = 0; a < totalProducts; a++)
    {

        if (t_id == productId[a])
        {

            for (int k = a; k < 20; k++)
            {
                productId[k] = productId[k + 1];
                productName[k] = productName[k + 1];
                price[k] = price[k + 1];
            }

            totalProducts--;
            cout << "\n\n *** PRODUCT DELETED SUCCESSFULLY ***";
        }
        found++;
    }
    if (found == 0)
    {
        cout << "No match";
    }
    getch();
}

string displayWorkerMenu()
{
    string workerChoice;
    cout << "Enter:      1 Delete Product       2 to view Collection    3 to view Customers Detail    ";
    cin >> workerChoice;
    return workerChoice;
}
void cusDetail(string userName[], string userPass[], string role[], int userCount)
{
    cout << "User ID\t\t\tUser Name\t\t\tUser Password" << endl
         << endl;
    for (int x = 0; x < userCount; x++)
    {
        if (role[x] == "custome0r" || role[x] == "customer")
        {
            cout << x + 1 << "\t\t\t" << userName[x] << "\t\t\t" << userPass[x] << endl;
        }
    }
    getch();
}
void workerDetail(string userName[], string userPass[], string role[], int userCount)
{
    int workerCount = 0;
    cout << "Worker ID\t\t\tWorker Name\t\t\tWorker Password" << endl
         << endl;
    for (int x = 0; x < userCount; x++)
    {
        if (role[x] == "worker" || role[x] == "Worker")
        {
            cout << x + 1 << "\t\t\t" << userName[x] << "\t\t\t" << userPass[x] << endl;
            workerCount++;
        }
    }
    if (workerCount == 0)
    {
        cout << "no worker to display" << endl;
    }
    cout << "Total number of Workers: " << workerCount;
    getch();
}

bool ownerCheck(string inCode, string vCode)
{
    bool c = false;
    {
        if (inCode == vCode)
        {
            c = true;
        }
    }
    return c;
}

string displayAdminMenu() // gives different options to admin to access different functionalities
{
    cout << "\e[0;32m";
    string adminChoice;
    cout << endl
         << endl
         << endl;
    cout << "***ADMIN MENU***" << endl
         << endl;
    cout << "Enter your choice: " << endl;
    cout << "1 to view Collection " << endl;
    cout << "2 to delete product " << endl;
    cout << "3 to view number of Orders placed " << endl;
    cout << "4 to view details of Workers " << endl;
    cout << "5 to change  " << endl;
    cin.ignore();
    getline(cin, adminChoice);
    return adminChoice;
}
void ordersPlaced() // displayes the total number of orders placed
{
    cout << "The number of orders Placed is: " << orderCount;
    getch();
}
void customerReview(string cusR[], int reviewNo, int r) // takes review from customer and saves in an array of customer reviews(cusR())
{
    cout << "Enter your review: ";

    getline(cin >> ws, cusR[r]);
    r++;
    cout << "your review has been submitted. Thank You!";
    getch();
}
string changeVerCode(string vCode, string inCode)
{
    string tcode, newCode = "0"; // temporary code for checking
    cout << "Enter current Verification code: ";
    cin >> tcode;
    if (tcode == vCode)
    {
        cout << "Enter New Admin Verification code (at least 5 characters long): ";
        cin >> newCode;
        if (newCode.length() > 4)
        {
            vCode = newCode;
            cout << "Code updated Successfully\n press any key to continue ";
            getch();
        }
        else
        {
            cout << "Invalid code! \npress any key to continue ";
            getch();
        }
    }
    else
    {
        cout << "invalid";
        getch();
    }
    return vCode;
}
string parseData(string line, int field)
{
    string item;
    int commaCount = 1;
    int length = line.length();
    for (int i = 0; i < length; i++)
    {
        if (line[i] == ',')
        {
            commaCount++;
        }
        else if (field == commaCount)
        {
            item = item + line[i];
        }
    }
    return item;
}
void loadUserData(string userName[], string userPass[], string role[], int &userCount)
{
    string line;
    fstream file;
    file.open("file.txt", ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            // cout << line << endl;

            string Name = parseData(line, 1);
            string Pass = parseData(line, 2);
            string role1 = parseData(line, 3);
             userName[userCount] = Name;
             userPass[userCount] = Pass;
             role[userCount] =role1 ;
            userCount++;

        }
    }
}
void writeData(string userName[], string userPass[], string role[], int userCount)
{
    fstream file;
    file.open("file.txt", ios::out);
    if (file.is_open())
    {
        for (int i = 0; i < userCount; i++)
        {
            file << userName[i] << "," << userPass[i] << "," << role[i] << endl;
        }
    }
    file.close();
}
void loadProductData( string productId[],string productName[] , string price[], int totalProducts)
{
      string line;
    fstream file;
    file.open("productData.txt", ios::in);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            // cout << line << endl;

            string Name = parseData(line, 1);
            string pric = parseData(line, 2);
            
             productName[totalProducts] = Name;
             price[totalProducts] = pric;
             
            totalProducts++;

        }
    }
}
void writeProductData(string productId[],string productName[] , string price[], int totalProducts)
{
    fstream file;
    file.open("productData.txt", ios::out);
    if (file.is_open())
    {
        for (int i = 0; i < totalProducts; i++)
        {
            file << productName[i] << "," << price[i] << "," << endl;
        }
    }
    file.close();
}

void welcomeHeader() // prints Home page header
{
    cout << endl;
    cout << "\e[1;33m \t\t\t\t\t__        __   _                               _____  " << endl;
    cout << "\t\t\t\t\t\\ \\      / /__| | ___ ___  _ __ ___   ___     |_   _|__ " << endl;
    cout << "\t\t\t\t\t \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\      | |/ _ \\ " << endl;
    cout << "\t\t\t\t\t  \\ V  V /  __/ | (_| (_) | | | | | |  __/      | | (_) |" << endl;
    cout << "\t\t\t\t\t   \\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|      |_|\\___/ " << endl;
    cout << endl;
    cout << endl;
}
void header()
{
    cout << "\e[0;36m ";

    cout << "\t\t\t  ___    ___   ___  ____  __   __    ___   ____  __  ____  __      ____ __  __ ______ __   ___  ____" << endl;
    cout << "\t\t\t // \\\\  //    //   ||    (( \\ (( \\  // \\\\  || \\\\ || ||    (( \\    ||    ||\\ || | || | ||  //   ||   " << endl;
    cout << "\t\t\t ||=|| ((    ((    ||==   \\\\   \\\\  ((   )) ||_// || ||==   \\\\     ||==  ||\\\\||   ||   || ((    ||== " << endl;
    cout << "\t\t\t || ||  \\\\__  \\\\__ ||___ \\_)) \\_))  \\\\_//  || \\\\ || ||___ \\_))    ||___ || \\||   ||   ||  \\\\__ ||___" << endl;

    cout << endl
         << endl
         << endl
         << endl;
}

void signUpHeader()
{
    cout << "";
    cout << " __ _                                                       " << endl;
    cout << "/ _(_) __ _ _ __    /\\ /\\ _ __       /\\/\\   ___ _ __  _   _ " << endl;
    cout << "\\ \\| |/ _` | '_ \\  / / \\ \\ '_ \\     /    \\ / _ \\ '_ \\| | | |" << endl;
    cout << "_\\ \\ | (_| | | | | \\ \\_/ / |_) |   / /\\/\\ \\  __/ | | | |_| |" << endl;
    cout << "\\__/_|\\__, |_| |_|  \\___/| .__/    \\/    \\/\\___|_| |_|\\__,_|" << endl;
    cout << "      |___/              |_|         " << endl
         << endl
         << endl;
}
void signInHeader()
{
    cout << " ___  _             _            __ __                " << endl;
    cout << "/ __><_> ___ ._ _  | |._ _      |  \\  \\ ___ ._ _  _ _ " << endl;
    cout << "\\__ \\| |/ . || ' | | || ' |     |     |/ ._>| ' || | |" << endl;
    cout << "<___/|_|\\_. ||_|_| |_||_|_|     |_|_|_|\\___.|_|_|`___|" << endl;
    cout << "        <___'                                         " << endl;
}
void collectionHeader()
{

    cout << "   ____   U  ___ u   _       _     U _____ u   ____   _____             U  ___ u  _   _   " << endl;
    cout << "U /\"___|   \\/\"_ \\/  |\"|     |\"|    \\| ___\"|/U \"___| |_ \" _|     ___     \\/\"_ \\/ | \\ |\"|    " << endl;
    cout << "\\| | u     | | | |U | | u U | | u   |  _|\"  \\| | u     | |      |_\"_|    | | | |<|  \\| |>   " << endl;
    cout << " | |/__.-,_| |_| | \\| |/__ \\| |/__  | |___   | |/__   /| |\\      | | .-,_| |_| |U| |\\  |u   " << endl;
    cout << "  \\____|\\_)-\\___/   |_____| |_____| |_____|   \\____| u |_|U    U/| |\\u\\_)-\\___/  |_| \\_|    " << endl;
    cout << " _// \\      \\     //  \\  //  \\  <<   >>  _// \\  _// \\_.-,_|___|_,-.  \\    ||   \\,-. " << endl;
    cout << "(__)(__)    (__)   (_\")(\"_)(_\")(\"_)(__) (__)(__)(__)(__) (__)\\_)-' '-(_/  (__)   (_\")  (_/  " << endl;
}
void glasses()
{
    cout << "\e[0;35m ";
    gotoxy(120, 5);
    cout << "    __         __" << endl;
    gotoxy(120, 6);
    cout << "   /.-'       `-.\\" << endl;
    gotoxy(120, 7);
    cout << "  //             \\\\" << endl;
    gotoxy(120, 8);
    cout << " /j_______________j\\" << endl;
    gotoxy(120, 9);
    cout << "/o.-==-. .-. .-==-.o\\" << endl;
    gotoxy(120, 10);
    cout << "||      )) ((      ||" << endl;
    gotoxy(120, 11);
    cout << " \\\\____//   \\\\____// " << endl;
    gotoxy(120, 12);
    cout << "  `-==-'     `-==-'" << endl;
}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void productDetails(string productId[],string productName[] , string price[], int totalProducts)
{
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
     productId[0] = "1";
    productId[1] = "2";
    productId[2] = "3";
    productId[3] = "4";
    productId[4] = "5";

}