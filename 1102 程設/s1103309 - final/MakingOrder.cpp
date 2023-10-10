#include <iostream>
#include <iomanip>
#include "MakingOrder.h" // MakingOrder class definition

extern int inputAnInteger( int begin, int end = INT_MAX );

MakingOrder::MakingOrder( string theEmail, AccountDatabase &theAccountDatabase )
   : email( theEmail ),
     accountDatabase( theAccountDatabase )
{
}

void MakingOrder::run()
{
    Account tmp(email);

    tmp.setCart(accountDatabase.getCart(email));

    int food, quantity, choice;

    do
    {
        tmp.displayCart();
        do
        {
            cout << "\nEnter foods code (0 to end): ";
            food = inputAnInteger(0, 14);
            if (food == 0)
                return;
        } while (food == -1);

        cout << "\nEnter quantity: ";
        cin >> quantity;
        cin.ignore();

        tmp.getCart()[food] = quantity;

        cout << "\n1. Continue Shopping\n"
            << "2. Save Your Shopping Cart\n"
            << "3. Abandon\n\n"
            << "Enter your choice: (1~3): ";
        choice = inputAnInteger(1, 3);

        if (choice == 2)
            accountDatabase.modifyCart(tmp);

    } while (choice == 1);
}