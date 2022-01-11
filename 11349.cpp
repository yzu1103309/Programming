#include <iostream>
using namespace std;

int main()
{
    int T;
    char trash; 
    //A var to store unnecessary "N="
    cin>>T;
    //input test cases
    for(int j=1; j<=T; j++) //execution count
    {
        bool NOneg=true,sym=true;
        //two var to check negative and symmetric
        //bool needs to be refreshed each case
        int n; //dimention
        cin>>trash>>trash>>n; //"N = int"
        //delete the unnecessary words and input the dimension
        long long M[n*n]= {};//1D array
        for(int i=0; i<n*n; i++)
        {
            cin>>M[i];
            //input the Matrix
        }
        for(int i=0; i<n*n; i++)
        {
            if(M[i]<0)
            {
                NOneg=false;
            };
            //check if the matrix contain a negative int
        }
        for(int i=0,k=n*n-1; i<n*n/2; i++,k--)
        {
            if(M[i]!=M[k])
            {
                sym=false;
            }
            //check if M is symmetric
        }
        if(NOneg&&sym){
            cout<<"Test #"<<j<<": Symmetric."<<endl;
        }else{
            cout<<"Test #"<<j<<": Non-symmetric."<<endl;
        }
    }//end for-loop
}//end main

