#include <iostream>
using namespace std;

int function(int input){
int p=0;
while(input>0)
        {
            p+=input%10;
            input/=10;
        }
        return p;
}

int main()
{
    int input,p;
    while(cin>>input&&input!=0)
    {
        p=function(input);
        while(p>=10){
            p=function(p);
        }
        cout<<p<<endl;
        p=0;
    }
}

// end main
