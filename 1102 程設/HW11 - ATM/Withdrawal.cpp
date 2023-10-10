// Withdrawal.cpp
// Member-function definitions for class Withdrawal.
#include <iostream>
#include <iomanip>
using namespace std;

#include "Withdrawal.h" // Withdrawal class definition
#include "BankDatabase.h" // BankDatabase class definition

// global constant that corresponds to menu option to cancel
const int CANCELED = 6;
const int INITIAL_REMAINING_BILLS = 5;
int Withdrawal::remainingBills = INITIAL_REMAINING_BILLS;

// Withdrawal constructor initialize class's data members
Withdrawal::Withdrawal( int userAccountNumber, BankDatabase &atmBankDatabase )
   : Transaction( userAccountNumber, atmBankDatabase ),
     amount( 0 )
{
}

// perform transaction; overrides Transaction's pure virtual function
void Withdrawal::execute()
{
   bool cashDispensed = false; // cash was not dispensed yet
   bool transactionCanceled = false; // transaction was not canceled yet

   // get references to bank database and screen
   BankDatabase &bankDatabase = getBankDatabase();

   while( !transactionCanceled && !cashDispensed )
   {
       if(remainingBills == 0) {
           cout << endl << "The machine has already run out of cash!" << endl;
           transactionCanceled = true;
       }
       else
       {
           int value = displayMenuOfAmounts();
           double avail = bankDatabase.getAvailableBalance(getAccountNumber());
           cout << endl;
           if(value == 6)
               transactionCanceled = true;
           else if(value > avail)
           {
               cout << "The balance in your account is not enough to execute this operation! "<< endl;
               (avail != 0)?cout << "Please choose a lower amount! " :cout<<"" ,transactionCanceled = true;
               cout <<"(Your available balance: $" << avail << ")";
           }
           else if(value/20 > remainingBills)
           {
               cout << "There are not enough $20 bills to accomplish this operation!" << endl;
               cout << "Only " << remainingBills << " $20";
               (remainingBills == 1)?cout << " bill is": cout << " bills are";
               cout << " left in the machine.";
           }
           else{
               bankDatabase.debit(getAccountNumber(),value);
               remainingBills -= value/20;
               cashDispensed = true;
           }
           if(cashDispensed){
               cout << "Please take your cash from the cash dispenser." ;
           }
           cout << endl;
       }
   }
}

// display a menu of withdrawal amounts and the option to cancel;
// return the chosen amount or 0 if the user chooses to cancel
int Withdrawal::displayMenuOfAmounts() const
{
   int userChoice = 0; // local variable to store return value

   // array of amounts to correspond to menu numbers
   int amounts[] = { 0, 20, 40, 60, 100, 200 };

   // loop while no valid choice has been made
   while ( userChoice == 0 )
   {
      // display the menu
      cout << "\nWithdrawal options:" << endl;
      cout << "1 - $20" << endl;
      cout << "2 - $40" << endl;
      cout << "3 - $60" << endl;
      cout << "4 - $100" << endl;
      cout << "5 - $200" << endl;
      cout << "6 - Cancel transaction" << endl;
      cout << "\nChoose a withdrawal option (1-6): " << endl;

      int input; // get user input through keypad
      cin >> input;

      // determine how to proceed based on the input value
      switch ( input )
      {
         case 1: // if the user chose a withdrawal amount 
         case 2: // (i.e., chose option 1, 2, 3, 4 or 5), return the
         case 3: // corresponding amount from amounts array
         case 4:
         case 5:
            userChoice = amounts[ input ]; // save user's choice
            break;       
         case CANCELED: // the user chose to cancel
            userChoice = CANCELED; // save user's choice
            break;
         default: // the user did not enter a value from 1-6
            cout << "\nInvalid selection. Try again." << endl;
      }
   }

   return userChoice; // return withdrawal amount or CANCELED
}