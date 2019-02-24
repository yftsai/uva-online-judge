// #dynamic_programming
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
    vector<vector<int8_t>> products;
    for (uint32_t n, k; cin >> n >> k; ) {
        products.resize(size_t(log2(n)) + 1u);
        products[0].resize(n);
        int value;
        for (auto &v: products[0]) {
            cin >> value;
            v = (value < 0) ? -1 : ((value == 0) ? 0 : 1);
        }
        for (uint8_t e = 0; e + 1u < products.size(); ++e) {
            products[e + 1u].resize(products[e].size() / 2u);
            for (uint32_t j = 0; j + 1u < products[e].size(); j += 2u)
                products[e + 1u][j >> 1] = products[e][j] * products[e][j + 1u];
        }

        uint32_t i;
        int j;
        for (char c; k > 0 && cin >> c >> i >> j; --k) {
            i -= 1;
            if (c == 'C') {
                products[0][i] = (j < 0) ? -1 : ((j == 0) ? 0 : 1);
                for (uint8_t e = 0; e + 1u < products.size() && (i ^ 1u) < products[e].size(); ++e, i /= 2)
                    products[e + 1u][i >> 1] = products[e][i] * products[e][i ^ 1u];
            }
            else {
                int8_t product = 1, e = 0;
                uint32_t length = uint32_t(j) - i, len = 1;
                for (; len < length; ++e, len <<= 1)
                    if ((i & len) != 0) {
                        product *= products[e][i >> e];
                        i += len;
                        length -= len;
                    }
                for (; e >= 0; --e, len >>= 1)
                    if (len <= length) {
                        product *= products[e][i >> e];
                        i += len;
                        length -= len;
                    }
                cout << ((product < 0) ? '-' : ((product == 0) ? '0' : '+'));
            }
        }
        cout << endl;
    }

    return 0;
}
