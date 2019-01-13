#include <iostream>
#include <string>
using namespace std;

int main()
{
    int t;
    string n;
    cin >> t;
    for (int case_number = 1; case_number <= t && cin >> n; ++case_number) {
        int counts[3] = { 0 }, r = 0;
        for (char c: n)
            ++counts[(c - '0') % 3];
        for (int i = 0; i < 3; ++i)
            r += i * counts[i];
        r %= 3;

        bool will_win;
        if (r == 0)
            will_win = (counts[0] % 2 == 1);
        else
            will_win = (counts[r] > 0) && (counts[0] % 2 == 0);

        cout << "Case " << case_number << ": " << (will_win ? 'S' : 'T') << endl;
    }

    return 0;
}
