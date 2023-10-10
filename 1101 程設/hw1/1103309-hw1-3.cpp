#include <iostream>
#include <math.h>
using namespace std; // program uses names from the std namespace

int main()
{
    int number; // integer read from user

    cout << "Enter a five-digit integer: "; // prompt
    cin >> number; // read integer from user
    int a[5];
    for(int i=0,j=4; i<5&&j>=0; i++,j--)
    {
        a[i]=number/pow(10,j);
        a[i]=a[i]%10;
    }

    if(a[0]==a[4]&&a[1]==a[3])
    {
        cout<<number<<" is a palindrome!!!";
    }
    else
    {
        cout<<number<<" is not a palindrome.";
    }

    return 0;
} // end main
