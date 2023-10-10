#include <iostream>
using namespace std;

int main()
{
    int t,store,a,distance;
    cin>>t;
    for(int i=1; i<=t; i++)
    {
        int min=99,max=0;
        cin>>store;
        for(int j=1; j<=store; j++)
        {
            cin>>a;
            if(a<min)
            {
                min=a;
            }
            if(a>max)
            {
                max=a;
            }
        }
    distance=(max-min)*2;
    cout<<distance<<endl;
    }

}

// end main
