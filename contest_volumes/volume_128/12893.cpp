// #trivial
#include <iostream>
#include <bitset>
using namespace std;

int main()
{
    uint16_t t;
    uint64_t n;
    for (cin >> t; t > 0 && cin >> n; t--) {
        bitset<60> bs(n);
        cout << bs.count() << endl;
    }

    return 0;
}
