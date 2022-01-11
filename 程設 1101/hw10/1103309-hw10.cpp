#include <iostream>
#include <fstream>
using namespace std;

struct Account
{
   int accountNumber;    // account number
   int pin;              // personal identification number
   int availableBalance; // funds available for withdrawal
   int totalBalance;     // funds available + funds waiting to clear
};

// retrieve Account object (from Accounts.dat) containing specified accountNumber and pin,
// put this object to currentAccount,
// and put the record number (in Accounts.dat) of this object into recordNumber.
// if this object exists, returns true; otherwise returns false.
bool loadAccount( int accountNumber, int pin, Account &currentAccount, int &recordNumber );

// display the main menu and perform transactions
void performTransactions( Account &currentAccount, int &recordNumber, int &remainingBills );

// perform withdrawal transaction
void withdrawal( Account &currentAccount, int &remainingBills );

// perform deposit transaction
void deposit( Account &currentAccount );

// write currentAccount into the n-th record of Accounts.dat
void saveAccount( Account currentAccount, int n );

const int INITIAL_BILLS = 5; // the number bills loaded each day
fstream ioFile("Accounts.dat", ios::in | ios::out | ios::binary);

int main()
{
   // the number of remaining bills in the cash dispenser
   int remainingBills = INITIAL_BILLS;
   int recordNumber;
   Account currentAccount;

   // welcome and authenticate user; perform transactions
   while ( true )
   {
      int accountNumber;
      int pin;

      do {
         cout << "Welcome!\n";
         cout << "\nPlease enter your account number: ";
         cin >> accountNumber;
         cout << "\nEnter your PIN: ";
         cin >> pin; // input PIN
      } while( !loadAccount( accountNumber, pin, currentAccount, recordNumber ) );
      
      performTransactions( currentAccount, recordNumber, remainingBills );
      cout << "\nThank you! Goodbye!\n\n";
   }
} // end function main

// retrieve Account object (from Accounts.dat) containing specified accountNumber and pin,
// put this object to currentAccount,
// and put the record number of this object into recordNumber.
// if this object exists, returns true; otherwise returns false.
bool loadAccount( int accountNumber, int pin, Account &currentAccount, int &recordNumber )
{   
    recordNumber = 0;
    Account buffer;
    ioFile.clear();
    ioFile.seekg(0, ios::beg);
    
    if (!ioFile) {
        cout << "The Account Data File is Not Accessable, exiting...";
        exit(1);
    }
   
    while (!ioFile.eof()) {
        ioFile.read(reinterpret_cast<char*>(&buffer.accountNumber), sizeof(buffer.accountNumber));
        ioFile.read(reinterpret_cast<char*>(&buffer.pin), sizeof(buffer.pin));
        ioFile.read(reinterpret_cast<char*>(&buffer.availableBalance), sizeof(buffer.availableBalance));
        ioFile.read(reinterpret_cast<char*>(&buffer.totalBalance), sizeof(buffer.totalBalance));
        
        if (accountNumber == buffer.accountNumber && pin == buffer.pin) {
            currentAccount = buffer;
            return true;
        }
        recordNumber++;
    }
    cout << endl << "Invalid account number or PIN. Please try again." << endl << endl;
    return false;

} // end function loadAccount

// display the main menu and perform transactions
void performTransactions( Account &currentAccount, int &recordNumber, int &remainingBills )
{
    int choice;
    do{
        cout << endl << "Main menu:" << endl;
        cout << "1 - View my balance" << endl;
        cout << "2 - Withdraw cash" << endl;
        cout << "3 - Deposit funds" << endl;
        cout << "4 - Exit" << endl << endl;
        cout << "Enter a choise: ";
        cin >> choice;
        cout << endl ;
        if( !(1 <= choice && choice <= 4) )
            cout << "You did not enter a valid selection. Try again." << endl << endl;
        
    switch (choice) {
        case 1:
            cout << "Balance Information:" << endl;
            cout << " - Available balance: " << currentAccount.availableBalance << endl;
            cout << " - Total balance: " << currentAccount.totalBalance << endl ;
            break;
        case 2:
            withdrawal(currentAccount, remainingBills);
            break;
        case 3:
            deposit(currentAccount);
            break;
        case 4:
            cout << "Exiting the system..." << endl;
            saveAccount(currentAccount, recordNumber);
        }
    } while (choice != 4);
} // end function performTransactions

