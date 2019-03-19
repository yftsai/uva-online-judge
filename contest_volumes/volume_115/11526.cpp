#include <iostream>
using namespace std;

int main()
{
    int t, n;
    for (cin >> t; t > 0 && cin >> n; ) {
        if (n <= 0)
            cout << 0 << endl;
        else {
            int64_t h = 0;
            int begin = 1;
            for (int end; n / begin > 1; begin = end) {
                int k = n / begin;
                end = n / k + 1;
                h += k * (end - begin);
            }
            h += (n - begin + 1);
            cout << h << endl;
        }
    }

    return 0;
}
