#include <iostream>
#include <climits>
using namespace std;

// 数字是正整数才正确
int divide(int numerator, int denominator)
{
    int quotient = 0;
    while(numerator >= denominator)
    {
        numerator -= denominator;
        quotient++;
    }
    return quotient;
}

// 被除数和除数异号就取相反数
int neg(int a, int b, int r)
{
    return ((a < 0) ^ (b < 0)) ? -r : r;
}

// O(n)
int division_naive(int num, int den)
{
    if(den == 0)
    {
        return INT_MAX;
    }
    else
    {
        int abs_num = abs(num);
        int abs_den = abs(den);

        int quo = 0;
        while(abs_num >= abs_den)
        {
            abs_num -= abs_den;
            quo++;
        }
        return neg(num, den, quo);
    }
}

// O(log(n))
int division_optimized(int num, int den)
{
    if(den == 0)
    {
        return INT_MAX;
    }
    else
    {
        int abs_num = abs(num);
        int abs_den = abs(den);

        int quo = 0;
        int bits = 0;
        while(abs_num >= abs_den)
        {
            bits = 0;
            while(abs_num >= abs_den<<bits)
            {
                abs_num -= abs_den<<bits;
                quo += 1<< bits;
                bits++;
            }
        }
        return neg(num, den, quo);
    }
}


int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        cout << "Usge: " << argv[0] << " num1 num2" << endl;
        exit(0);
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    cout << "Doing naive way ..." << endl;
    int q = division_naive(a, b);
    cout << "a / b = " << q << endl;

    cout << "Doing optimized way ..." << endl;
    int r = division_optimized(a, b);
    cout << "a / b = " << r << endl;

    return 0;
}
