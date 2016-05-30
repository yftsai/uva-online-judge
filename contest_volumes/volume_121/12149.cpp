#include <iostream>
using namespace std;

int main()
{
    // 1^2 + 2^2 + ... + n^2 = n*(n+1)*(2n+1)/6
    for (int n; (cin >> n) && (n!=0); )
        cout << n*(n+1)*(2*n+1)/6 << endl;
    return 0;
}
