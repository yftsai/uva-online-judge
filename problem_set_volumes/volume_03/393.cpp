// #geometry #dynamic_programming
#include <iostream>
#include <map>
#include <cmath>
#include <limits>
using namespace std;

typedef pair<double, double> point;

struct path_set
{
    point source;
    pair<double, double> vector_ys;
        // represents two vectors (1, vector_ys.first) and (1, vector_ys.second)
        // where vector_ys.first <= vector_ys.second

    path_set(pair<double, double> s, double low_vy, double high_vy):
        source(s),
        vector_ys(low_vy, high_vy)
    {}

    pair<double, double> end_at(double x) const
    {
        const double dx = x - source.first;
        const pair<double, double> ys(
            source.second + vector_ys.first * dx,
            source.second + vector_ys.second * dx);
        return ys;
    }

    bool operator<(const path_set &ps) const
    {
        if (source != ps.source)
            return source < ps.source;
        else
            return vector_ys < ps.vector_ys;
    }
};

double get_distance(const point p, const point q)
{
    return sqrt(pow(p.first - q.first, 2) + pow(p.second - q.second, 2));
}

int main()
{
    constexpr double inf = numeric_limits<double>::infinity();

    cout.setf(ios::fixed);
    cout.precision(2);

    for (int n; cin >> n && n >= 0; ) {
        map<path_set, double> lengths;
        lengths.emplace(path_set(point(0, 5), -inf, inf), 0);

        double x;
        for (int i = 0; i < n && cin >> x; i++) {
            double ys[4];
            for (auto &y: ys)
                cin >> y;

            map<path_set, double> updated_lengths;
            for (const auto &ps_len: lengths) {
                const auto &source = ps_len.first.source;
                const double dx = x - source.first;
                const auto proj_ys = ps_len.first.end_at(x);

                for (uint16_t j = 0; j < 4; j += 2) {
                    const double restricted_ys[2] = {
                        max(ys[j],     proj_ys.first),
                        min(ys[j + 1], proj_ys.second) };

                    if (restricted_ys[0] <= restricted_ys[1]) {
                        const path_set ps(source,
                            (restricted_ys[0] - source.second) / dx,
                            (restricted_ys[1] - source.second) / dx);

                        auto it = updated_lengths.lower_bound(ps);
                        if (it == updated_lengths.end() || ps < it->first)
                            updated_lengths.emplace_hint(it, ps, ps_len.second);
                        else
                            it->second = min(it->second, ps_len.second);

                        for (uint16_t k = 0; k < 2; k++)
                            if (restricted_ys[k] == ys[j + k]) {
                                const point p(x, ys[j + k]);
                                const double len = ps_len.second + get_distance(source, p);
                                const path_set ps(p, -inf, inf);

                                auto it = updated_lengths.lower_bound(ps);
                                if (it == updated_lengths.end() || ps < it->first)
                                    updated_lengths.emplace_hint(it, ps, len);
                                else
                                    it->second = min(it->second, len);
                            }
                    }
                }
            }

            lengths.swap(updated_lengths);
        }

        double min_length = numeric_limits<double>::max();
        const point end(10, 5);
        for (const auto &ps_len: lengths) {
            auto ys = ps_len.first.end_at(10);
            if (ys.first <= 5 && 5 <= ys.second) {
                const double dlen = get_distance(ps_len.first.source, end);
                min_length = min(min_length, ps_len.second + dlen);
            }
        }
        cout << min_length << endl;
    }

    return 0;
}
