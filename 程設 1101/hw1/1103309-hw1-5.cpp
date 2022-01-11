#include <iostream>
using namespace std;

int main()
{
    int year;
    cout << "Enter a year ( 1583-3000 ): ";
    cin >> year;

    if(year%4==0)
    {
        if(year%100==0)
        {
            if(year%400==0)
            {
                cout<<"Year "<<year<<" is a leap year.";
            }
            else
            {
                cout<<"Year "<<year<<" is a common year.";
            }

        }
        else
        {
            cout<<"Year "<<year<<" is a leap year.";
        }
    }
    else
    {
        cout<<"Year "<<year<<" is a common year.";
    }


    return 0;
}
