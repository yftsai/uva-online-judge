#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<double, double> position;

// assume p < q && q < r
bool is_collinear(const position &p, const position &q, const position &r)
{
    constexpr double eps = 1E-8;
    if (p.first == q.first)
        return p.first == r.first;
    else {
        const auto second = p.second + (q.second - p.second) / (q.first - p.first) * (r.first - p.first);
        return second - eps < r.second && r.second < second + eps;
    }
}

int main()
{
    vector<position> positions;

    uint16_t t;
    cin >> t;
    for (uint16_t dsn = 1, n; dsn <= t && cin >> n; ++dsn) {
        positions.resize(n);
        for (auto &p: positions)
            cin >> p.first >> p.second;
        sort(positions.begin(), positions.end());
        positions.erase(unique(positions.begin(), positions.end()), positions.end());

        uint16_t max_aligned_count = 0;
        for (uint16_t i = 0; i < positions.size(); ++i)
            for (uint16_t j = i + 1; j < positions.size(); ++j) {
                uint16_t aligned_count = 2;
                for (uint16_t k = j + 1; k < positions.size(); ++k)
                    if (is_collinear(positions[i], positions[j], positions[k]))
                        ++aligned_count;
                max_aligned_count = max(max_aligned_count, aligned_count);
            }

        cout << "Data set #" << dsn << " contains ";
        if (positions.size() == 1)
            cout << "a single gnu." << endl;
        else
            cout << positions.size() << " gnus, out of which a maximum of "
                << max_aligned_count << " are aligned." << endl;
    }

    return 0;
}
