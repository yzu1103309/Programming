#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

vector <string> users = {"12345", "98765"};
vector <string> passwd = {"54321", "56789"};
vector <float> available = {1000, 200};
vector <float> total = {1200, 200};
int remaining_bills = 500;

class account
{
public:
    void show_menu();
    account(size_t in){
        index = in;
    }

private:
    void view_balance();
    void withdraw();
    void deposit();
    size_t index;
};

int main()
{
    string account_in;
    string passwd_in;

    while(true)
    {
        size_t index = -1;
        cout << "Welcome!" << endl << endl ;
        cout << "Please enter your account number: ";
        cin >> account_in;
        cout << endl << "Enter your PIN: ";
        cin >> passwd_in;

        for(size_t t = 0; t < users.size(); t++){
            if(account_in == users[t]){
                if(passwd_in == passwd[t]){
                    index = t;
                }
            }
        }

        cout << endl;
        if(index == -1)
        {
            cout << "Wrong account number or wrong pin! Please retry." << endl << endl;
        }else
        {
            account current(index);
            current.show_menu();
        }
    }
}

void account::show_menu()
{
    int choice = -1;
    while(choice != 4){
        cout << "Main menu: "<<endl
             << "1 - View my balance" << endl
             << "2 - Withdraw cash" << endl
             << "3 - Deposit funds" <<endl
             << "4 - Exit " <<endl << endl
             << "Enter a choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                view_balance();
                break;
            case 2:
                withdraw();
                break;
            case 3:
                deposit();
                break;
            case 4:
                cout << "Exiting the system..."<< endl << endl;
                cout << "Thank you! Goodbye!"<< endl << endl;
                break;
            default:
                cout << "Invalid choice, Please retry" << endl << endl;
        }
    }
}

void account::view_balance()
{
    cout << endl << "Balance Information: " << endl << fixed << setprecision(2);
    cout  << " - Available balance: $" << available[index] << endl;
    cout << " - Total balance: $" << total[index] << endl << endl;
}

void account::withdraw()
{
    int bills[] = {0,1,2,3,5,10};
    int choice = -1;
    bool end_function;
    cout << endl;

    do
    {
        end_function = 1;

        cout << "Withdrawal options:" << endl
             << "1 - $20" << endl
             <<"2 - $40" << endl
             << "3 - $60" << endl
             << "4 - $100" << endl
             << "5 - $200" << endl
             << "6 - Cancel transaction" << endl << endl
             << "Choose a withdrawal option (1-6): ";

        cin >> choice;
        cout << endl;

        switch(choice)
        {
            case 6:
                cout << "Operation canceled." << endl;
                break;
            case 1: case 2: case 3: case 4: case 5:
            {
                int deduct_bills = bills[choice], deduct_dollars = bills[choice] * 20;
                if(deduct_dollars > available[index])
                {
                    cout << "The balance in your account is not enough to execute this operation! "<< endl;
                    (available[index] == 0)? cout<<"" :cout << "Please choose a lower amount! ", end_function = 0;
                    cout <<"(Your available balance: $" << available[index] << ")";
                }
                else if(deduct_bills > remaining_bills)
                {
                    cout << "There are not enough $20 bills to accomplish this operation!" << endl ;
                    if(remaining_bills == 0)
                        cout << "The machine has already run out of cash!";
                    else
                    {
                        cout << "Only " << remaining_bills << " $20";
                        (remaining_bills == 1)?cout << " bill is": cout << " bills are";
                        cout << " left in the machine.";
                        end_function = 0;
                    }
                }
                else
                {
                    available[index] -= deduct_dollars;
                    total[index] -= deduct_dollars;
                    remaining_bills -= deduct_bills;
                    cout << "Please take your cash from the cash dispenser." ;
                }
                cout << endl;
                break;
            }
            default:
                cout << "Invalid choice, Please retry.";
        }
        cout << endl;
    } while(!(1<=choice && choice<=6) || !end_function);
}

void account::deposit()
{
    float cents;
    cout << "Please enter a deposit amount in CENTS (or 0 to cancel): ";
    cin >> cents; cents /= 100;
    cout << endl << "Please insert a deposit envelope containing $"
    << cents << " in the deposit slot." << endl << endl;
    cout << "Your envelope has been received." << endl
    << "NOTE: The money deposited will not be available until we" <<endl
    << "verify the amount of any enclosed cash, and any enclosed checks clear." << endl << endl;

    total[index] += cents;
}