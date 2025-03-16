// #greedy
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

constexpr double eps = pow(0.1, 64);

struct island
{
    int32_t x;
    uint32_t y;
    double dx;

    bool operator<(const island &i) const;
};

bool island::operator<(const island &i) const
{
    if (x != i.x)
        return x < i.x;
    else
        return y < i.y;
}

double get_leftest_radar(uint32_t d, const island *islands, uint32_t n)
{
    double x = islands[0].x + islands[0].dx;
    for (uint32_t i = 1; i < n && islands[i].x <= x + eps; i++)
        x = min(islands[i].x + islands[i].dx, x);
            // x is updated when islands[i] has a strictly smaller x-axis range
            // than the range of islands[0]. Therefore, islands[i] does not
            // covered by known radars.
    return x;
}

int main()
{
    vector<island> islands;

    for (uint32_t n, d, cno = 1; cin >> n >> d && n > 0; cno++) {
        bool has_solution = true;

        islands.resize(n);
        for (auto &i: islands) {
            cin >> i.x >> i.y;
            if (i.y > d)
                has_solution = false;
            else
                i.dx = sqrt(pow(d, 2) - pow(i.y, 2));
        }

        cout << "Case " << cno << ": ";
        if (!has_solution)
            cout << -1 << endl;
        else {
            sort(islands.begin(), islands.end());

            double x = get_leftest_radar(d, islands.data(), n);
            uint32_t count = 1;
            for (uint32_t i = 0; i < n; i++)
                if (x + eps < islands[i].x - islands[i].dx) {
                    x = get_leftest_radar(d, islands.data() + i, n - i);
                    count++;
                }

            cout << count << endl;
        }
    }

    return 0;
}
