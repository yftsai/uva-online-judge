// #trivial
#include <iostream>
#include <string>
using namespace std;

unsigned int operator%(const string &dividend, const unsigned int divisor)
{
    unsigned int remainder = 0;
    for (char c: dividend)
        remainder = (remainder * 10 + c - '0') % divisor;
    return remainder;
}

int main()
{
    string year;
    for (bool is_first_case = true; cin >> year; is_first_case = false){
        const bool is_leap_year = (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
        if (!is_first_case)
            cout << endl;
        if (is_leap_year)
            cout << "This is leap year." << endl;
        if (year % 15 == 0)
            cout << "This is huluculu festival year." << endl;
        if (year % 55 == 0 && is_leap_year)
            cout << "This is bulukulu festival year." << endl;
        if (!is_leap_year && year % 15 != 0)
            cout << "This is an ordinary year." << endl;
    }

    return 0;
}
