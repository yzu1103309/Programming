// Huge integer division
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#include<cmath>
using std::log10;

// returns true if and only if the specified huge integer is zero
bool isZero(int hugeInt[], int size);

// returns true if and only if hugeInt1 < hugeInt2
bool less(int hugeInt1[], int hugeInt2[], int size1, int size2);

// --hugeInt
void decrement(int hugeInt[], int& size);

// multiplicand *= multiplier
void multiAssign(int multiplicand[], int multiplier[], int& multiplicandSize, int multiplierSize);

// quotient = dividend / divisor; remainder = dividend % divisor
void division(int dividend[], int divisor[], int quotient[], int remainder[],
    int dividendSize, int divisorSize, int& quotientSize, int& remainderSize);

// product = multiplicand * multiplier * ( 10 ^ multiplierPos )
void multiplication(int multiplicand[], int multiplier, int product[],
    int multiplicandSize, int multiplierPos, int& productSize);

// minuend -= subtrahend
void subtraAssign(int minuend[], int subtrahend[], int& minuendSize, int subtrahendSize);

const int arraySize = 200;

int main()
{
    int t, a, b;
    while (cin >> t >> a >> b)
    {
        cout << "(" << t << "^" << a << "-1)/(" << t << "^" << b << "-1) ";

        if (t == 1)
            cout << "is not an integer with less than 100 digits.\n";
        else if (a == b)
            cout << "1\n";
        else if (a < b)
            cout << "is not an integer with less than 100 digits.\n";
        else if (a % b != 0)
            cout << "is not an integer with less than 100 digits.\n";
        else if ((a - b) * static_cast<int>(log10(t)) > 95)
            cout << "is not an integer with less than 100 digits.\n";
        else
        {
            int dividend[arraySize] = {};
            int divisor[arraySize] = {};
            int quotient[arraySize] = {};
            int remainder[arraySize] = {};

            int dividendSize = 1;
            int divisorSize = 1;
            int quotientSize = 1;
            int remainderSize = 1;

            // put all digits of t into base
            int base[arraySize] = {};
            int baseSize = 0;
            for (int i = t; i > 0; i /= 10)
                base[baseSize++] = i % 10;

            // dividend = pow( t, a )
            dividend[0] = 1;
            for (int i = 0; i < a; ++i)
            {
                multiAssign(dividend, base, dividendSize, baseSize);
                if (dividendSize > arraySize)
                    break;
            }

            if (dividendSize > arraySize)
                cout << "is not an integer with less than 100 digits.\n";
            else
            {
                // divisor = pow( t, b )
                divisor[0] = 1;
                for (int i = 0; i < b; ++i)
                    multiAssign(divisor, base, divisorSize, baseSize);

                decrement(dividend, dividendSize); // --dividend
                decrement(divisor, divisorSize);   // --divisor

                division(dividend, divisor, quotient, remainder,
                    dividendSize, divisorSize, quotientSize, remainderSize);

                // quotient is an integer with less than 100 digits
                if (quotientSize < 100 && isZero(remainder, remainderSize))
                    for (int i = quotientSize - 1; i >= 0; i--)
                        cout << quotient[i];
                else
                   cout << "is not an integer with less than 100 digits.";
                cout << endl;

            }
        }
    }
}

// returns true if and only if the specified huge integer is zero
bool isZero(int hugeInt[], int size)
{
    for (int i = 0; i < size; i++)
        if (hugeInt[i] != 0)
            return false;
    return true;
}

// returns true if and only if hugeInt1 < hugeInt2
bool less(int hugeInt1[], int hugeInt2[], int size1, int size2)
{
    bool ToF = false;
    if (size2 >= size1)
    {
        for (int i = size2 - 1; i >= 0; i--)
        {
            if (hugeInt2[i] > hugeInt1[i])
            {
                ToF = true;
                break;
            }
            else if(hugeInt1[i]>hugeInt2[i])
            {
                ToF = false;
                break;
            }
        }
    }
    return ToF;
}

