// #sorting
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    for (unsigned int n; cin >> n; )
        cout << (n - 1 + (unsigned int)ceil(log2(n)) - 1) << endl;
    return 0;
}
