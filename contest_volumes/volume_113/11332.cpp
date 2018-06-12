// #trivial
#include <iostream>
using namespace std;

int main()
{
    for (int n; cin >> n && n != 0; ) {
        for (int g; n >= 10; n = g)
            for (g = 0; n > 0; n /= 10)
                g += n % 10;
        cout << n << endl;
    }

    return 0;
}
