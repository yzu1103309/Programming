#include<iostream>
using std::cin;
using std::cout;
using std::endl;
#include <cstring>
using std::memset;

// returns true if and only if the specified huge integer is zero
bool isZero( int hugeInt[], int size );

// returns true if and only if hugeInt1 < hugeInt2
bool less( int hugeInt1[], int hugeInt2[], int size1, int size2 );

// --hugeInt
void decrement( int hugeInt[], int size );

// minuend -= subtrahend provided that minuend > subtrahend
void subtraction( int minuend[], int subtrahend[], int &minuendSize, int subtrahendSize );

// multiplicand *= multiplier
void multiplication( int multiplicand[], int multiplier[], int &multiplicandSize, int multiplierSize );

// quotient = dividend / divisor; remainder = dividend % divisor
void division( int dividend[], int divisor[], int quotient[], int remainder[],
               int dividendSize, int divisorSize, int &quotientSize, int &remainderSize );

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( int hugeInt[], int &size );

const int arraySize = 200;

int main()
{
    int t, a, b;
    while( cin >> t >> a >> b )
    {
        cout << "(" << t << "^" << a << "-1)/(" << t << "^" << b << "-1) ";

        if( t == 1 )
            cout << "is not an integer with less than 100 digits.\n";
        else if( a == b )
            cout << "1\n";
        else if( a < b )
            cout << "is not an integer with less than 100 digits.\n";
        else
        {
            int dividend[ arraySize ] = {};
            int divisor[ arraySize ] = {};
            int quotient[ arraySize ] = {};
            int remainder[ arraySize ] = {};

            int dividendSize = 1;
            int divisorSize = 1;
            int quotientSize = 1;
            int remainderSize = 1;

            // put all digits of t into base
            int base[ arraySize ] = {};
            int baseSize = 0;
            for( int i = t; i > 0; i /= 10 )
                base[ baseSize++ ] = i % 10;

            // dividend = pow( t, a )
            dividend[ 0 ] = 1;
            for( int i = 0; i < a; ++i )
            {
                multiplication( dividend, base, dividendSize, baseSize );
                if( dividendSize > arraySize )
                    break;
            }

            if( dividendSize > arraySize )
                cout << "is not an integer with less than 100 digits.\n";
            else
            {
                // divisor = pow( t, b )0
                divisor[ 0 ] = 1;
                for( int i = 0; i < b; ++i )
                    multiplication( divisor, base, divisorSize, baseSize );

                decrement( dividend, dividendSize ); // --dividend
                decrement( divisor, divisorSize );   // --divisor

                division( dividend, divisor, quotient, remainder,
                          dividendSize, divisorSize, quotientSize, remainderSize );

                // quotient is an integer with less than 100 digits
                if( quotientSize < 100 && isZero( remainder, remainderSize ) )
                    for( int i = quotientSize - 1; i >= 0; i-- )
                        cout << quotient[ i ];
                else
                    cout << "is not an integer with less than 100 digits.";
                cout << endl;
            }
        }
    }
}

// returns true if and only if the specified huge integer is zero
bool isZero( int hugeInt[], int size )
{
    for( int i = 0; i < size; i++ )
        if( hugeInt[ i ] != 0 )
            return false;
    return true;
}

