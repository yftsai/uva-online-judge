// #sort
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

uint16_t get_kth(uint16_t *data, uint16_t size, uint16_t k)
{
    while (true) {
        swap(data[size / 2], data[size - 1]);
        auto m = partition(data, data + size - 1,
            [&](const uint16_t d) { return d < data[size - 1]; }) - data;

        if (k < m)
            size = m;
        else if (k == m)
            return data[size - 1];
        else {
            swap(data[m], data[size - 1]);
            data += m + 1;
            size -= m + 1;
            k -= m + 1;
        }
    }
}

int main()
{
    vector<uint16_t> xs(50000), ys(50000);

    uint32_t t, s, a, f;
    for (cin >> t; t > 0 && cin >> s >> a >> f; --t) {
        xs.resize(f);
        ys.resize(f);
        for (uint16_t i = 0; i < f; ++i)
            cin >> xs[i] >> ys[i];

        cout << "(Street: "  << get_kth(xs.data(), f, (f - 1) / 2)
             << ", Avenue: " << get_kth(ys.data(), f, (f - 1) / 2) << ")" << endl;
    }

    return 0;
}
