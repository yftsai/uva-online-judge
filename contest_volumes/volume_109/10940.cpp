// #easy
#include <iostream>
using namespace std;

int main()
{
    int remaining[500001];
    remaining[0] = 1;
    remaining[1] = 2;
    for (int n = 3; n <= 500000; ++n)
        remaining[n - 1] = (remaining[n - 2] + 2 <= n) ? (remaining[n - 2] + 2) : 2;

    for (int n; cin >> n && n > 0; )
        cout << remaining[n - 1] << endl;
    return 0;
}
