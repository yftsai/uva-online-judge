// #easy
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    const int primes[23] = {
        2,   3,  5,  7, 11, 13, 17, 19, 23, 29,
        31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
        73, 79, 81};
    int case_count;
    for (cin >> case_count; case_count > 0; case_count--){
        char line[81];
        cin >> line;

        int length = strlen(line);
        for (int p = 0; length >= primes[p]; p++) {
            bool is_period = true;
            while (length % primes[p] == 0 && is_period) {
                int period_length = length / primes[p];
                for (int i = period_length; i < length && is_period; i += period_length)
                    is_period = (strncmp(line, line + i, period_length) == 0);
                if (is_period)
                    length = period_length;
            }
        }

        cout << length << endl;
        if (case_count > 1)
            cout << endl;
    }
    return 0;
}
