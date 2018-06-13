// #easy
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

int main()
{
    string digits = "0123456789";
    set<string> solutions[80];
    do {
        int num = stoi(string(digits.begin(), digits.begin() + 5));
        int den = stoi(string(digits.begin() + 5, digits.end()));
        if (num % den == 0)
            solutions[num / den].insert(digits);
    } while (next_permutation(digits.begin(), digits.end()));

    bool is_first_case = true;
    for (int n; cin >> n && n != 0; is_first_case = false) {
        if (!is_first_case)
            cout << endl;

        if (solutions[n].size() == 0)
            cout << "There are no solutions for " << n << "." << endl;
        else
            for (const string &s: solutions[n])
                cout << string(s.begin(), s.begin() + 5)
                     << " / " << string(s.begin() + 5, s.end())
                     << " = " << n << endl;
    }
    return 0;
}
