#include <iostream>
#include <set>
using namespace std;

int main()
{
    multiset<uint32_t> small_bills, large_bills;
    
    for (uint16_t n; cin >> n && n > 0; small_bills.clear(), large_bills.clear()){
        uint64_t amount = 0;
        for (; n > 0; --n) {
            uint32_t k;
            cin >> k;
            for (uint32_t j = 0, b; j < k && cin >> b; ++j) {
                if (small_bills.size() < n || b < *(--small_bills.end()))
                    small_bills.insert(b);
                else
                    large_bills.insert(b);
                if (small_bills.size() > n) {
                    large_bills.insert(large_bills.begin(), *(--small_bills.end()));
                    small_bills.erase(--small_bills.end());
                }
                if (large_bills.size() > n)
                    large_bills.erase(large_bills.begin());
            }

            auto &bills = (large_bills.size() > 0) ? large_bills : small_bills;
            amount += *(--bills.end()) - *small_bills.begin();
            bills.erase(--bills.end());
            small_bills.erase(small_bills.begin());
        }
        cout << amount << endl;
    }

    return 0;
}
