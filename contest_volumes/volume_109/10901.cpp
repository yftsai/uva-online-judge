#include <iostream>
#include <string>
#include <queue>
#include <limits>
using namespace std;

struct car
{
    uint32_t id;
    uint32_t atime;
    bool is_on_left;
};

int main()
{
    uint32_t c;
    string bank;
    queue<car> lq, rq;
    priority_queue<pair<uint32_t, uint32_t>> output_pq;     // id, unloaded time

    for (cin >> c; c > 0; --c) {
        uint16_t n, t, m;
        cin >> n >> t >> m;

        uint32_t last_car_arrival_time, ferry_time = 0;
        bool is_ferry_on_left = true;
        uint16_t next_output_id = m;

        while (m > 0 || !lq.empty() || !rq.empty()) {
            auto &q = is_ferry_on_left ? lq : rq;
            auto &r = is_ferry_on_left ? rq : lq;

            if (m > 0 && ((lq.empty() && rq.empty()) || last_car_arrival_time <= ferry_time)) {
                car c;
                c.id = m--;
                cin >> c.atime >> bank;
                c.is_on_left = (bank == "left");

                (c.is_on_left ? lq : rq).push(c);
                last_car_arrival_time = c.atime;
            }
            else if ((q.empty() || ferry_time < q.front().atime)
                  && (r.empty() || ferry_time < r.front().atime)) {
               ferry_time = min(q.empty() ? numeric_limits<uint32_t>::max() : q.front().atime,
                                r.empty() ? numeric_limits<uint32_t>::max() : r.front().atime);
            }
            else {
                for (uint16_t i = 0; i < n && !q.empty() && q.front().atime <= ferry_time; ++i, q.pop()) {
                    output_pq.emplace(q.front().id, ferry_time + t);

                    while (output_pq.size() > 0 && output_pq.top().first == next_output_id) {
                        cout << output_pq.top().second << endl;
                        output_pq.pop();
                        --next_output_id;
                    }
                }
                is_ferry_on_left = !is_ferry_on_left;
                ferry_time += t;
            }
        }

        if (c > 1)
            cout << endl;
    }

    return 0;
}
