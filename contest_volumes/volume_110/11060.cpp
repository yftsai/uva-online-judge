// #topological_sort
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct beverage
{
    string name;
    uint16_t input_index;
    vector<uint16_t> orders;
    uint16_t pred_count;

    bool operator<(const beverage &b) const
    {
        return name < b.name;
    }
};

int main()
{
    vector<beverage> beverages;
    string b1, b2;
    vector<pair<int16_t, uint16_t>> heap;

    auto get_index = [&beverages](const string &name) {
        auto by_name = [&name](const beverage &b) { return b.name == name; };
        return find_if(beverages.begin(), beverages.end(), by_name) - beverages.begin();
    };

    for (uint16_t number = 1, n; cin >> n; ++number) {
        beverages.resize(n);
        for (uint16_t i = 0; i < n && cin >> beverages[i].name; ++i) {
            beverages[i].input_index = i;
            beverages[i].orders.clear();
            beverages[i].pred_count = 0;
        }
        sort(beverages.begin(), beverages.end());

        uint16_t m;
        cin >> m;
        for (uint16_t i = 0; i < m && cin >> b1 >> b2; ++i) {
            const uint16_t b = get_index(b1);
            const uint16_t c = get_index(b2);
            beverages[b].orders.push_back(c);
            ++beverages[c].pred_count;
        }

        heap.clear();
        for (uint16_t i = 0; i < n; ++i)
            if (beverages[i].pred_count == 0)
                heap.emplace_back(-beverages[i].input_index, i);
        make_heap(heap.begin(), heap.end());

        cout << "Case #" << number << ": ";
        cout << "Dilbert should drink beverages in this order:";
        while (!heap.empty()) {
            const uint16_t i = heap.front().second;
            pop_heap(heap.begin(), heap.end());
            heap.pop_back();

            cout << " " << beverages[i].name;
            for (const uint16_t j: beverages[i].orders)
                if (--beverages[j].pred_count == 0) {
                    heap.emplace_back(-beverages[j].input_index, j);
                    push_heap(heap.begin(), heap.end());
                }
        }
        cout << "." << endl;
        cout << endl;
    }

    return 0;
}