// perform withdrawal transaction
void withdrawal( Account &currentAccount, int &remainingBills )
{
    int choice;
    do{
    cout << "Withdrawal options:" << endl;
    cout << "1 - $20" << endl;
    cout << "2 - $40" << endl;
    cout << "3 - $60" << endl;
    cout << "4 - $100" << endl;
    cout << "5 - $200" << endl;
    cout << "6 - Cancel transaction" << endl << endl;
    cout << "Choose a withdrawal option (1-6): ";
    cin >> choice; 
    cout << endl;
    if (choice == 6) {
        cout << "Canceling transaction..." << endl;
    }
    else if (choice == 1){
        if (currentAccount.availableBalance >= 20 && remainingBills >= 1) {
            currentAccount.availableBalance -= 20;
            currentAccount.totalBalance -= 20;
            remainingBills -= 1;
            cout << "Please take your cash from the cash dispenser." << endl;
            break;
        }
        else {
            if (currentAccount.availableBalance < 20) {
                cout << "Insufficient funds in your account." << endl << endl;
            }
            else if (remainingBills < 1) {
                cout << "Insufficient cash available in the ATM." << endl << endl;
            }
            cout << "Please choose a smaller amount." << endl << endl;
        }
    }
    else if (choice == 2) {
        if (currentAccount.availableBalance >= 40 && remainingBills >= 2) {
            currentAccount.availableBalance -= 40;
            currentAccount.totalBalance -= 40;
            remainingBills -= 2;
            cout << "Please take your cash from the cash dispenser." << endl;
            break;
        }
        else {
            if (currentAccount.availableBalance < 40) {
                cout << "Insufficient funds in your account." << endl << endl;
            }
            else if (remainingBills < 2) {
                cout << "Insufficient cash available in the ATM." << endl << endl;
            }
            cout << "Please choose a smaller amount." << endl << endl;
        }
    }
    else if (choice == 3) {
        if (currentAccount.availableBalance >= 60 && remainingBills >= 3) {
            currentAccount.availableBalance -= 60;
            currentAccount.totalBalance -= 60;
            remainingBills -= 3;
            cout << "Please take your cash from the cash dispenser." << endl;
            break;
        }
        else {
            if (currentAccount.availableBalance < 60) {
                cout << "Insufficient funds in your account." << endl << endl;
            }
            else if (remainingBills < 3) {
                cout << "Insufficient cash available in the ATM." << endl << endl;
            }
            cout << "Please choose a smaller amount." << endl << endl;
        }
    }
    else if (choice == 4) {
        if (currentAccount.availableBalance >= 100 && remainingBills >= 5) {
            currentAccount.availableBalance -= 100;
            currentAccount.totalBalance -= 100;
            remainingBills -= 5;
            cout << "Please take your cash from the cash dispenser." << endl;
            break;
        }
        else {
            if (currentAccount.availableBalance < 100) {
                cout << "Insufficient funds in your account." << endl << endl;
            }
            else if (remainingBills < 5) {
                cout << "Insufficient cash available in the ATM." << endl << endl;
            }
            cout << "Please choose a smaller amount." << endl << endl;
        }
    }
    else if (choice == 5) {
        if (currentAccount.availableBalance >= 200 && remainingBills >= 10) {
            currentAccount.availableBalance -= 200;
            currentAccount.totalBalance -= 200;
            remainingBills -= 10;
            cout << "Please take your cash from the cash dispenser." << endl;
            break;
        }
        else {
            if (currentAccount.availableBalance < 200) {
                cout << "Insufficient funds in your account." << endl << endl;
            }
            else if (remainingBills < 10) {
                cout << "Insufficient cash available in the ATM." << endl << endl;
            }
            cout << "Please choose a smaller amount." << endl << endl;
        }
    }
    } while (choice != 6);
} // end function withdrawal

// perform deposit transaction
void deposit( Account &currentAccount )
{
   cout << "Please enter a deposit amount in dollars (or 0 to cancel): ";
   int amount;
   cin >> amount; // receive input of deposit amount

   // check whether user entered a deposit amount or canceled
   if( amount == 0 )
      cout << "\nCanceling transaction...\n";
   else // user canceled instead of entering amount
   {
      // request deposit envelope containing specified amount
      cout << "\nPlease insert a deposit envelope containing ";
      cout << "$" << amount;
      cout << " in the deposit slot.\n";

      cout << "\nYour envelope has been received."
         << "\nNOTE: The money deposited will not be available until we"
         << "\nverify the amount of any enclosed cash, and any enclosed checks clear.\n";

      // credit account to reflect the deposit
      currentAccount.totalBalance += amount; // add to total balance
   } // end if 
} // end function deposit

void saveAccount( Account currentAccount, int n )
{   
    int POS = (4 * n + 2) * sizeof(int);
    ioFile.seekp(POS, ios::beg);
    ioFile.write(reinterpret_cast<const char*>(&currentAccount.availableBalance), sizeof(currentAccount.availableBalance));
    ioFile.write(reinterpret_cast<const char*>(&currentAccount.totalBalance), sizeof(currentAccount.totalBalance));
}