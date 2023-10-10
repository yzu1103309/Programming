#include <iostream>
using namespace std;

int main()
{
    int T,a,b,sum=0;
    cin>>T;
    for(int i=1;i<=T;i++){
        cin>>a>>b;
        for(int j=a;j<=b;j++){
            if(j%2==1){
                sum+=j;
            }
        }
        cout<<"Case "<<i<<": "<<sum<<endl;
        sum=0;
    }
}

// end main
