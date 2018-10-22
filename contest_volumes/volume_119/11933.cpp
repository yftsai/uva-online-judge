// #easy
#include <iostream>
using namespace std;

int main()
{
    for (int n; cin >> n && n != 0; ) {
        int a = 0, b = 0;
        bool is_odd = true;
        for (int c = 1; n > 0; n >>= 1, c <<= 1)
            if (n & 1) {
                if (is_odd)
                    a |= c;
                else
                    b |= c;
                is_odd = !is_odd;
            }
        cout << a << " " << b << endl;
    }
    return 0;
}
