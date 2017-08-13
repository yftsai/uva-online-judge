// #easy
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void add(const string &addend, string &number)
{
    char carry = 0;
    for (size_t i = 0; i < addend.size() || i < number.size() || carry != 0; i++, carry /= 10) {
        carry += (i < addend.size()) ? (addend[i] - '0') : 0;
        carry += (i < number.size()) ? (number[i] - '0') : 0;
        if (i < number.size())
            number[i] = '0' + carry % 10;
        else
            number += '0' + carry % 10;
    }
}

int main()
{
    vector<string> row;
    do {
        for (size_t i = row.size(); i >= 2; i--)
           add(row[i-2], row[i-1]);
        row.push_back("1");
        for (size_t i = 0; i < row.size(); i++) {
            for (auto it = row[i].rbegin(); it != row[i].rend(); it++)
                cout << *it;
            if (i < row.size() - 1)
                cout << " ";
            else
                cout << endl;
        }
    } while (row[row.size() /2].size() < 61);

    return 0;
}
