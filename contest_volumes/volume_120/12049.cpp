// #trivial
#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{
    uint16_t t, n, m;
    unordered_map<int32_t, uint16_t> counts(20011);
    for (cin >> t; t > 0 && cin >> n >> m; t--) {
        int number;
        counts.clear();
        for (uint16_t i = 0; i < n && cin >> number; i++)
            counts.emplace(number, 0).first->second++;

        uint16_t remove_count = n;
        for (uint16_t i = 0; i < m && cin >> number; i++) {
            auto it = counts.find(number);
            if (it == counts.end() || it->second == 0)
                remove_count++;
            else
                it->second--, remove_count--;
        }

        cout << remove_count << endl;
    }

    return 0;
}
