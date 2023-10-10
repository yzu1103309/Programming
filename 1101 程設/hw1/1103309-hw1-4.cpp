// Determine whether three values represent the sides of a right triangle.
#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    int side1; // length of side 1
    int side2; // length of side 2
    int side3; // length of side 3

    // get values of three sides
    cout << "Enter side 1: ";
    cin >> side1;

    cout << "Enter side 2: ";
    cin >> side2;

    cout << "Enter side 3: ";
    cin >> side3;

    int longest,a,b;
    longest=side1;
    a=side2;
    b=side3;
    if(side2>longest)
    {
        if(side3>side2)
        {
            longest=side3;
            a=side1;
            b=side2;
        }
        else
        {
            longest=side2;
            a=side1;
            b=side3;
        }
    }
    if(a*a+b*b==pow(longest,2))
    {
        cout<<"These are the sides of a right triangle.";
    }
    else
    {
        cout<<"These do not form a right triangle.";
    }


    return 0;
} // end main
