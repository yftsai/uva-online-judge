// #easy
// This problem is paired with problem 11129.
#include <iostream>
using namespace std;

int main()
{
    int p[10000];
    bool used[10000];
    for (int n; cin >> n && n != 0; ) {
        char colon;
        cin >> colon;
        for (int i = 0; i < n; i++) {
            cin >> p[i];
            used[i] = false;
        }

        bool is_antiarithmetic = true;
        for (int j = 0; j < n && is_antiarithmetic; j++) {
            if (used[ p[j] ])
                is_antiarithmetic = false;
            else {
                used[ p[j] ] = true;
                for (int i = 0; i < j; i++) {
                    int pk = p[j] + p[j] - p[i];
                    if (0 <= pk && pk < n && !used[pk])
                        is_antiarithmetic = false;
                }
            }
        }
        cout << (is_antiarithmetic ? "yes" : "no") << endl;
    }
    return 0;
}
