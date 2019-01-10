// #dynamic_programming
#include <iostream>
#include <bitset>
using namespace std;

int main()
{
    int t;
    for (cin >> t; t > 0; --t) {
        bitset<1001> lengths;
        lengths.set(0);

        int n, p;
        cin >> n >> p;
        for (int i = 0, b; i < p && cin >> b; ++i)
            for (int len = n - b; len >= 0; --len)
                if (lengths.test(len))
                    lengths.set(len + b);

        cout << (lengths.test(n) ? "YES" : "NO") << endl;
    }

    return 0;
}
