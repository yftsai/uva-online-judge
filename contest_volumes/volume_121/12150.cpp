// #trivial
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<uint16_t> order;
    for (uint16_t n; cin >> n && n > 0; order.clear()) {
        order.resize(n, 0);
        uint32_t p;
        bool is_valid = true;
        for (uint16_t i = 0, c; i < n && cin >> c >> p; i++) {
            p += i;
            if (0 <= p && p < n && order[p] == 0)
                order[p] = c;
            else
                is_valid = false;
        }

        if (!is_valid)
            cout << -1 << endl;
        else {
            for (uint16_t i = 0; i < n; i++)
                cout << (i == 0 ? "" : " ") << order[i];
            cout << endl;
        }
    }

    return 0;
}