// returns true if and only if hugeInt1 < hugeInt2
bool less( int hugeInt1[], int hugeInt2[], int size1, int size2 )
{
    bool ToF=false;
    if(size2>=size1)
    {
        for(int i=size2-1; i>=0; i--)
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

// --hugeInt
void decrement( int hugeInt[], int size )
{
    hugeInt[0]--;
    for(int i=0; i<size; i++)
    {
        if(hugeInt[i]<0)
        {
            hugeInt[i+1]--;
            hugeInt[i]+=10;
        }
    }
}

// minuend -= subtrahend provided that minuend > subtrahend
void subtraction( int minuend[], int subtrahend[], int &minuendSize, int subtrahendSize )
{
    int differenceSize=minuendSize,difference[arraySize];
    for(int i=0; i<differenceSize; i++)
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
    //clear minuend
    memset(minuend,0,minuendSize);
    minuendSize=differenceSize;
    //put difference back to minuend
    for(int i=0; i<minuendSize; i++)
    {
        minuend[i]=difference[i];
    }
    //delete excessive 0s in minuend
    for(int i=minuendSize-1; i>=0; i--)
    {
        if(minuend[i]==0)
        {
            minuendSize--;
        }
        else
        {
            break;
        }
    }
}

// multiplicand *= multiplier
void multiplication( int multiplicand[], int multiplier[], int &multiplicandSize, int multiplierSize )
{
    int productSize=multiplicandSize+multiplierSize,product[arraySize];
    for(int i=0; i<productSize; i++) //put 0 first
    {
        product[i]=0;
    }
    for(int i=0; i<multiplicandSize; i++)
    {
        for(int j=0; j<multiplierSize; j++)
        {
            product[i+j]+=multiplicand[i]*multiplier[j];
        }
    }
    for(int i=0; i<productSize; i++)
    {
        if(product[i]>=10)
        {
            product[i+1]+=product[i]/10;
            product[i]%=10;
        }
    }
    //delete excessive 0s
    for(int i=productSize-1; i>=1; i--)
    {
        if(product[i]==0)
        {
            productSize--;
        }
        else
        {
            break;
        }
    }
    //put product back in multiplicand
    multiplicandSize=productSize;
    for(int i=0; i<productSize; i++)
    {
        multiplicand[i]=product[i];
    }
}


// quotient = dividend / divisor; remainder = dividend % divisor
void division( int dividend[], int divisor[], int quotient[], int remainder[],
               int dividendSize, int divisorSize, int &quotientSize, int &remainderSize )
{
    int bufferSize=divisorSize,buffer[arraySize];//create buffer
    int n=dividendSize-divisorSize;//shift position count
    quotientSize=dividendSize-divisorSize;//create quotient size
    remainderSize =dividendSize ;//create dividend size
    //put dividend in remainder
    for(int i=0; i<remainderSize; i++)
    {
        remainder[i]=dividend[i];
    }
    //put divisor in buffer
    for(int i=0; i<bufferSize; i++)
    {
        buffer[i]=divisor[i];
    }
    //buffer shift left for n positions
    for(int i=1; i<=n; i++)
    {
        int a[2]= {0,1},aSize=2;
        multiplication(buffer,a,bufferSize,aSize);
    }
    //Case 1: buffer>remainder
    if(less(remainder,buffer,remainderSize,bufferSize))
    {
        divideBy10(buffer,bufferSize);
        // put 0 in quotient first
        for(int i=0; i<quotientSize; i++)
        {
            quotient[i]=0;
        }

        for(int i=quotientSize-1; i>=0; i--)
        {
            while(less(remainder,buffer,remainderSize,bufferSize)==false)//while remainder>=buffer
            {
                subtraction(remainder,buffer,remainderSize,bufferSize);//remainder-=buffer loop
                quotient[i]++;
            }
            divideBy10(buffer,bufferSize);
        }
    }
    else //Case 2: remainder>=buffer
    {
        quotientSize++;
        //put 0 in quotient first
        for(int i=0; i<quotientSize; i++)
        {
            quotient[i]=0;
        }
        //division part
        for(int i=quotientSize-1; i>=0; i--)
        {
            while(less(remainder,buffer,remainderSize,bufferSize)==false)//while remainder">="buffer
            {
                subtraction(remainder,buffer,remainderSize,bufferSize);//remainder-=buffer
                quotient[i]++;
            }
            divideBy10(buffer,bufferSize);
        }
    }
}


// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( int hugeInt[], int &size )
{
    if( size == 1 )
        hugeInt[ 0 ] = 0;
    else
    {
        for( int i = 1; i < size; i++ )
            hugeInt[ i - 1 ] = hugeInt[ i ];

        size--;
        hugeInt[ size ] = 0;
    }
}
