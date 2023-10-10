#include <iostream>
using namespace std;

// returns the maximum cycle-length over all integers
// between and including first and last
int maxCycleLength( int first, int last );

int cycleLength( int n ); // returns the cycle-length of n

int main()
{
   int i, j;
   while( cin >> i >> j )
   {
      cout << i << ' ' << j << ' ';

      if( i > j )
      {
         int buf = i;
         i = j;
         j = buf;
      }

      cout << maxCycleLength( i, j ) << endl;
   }
}

int maxCycleLength( int first, int last )
{
	if(first==last){
	  return cycleLength(last);
	}else{
		int k=maxCycleLength(first+1,last);
		if(cycleLength(first)<k){
			return k;
		}else{
			return cycleLength(first);
		}
	}
}

int cycleLength( int n )
{	
	if(n==1){
		return 1; 
	}else if(n%2==1){
		return 1+cycleLength(n*3+1);
	}else if(n%2==0){
		return 1+cycleLength(n/2);
	}

}
