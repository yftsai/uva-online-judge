// #trivial
#include <algorithm>
#include <iostream>
using namespace std;

int main()
{
    for (uint32_t a, b, c; cin >> a >> b >> c && a != 0; ) {
        if (a > b && a > c)
            swap(a, c);
        else if (b > a && b > c)
            swap(b, c);

        cout << ((a * a + b * b == c * c) ? "right" : "wrong") << endl;
    }

    return 0;
}
