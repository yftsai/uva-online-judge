#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct order
{
    int start, destination;
    int passenger_count;
};

void maximize_earning(const vector<order> &orders, uint16_t order_index, vector<int> &capacities, int earning, int potential_earning, int *max_earning)
{
    if (order_index < orders.size() && earning + potential_earning > *max_earning) {
        auto &o = orders[order_index];
        const int e = (o.destination - o.start) * o.passenger_count;
        bool is_acceptable = all_of(capacities.begin() + o.start, capacities.begin() + o.destination, [p=o.passenger_count](int c) { return c >= p; });
        potential_earning -= e;
        if (is_acceptable) {
            for_each(capacities.begin() + o.start, capacities.begin() + o.destination, [p = o.passenger_count](int &c) { c -= p; });
            earning += e;

            *max_earning = max(*max_earning, earning);
            maximize_earning(orders, order_index + 1u, capacities, earning, potential_earning, max_earning);

            earning -= e;
            for_each(capacities.begin() + o.start, capacities.begin() + o.destination, [p = o.passenger_count](int &c) { c += p; });
        }
        maximize_earning(orders, order_index + 1u, capacities, earning, potential_earning, max_earning);
        potential_earning += e;
    }
}

int main()
{
    vector<int> capacities;
    vector<order> orders;
    for (int n, station_count, order_count; cin >> n >> station_count >> order_count && station_count != 0; ) {
        capacities.assign(station_count, n);
        orders.resize(order_count);
        int potential_earning = 0;
        for (auto &o: orders) {
            cin >> o.start >> o.destination >> o.passenger_count;
            potential_earning += (o.destination - o.start) * o.passenger_count;
        }
        int max_earning = 0;
        maximize_earning(orders, 0, capacities, 0, potential_earning, &max_earning);
        cout << max_earning << endl;
    }
    return 0;
}
