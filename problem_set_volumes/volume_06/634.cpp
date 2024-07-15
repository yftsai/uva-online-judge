// #geometry
#include <iostream>
#include <vector>
using namespace std;

typedef pair<int16_t, int16_t> point;

int main()
{
    constexpr int16_t inf = 10001;
    vector<point> polygon;

    for (uint16_t n; cin >> n && n > 0; ) {
        polygon.resize(n);
        for (auto &v: polygon)
            cin >> v.first >> v.second;
        point p;
        cin >> p.first >> p.second;

        // check the intersection with (p.x, p.y) - (10001, inf)
        bool even_count = true;
        polygon.push_back(polygon.front());
        for (uint16_t i = 0; i < n; i++) {
            const auto &v = polygon[i], &w = polygon[i + 1];
            if (v.first == w.first && p.first <= v.first && v.first < inf) {
                if (v.second <= p.second && p.second <= w.second)
                    even_count = !even_count;
                else if (v.second >= p.second && p.second >= w.second)
                    even_count = !even_count;
            }
        }

        cout << (even_count ? 'F' : 'T') << endl;
    }

    return 0;
}
