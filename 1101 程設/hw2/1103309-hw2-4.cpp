#include <iostream>
using namespace std;

int main()
{
    int a,b,c,d,L;
    while(cin>>a>>b>>c>>d>>L&&a!=0||b!=0||c!=0||d!=0||L!=0){
            int num=0;
    for(int i=0; i<=L; i++)
    {
        if((a*i*i+b*i+c)%d==0)
        {
            num++;
        }
    }
    cout<<num<<endl;
}
}
// end main
