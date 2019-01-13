// #travelling_salesman
#include <iostream>
#include <vector>
#include <cstdlib>
#include <limits>
using namespace std;

int main()
{
    typedef pair<int, int> position;
    vector<position> positions;
    auto get_distance = [&positions](const position &p, const position &q) {
        return abs(p.first - q.first) + abs(p.second - q.second);
    };
    vector<int> lengths;

    int case_count;
    for (cin >> case_count; case_count > 0; --case_count) {
        int n;
        pair<int, int> start;
        positions.resize(1);
        cin >> start.first >> start.second;
        cin >> start.first >> start.second >> n;

        lengths.assign((1 << (n + 4 + 1)) + n, numeric_limits<int>::max());
        positions.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> positions[i].first >> positions[i].second;
            lengths[(1u << (i + 4)) + i] = get_distance(start, positions[i]);
        }

        for (int mask = 1; mask < (1 << n); ++mask)
            for (int end = 0; end < n; ++end)
                if (mask & (1u << end)) {
                    int p = (mask << 4) + end;
                    for (int e = 0, m = 1; e < n; ++e, m <<= 1)
                        if ((mask & m) == 0) {
                            int q = ((mask | m) << 4) + e;
                            lengths[q] = min(lengths[q], lengths[p] + get_distance(positions[end], positions[e]));
                        }
                }

        int length = (n == 0) ? 0 : numeric_limits<int>::max();
        for (int e = 0; e < n; ++e)
            length = min(length, lengths[(((1u << n) - 1) << 4) + e] + get_distance(positions[e], start));
        cout << "The shortest path has length " << length << endl;
    }
    return 0;
}
