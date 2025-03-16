// #priority_queue
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    uint32_t ncases, n;
    vector<pair<uint16_t, uint32_t>> orders;
    auto cmp = [](const pair<uint16_t, uint32_t> &o1, const pair<uint16_t, uint32_t> &o2) {
        if (o1.second != o2.second)
            return o1.second > o2.second;
        else
            return o1.first < o2.first;
    };

    for (cin >> ncases; ncases > 0 && cin >> n; ncases--) {
        orders.resize(n);
        for (auto &o: orders)
            cin >> o.first >> o.second;
        make_heap(orders.begin(), orders.end(), cmp);

        priority_queue<uint16_t> amounts;
        uint32_t due = 0;
        while (!orders.empty()) {
            pop_heap(orders.begin(), orders.end(), cmp);
            auto o = orders.back();
            orders.pop_back();
            if (due + o.first <= o.second) {
                due += o.first;
                amounts.push(o.first);
            }
            else if (amounts.size() > 0 && amounts.top() > o.first
                  && due - amounts.top() + o.first <= o.second) {
                due = due - amounts.top() + o.first;
                amounts.pop();
                amounts.push(o.first);
            }
        }

        cout << amounts.size() << endl;
        if (ncases > 1)
            cout << endl;
    }

    return 0;
}
