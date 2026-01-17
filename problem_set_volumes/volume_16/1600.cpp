// #easy
#include <bitset>
#include <cstdint>
#include <iostream>
#include <queue>
using namespace std;

struct state
{
    int16_t x, y;
    uint16_t k;
    int16_t moves;
};

int main()
{
    bitset<400> obstacles;
    bitset<400> visited[21];

    uint32_t ds_count;
    int16_t m, n;
    uint16_t k;
    for (cin >> ds_count; ds_count > 0 && cin >> m >> n >> k; ds_count--) {
        obstacles.reset();
        for (int16_t i = 0; i < m; i++)
            for (int16_t j = 0, o; j < n && cin >> o; j++)
                if (o == 1)
                    obstacles.set(n * i + j);

        for (uint16_t i = 0; i <= k; i++)
            visited[i].reset();

        queue<state> q;

        auto enqueue = [&](const state s) -> int16_t {
            uint16_t index = n * s.x + s.y;
            if (s.x == m - 1 && s.y == n - 1)
                return s.moves;
            else {
                visited[s.k].set(index);
                q.emplace(s);
                return -1;
            }
        };

        auto move = [&](const state &s, int16_t dx, int16_t dy) -> int16_t {
            int16_t tx = s.x + dx;
            if (0 > tx || tx >= m) return -1;

            int16_t ty = s.y + dy;
            if (0 > ty || ty >= n) return -1;

            uint16_t index = n * tx + ty;
            uint16_t tk = obstacles[index] ? s.k + 1 : 0;
            if (tk > k) return -1;

            int16_t tmoves = s.moves + 1;
            if (tk > k || visited[tk][index])
                return -1;
            else
                return enqueue(state{tx, ty, tk, tmoves});
        };

        state s{0, 0, 0, 0};
        int16_t moves = enqueue(s);

        while (!q.empty() && moves < 0) {
            s = q.front();
            q.pop();

            if (moves < 0) moves = move(s, -1,  0);
            if (moves < 0) moves = move(s,  1,  0);
            if (moves < 0) moves = move(s,  0, -1);
            if (moves < 0) moves = move(s,  0,  1);
        }
        cout << moves << endl;
    }

    return 0;
}