// --hugeInt
void decrement(int hugeInt[], int& size)
{
    hugeInt[0]--;
    for (int i = 0; i < size; i++) {
        if (hugeInt[i] < 0) {
            hugeInt[i] += 10;
            hugeInt[i + 1]--; //modified: just corrected the typing mistake "i+i" to "i+1"
        }
    }
    //delete excessive 0s in hugeInt
    for (int i = size - 1; i > 0; i--) {
        if (hugeInt[i] == 0) {
            size--;
        }
        else {
            break;
        }
    }
}

// multiplicand *= multiplier
void multiAssign(int multiplicand[], int multiplier[], int& multiplicandSize, int multiplierSize)
{
    int productSize = multiplicandSize + multiplierSize, product[arraySize] = {};
    for (int i = 0; i < multiplicandSize; i++) {
        for (int j = 0; j < multiplierSize; j++) {
            product[i + j] += multiplicand[i] * multiplier[j];
        }
    }
    for (int i = 0; i < productSize; i++) {
        if (product[i] >= 10) {
            product[i + 1] += product[i] / 10;
            product[i] %= 10;
        }
    }
    //delete excessive 0s in product
    for (int i = productSize-1; i >0; i--) {
        if (product[i] == 0) {
            productSize--;
        }
        else {
            break;
        }
    }
    //put product back to multiplicand
    multiplicandSize = productSize;
    for (int i = 0; i < productSize; i++) {
        multiplicand[i] = product[i];
    }
}

void division(int dividend[], int divisor[], int quotient[], int remainder[],
    int dividendSize, int divisorSize, int& quotientSize, int& remainderSize)
{
    //put dividend in remainder
    remainderSize = dividendSize;
    for (int i = 0; i < dividendSize; i++) {
        remainder[i] = dividend[i];
    }

    //quotientSize will not be less than this
    quotientSize = dividendSize - divisorSize +1;

    int a = divisor[divisorSize - 1], j = dividendSize - 1, buffer[arraySize] = {};
    for (int i = dividendSize - divisorSize; i >= 0; i--, j--) {
        int b = 10 * remainder[j + 1] + remainder[j], bufferSize=divisorSize+i+1;
        if(a<=b){
            quotient[i] = b / a;
            multiplication(divisor, quotient[i], buffer, divisorSize, i, bufferSize);
            while (less(remainder, buffer, remainderSize, bufferSize)==true) {

			    //clear current buffer
                for (int k = 0; k < bufferSize; k++) {
                    buffer[k] = 0;
                }
                quotient[i]--;
                multiplication(divisor, quotient[i], buffer, divisorSize, i, bufferSize);
            }
            subtraAssign(remainder, buffer, remainderSize, bufferSize);
        }
        //clear buffer
        for (int k = 0; k < bufferSize; k++) {
            buffer[k] = 0;
       }
    }
    //delete excessive 0s in the final quotient
    for (int i = quotientSize - 1; i > 0; i--) {
        if (quotient[i] == 0) {
            quotientSize--;
        }
        else {
            break;
        }
    }
}

// product = multiplicand * multiplier * ( 10 ^ multiplierPos )
void multiplication(int multiplicand[], int multiplier, int product[],
    int multiplicandSize, int multiplierPos, int& productSize)
{
    for (int i = 0; i < multiplicandSize; i++) {
        product[multiplierPos + i] = multiplicand[i] * multiplier;
    }
    for (int i = multiplierPos; i < productSize; i++) {
        if (product[i] >= 10) {
            product[i + 1] += product[i] / 10; //modified: just added the little missing "+"
            product[i] %= 10;
        }
    }
    //delete excessive 0s in product
    for (int i = productSize - 1; i > 0; i--) {
        if (product[i] == 0) {
            productSize--;
        }
        else {
            break;
        }
    }
}

// minuend -= subtrahend
void subtraAssign(int minuend[], int subtrahend[], int& minuendSize, int subtrahendSize)
{
    for (int i = 0; i < minuendSize; i++) {
        minuend[i] -= subtrahend[i];
    }
    for (int i = 0; i < minuendSize; i++) {
        if (minuend[i] < 0) {
            minuend[i] += 10;
            minuend[i + 1] -= 1;
        }
    }
    //delete excessive 0s in minuend
    for (int i = minuendSize-1; i > 0 ; i--) {
        if (minuend[i] == 0) {
            minuendSize--;
        }
        else {
            break;
        }
    }
}
