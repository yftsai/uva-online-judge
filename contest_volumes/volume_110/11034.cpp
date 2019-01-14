// #easy
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int c;
    string bank;
    for (cin >> c; c > 0; --c) {
        int l, m;
        int left_count = 0, right_count = 0;
        int left_load = 0, right_load = 0;
        cin >> l >> m;
        l *= 100;
        for (int i = 0, len; i < m && cin >> len >> bank; ++i)
            if (bank == "left")
                if (left_load + len <= l)
                    left_load += len;
                else
                    ++left_count, left_load = len;
            else if (right_load + len <= l)
                right_load += len;
            else
                ++right_count, right_load = len;
        left_count += (left_load == 0) ? 0 : 1;
        right_count += (right_load == 0) ? 0 : 1;

        cout << ((left_count > right_count) ? (2 * left_count - 1) : (2 * right_count)) << endl;
    }

    return 0;
}
