// #trivial
#include <bitset>
#include <cstdint>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    uint16_t t;
    uint32_t n;
    string rep;
    for (cin >> t; t > 0 && cin >> n; t--) {
        bitset<26> common;
        common.flip();

        uint32_t ncuts = 0;
        for (uint32_t i = 0; i < n && cin >> rep; i++) {
            bitset<26> bset;
            for (auto c: rep)
                bset.set(c - 'a');
            common &= bset;
            if (common.none()) {
                common = bset;
                ncuts += 1;
            }
        }

        cout << ncuts << endl;
    }

    return 0;
}
