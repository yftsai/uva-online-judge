// #shortest_path
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int c, n, m;
    for (cin >> c; c > 0 && cin >> n >> m; c--) {
        int16_t wormholes[m][3];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < 3; j++)
                cin >> wormholes[i][j];
        int distances[m];
        fill(distances, distances + m, 1000 * m);
        for (int i = 1; i < n; i++)
            for (int j = 0; j < m; j++) {
                const int16_t x = wormholes[j][0], y = wormholes[j][1], t = wormholes[j][2];
                distances[y] = min(distances[x] + t, distances[y]);
            }
        auto is_negative_cycle = [&distances](decltype(wormholes[0]) &wormhole) {
            const auto x = wormhole[0], y = wormhole[1], t = wormhole[2];
            return distances[x] + t < distances[y];
        };
        bool has_negative_cycle = any_of(wormholes, wormholes + m, is_negative_cycle);
        cout << (has_negative_cycle ? "possible" : "not possible") << endl;
    }

    return 0;
}
