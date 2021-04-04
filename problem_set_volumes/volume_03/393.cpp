// #geometry #dynamic_programming
#include <iostream>
#include <map>
#include <cmath>
#include <limits>
using namespace std;

typedef pair<double, double> point;

struct segment
{
    point source;
    pair<double, double> vector_ys;

    segment(pair<double, double> s, double low_vy, double high_vy):
        source(s),
        vector_ys(low_vy, high_vy)
    {}

    pair<double, double> project(double x) const
    {
        const double dx = x - source.first;
        pair<double, double> ys(
            source.second + vector_ys.first * dx,
            source.second + vector_ys.second * dx);
        return ys;
    }

    bool operator<(const segment &s) const
    {
        if (source != s.source)
            return source < s.source;
        else
            return vector_ys < s.vector_ys;
    }
};

double get_distance(const point p, const point q)
{
    return sqrt(pow(p.first - q.first, 2) + pow(p.second - q.second, 2));
}

int main()
{
    constexpr double pi = acos(-1);
    constexpr double inf = numeric_limits<double>::infinity();

    cout.setf(ios::fixed);
    cout.precision(2);

    int n;
    for (int n; cin >> n && n >= 0; ) {
        map<segment, double> lengths;
        lengths.emplace(segment(point(0, 5), -inf, inf), 0);

        double x;
        for (int i = 0; i < n && cin >> x; i++) {
            double ys[4];
            for (auto &y: ys)
                cin >> y;

            map<segment, double> updated_lengths;
            for (const auto &s: lengths) {
                const auto &source = s.first.source;
                const double dx = x - source.first;
                const auto proj_ys = s.first.project(x);

                for (uint16_t j = 0; j < 4; j += 2) {
                    const double restricted_ys[2] = {
                        max(ys[j],     proj_ys.first),
                        min(ys[j + 1], proj_ys.second) };

                    if (restricted_ys[0] <= restricted_ys[1]) {
                        const segment t(source,
                            (restricted_ys[0] - source.second) / dx,
                            (restricted_ys[1] - source.second) / dx);

                        auto it = updated_lengths.lower_bound(t);
                        if (it == updated_lengths.end() || t < it->first)
                            updated_lengths.emplace_hint(it, t, s.second);
                        else
                            it->second = min(it->second, s.second);

                        for (uint16_t k = 0; k < 2; k++)
                            if (restricted_ys[k] == ys[j + k]) {
                                const point p(x, ys[j + k]);
                                const double len = s.second + get_distance(source, p);
                                const segment t(p, -inf, inf);

                                auto it = updated_lengths.lower_bound(t);
                                if (it == updated_lengths.end() || t < it->first)
                                    updated_lengths.emplace_hint(it, t, len);
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
        for (const auto s: lengths) {
            auto ys = s.first.project(10);
            if (ys.first <= 5 && 5 <= ys.second) {
                const double dlen = get_distance(s.first.source, end);
                min_length = min(min_length, s.second + dlen);
            }
        }
        cout << min_length << endl;
    }
    return 0;
}
