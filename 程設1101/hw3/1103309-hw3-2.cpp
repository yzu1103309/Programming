#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <cstring>
using std::memset;

// returns true if and only if hugeInt1 < hugeInt2
bool less( int hugeInt1[], int hugeInt2[], int size1, int size2 );

// difference = minuend - subtrahend provided that minuend > subtrahend
void subtraction( int minuend[], int subtrahend[], int difference[],
                  int minuendSize, int subtrahendSize, int &differenceSize );

char strA[ 10000 ], strB[ 10000 ];
int numA[ 10000 ], numB[ 10000 ], numC[ 10000 ];

int main()
{
    int n;
    while( cin >> n )
        for( int k = 0; k < n; ++k )
        {
            cin >> strA >> strB;
            memset( numA, 0, sizeof( numA ) );
            memset( numB, 0, sizeof( numB ) );
            memset( numC, 0, sizeof( numC ) );

            int sizeA = strlen( strA );
            for( int i = 0; i < sizeA; ++i )
                numA[ i ] = strA[ sizeA - 1 - i ] - '0';

            int sizeB = strlen( strB );
            for( int i = 0; i < sizeB; ++i )
                numB[ i ] = strB[ sizeB - 1 - i ] - '0';

            int sizeC = 0;
            if( less( numA, numB, sizeA, sizeB ) )
            {
                cout << "-";
                subtraction( numB, numA, numC, sizeB, sizeA, sizeC );
            }
            else if( less( numB, numA, sizeB, sizeA ) )
                subtraction( numA, numB, numC, sizeA, sizeB, sizeC );
            else
            {
                sizeC = 1;
                numC[ 0 ] = 0;
            }

            for( int i = sizeC - 1; i >= 0; i-- )
                cout << numC[ i ];
            cout << endl;
        }

    return 0;
}

// returns true if and only if hugeInt1 < hugeInt2
bool less( int hugeInt1[], int hugeInt2[], int size1, int size2 )
{
    bool ToF;
    if(size2>=size1)
    {
        for(int i=size2; i>=0; i--)
        {
            if(hugeInt2[i]>hugeInt1[i])
            {
                ToF=true;
                break;
            }
            else if(hugeInt2[i]<hugeInt1[i])
            {
                ToF=false;
                break;
            }
        }
    }
    else
    {
        ToF=false;
    }
    return ToF;
}

// difference = minuend - subtrahend provided that minuend > subtrahend
void subtraction( int minuend[], int subtrahend[], int difference[],
                  int minuendSize, int subtrahendSize, int &differenceSize )
{
    differenceSize=minuendSize;
    for(int i=0; i<minuendSize; i++)
    {
        difference[i]=minuend[i]-subtrahend[i];
    }
    for(int i=0; i<differenceSize; i++)
    {
        if(difference[i]<0)
        {
            difference[i+1]--;
            difference[i]+=10;
        }
    }
    for(int i=differenceSize-1; i>=0; i--)
    {
        if(difference[i]==0)
        {
            differenceSize--;
        }
        else
        {
            break;
        }
    }

}
