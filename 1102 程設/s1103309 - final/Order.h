// Order.h
// Order class definition.
#ifndef ORDER_H
#define ORDER_H

#include <string>
using namespace std;

#include "Date.h"

const int price[ 15 ] = { 0, 200, 144, 184, 176, 176, 396, 200,
                             200, 175, 175, 200, 225, 375, 350 };

class Order
{
public:
   Order( string theOrderNumber = "", string theEmail = "" );
   void setOrderNumber( string theOrderNumber );
   string getOrderNumber() const;
   void setEmail( string theEmail );
   string getEmail() const;
   void setDeliveryDate( Date date );
   Date getDeliveryDate();
   void setOrderDetails( int theOrderDetails[] );
   void displayOrderDetails() const;
private:
   char orderNumber[ 12 ]; // each order has a unique orderNumber
   char email[ 40 ];
   Date deliveryDate;  // delivery date
   int quantity[ 15 ]; // quantity[ i ] is the quantity of food #i in the order
                       // quantity[ 0 ] is not used
}; // end class Order

#endif // ORDER_H