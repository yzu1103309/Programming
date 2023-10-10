// AccountDatabase.cpp
// Member-function definitions for class AccountDatabase.
#include <iostream>
#include <fstream>
#include "AccountDatabase.h" // AccountDatabase class definition

AccountDatabase::AccountDatabase()
{
   loadAccountDetails();
}

AccountDatabase::~AccountDatabase()
{
   saveAccountDetails();
}

void AccountDatabase::loadAccountDetails()
{
    ifstream ioFile("Accounts.dat", ios::in | ios::binary);

    if (!ioFile)
    {
        cout << "Error when reading the account database" << endl;
        exit(1);
    }

    Account tmp;
    while ( ioFile.read( reinterpret_cast<char*>(&tmp), sizeof(Account) ) )
    {
        accounts.push_back(tmp);
    }

}

// determine whether user-specified email address and password match
// those of an account in the database
bool AccountDatabase::existAccount( string userEmail )
{
   // attempt to retrieve the account with the email address
   Account * const userAccountPtr = getAccount( userEmail );

   if( userAccountPtr == nullptr )
      return false;
   else // account found
      return true;
} // end function authenticateUser

// determine whether user-specified email address and password match
// those of an account in the database
bool AccountDatabase::authenticateUser( string email, string password )
{
   // attempt to retrieve the account with the email address
   Account * const userAccountPtr = getAccount( email );

   // if account exists, return result of Account function validatePassword
   if ( userAccountPtr == nullptr )
      return false;
   else
      return userAccountPtr->validatePassword( password );
} // end function authenticateUser

void AccountDatabase::pushBack( Account &newAccount )
{
   accounts.push_back( newAccount );
}

string AccountDatabase::getName( string email )
{
   Account *accountPtr = getAccount( email );
   if( accountPtr == nullptr )
      return string( "" );
   else
      return accountPtr->getName();
}

string AccountDatabase::getAddress( string email )
{
   Account *accountPtr = getAccount( email );
   if( accountPtr == nullptr )
      return string( "" );
   else
      return accountPtr->getAddress();
}

int* AccountDatabase::getCart( string email )
{
   Account *accountPtr = getAccount( email );
   if( accountPtr == nullptr )
      return nullptr;
   else
      return accountPtr->getCart();
}

void AccountDatabase::modifyCart( Account &account )
{
   Account *ptr = getAccount( account.getEmail() );
   ptr->setCart( account.getCart() );
}

void AccountDatabase::resetCart( string email )
{
   Account *ptr = getAccount( email );
   ptr->resetCart();
}

bool AccountDatabase::emptyCart( string email )
{
   Account *accountPtr = getAccount( email );
   if( accountPtr == nullptr )
      return true;
   else
      return accountPtr->emptyCart();
}

void AccountDatabase::displayOrders( string email )
{
   Account *accountPtr = getAccount( email );
   if( accountPtr != nullptr )
      return accountPtr->displayOrders();
}

void AccountDatabase::saveAccountDetails()
{
    ofstream ioFile("Accounts.dat", ios::out | ios::binary);
    
    if (!ioFile)
    {
        cout << "There are some problems writing the accounts database" << endl;
        exit(1);
    }

    for (size_t t = 0; t < accounts.size(); t++)
    {
        ioFile.write(reinterpret_cast<char*>(&accounts[t]), sizeof(Account));
    }
}

Account* AccountDatabase::getAccount( string email )
{
    for (size_t t = 0; t < accounts.size(); t++)
    {
        if (email == accounts[t].getEmail())
            return &accounts[t];
    }

    return nullptr;
}