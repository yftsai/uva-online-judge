// #dynamic_programming #breadth_first_search
#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct crossing
{
    uint32_t block_count;
    uint32_t path_count;

    crossing(uint32_t b, uint32_t p):
        block_count(b), path_count(p)   {}
};

int main()
{
    vector<vector<crossing>> crossings;

    string line;
    stringstream ss;
    getline(cin, line);
    const int case_count = stoi(line);

    for (int case_n = 0; case_n < case_count; case_n++) {
        getline(cin, line);

        int32_t w, n;
        getline(cin, line);
        ss.str(line);
        ss.clear();
        ss >> w >> n;

        const uint32_t MAX_BLOCK_COUNT = w + n - 2;
        const uint32_t UNKNOWN = w + n;
        const uint32_t UNSAFE  = w + n + 1;
        crossings.resize(w);
        for (auto &cs: crossings)
            cs.assign(n, crossing(UNKNOWN, 0));

        for (int32_t i = 0, j; i < w && getline(cin, line); i++) {
            ss.str(line);
            ss.clear();
            for (ss >> j; ss >> j; )
                crossings[i][j - 1].block_count = UNSAFE;
        }
        crossings[0][0].block_count = 0;
        crossings[0][0].path_count  = 1;

        typedef pair<int32_t, int32_t> position;
        queue<position> q;
        q.emplace(0, 0);

        while (!q.empty()) {
            const position p = q.front();
            const auto &cp = crossings[p.first][p.second];
            q.pop();

            const pair<int16_t, int16_t> shifts[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
            for (auto &s: shifts) {
                const position r(p.first + s.first, p.second + s.second);
                if (0 > r.first || r.first >= w || 0 > r.second || r.second >= n)
                    continue;

                auto &cr = crossings[r.first][r.second];
                if (cr.block_count == UNKNOWN) {
                    cr = cp;
                    cr.block_count += 1;
                    if (cr.block_count <= MAX_BLOCK_COUNT)
                        q.push(r);
                } else if (cp.block_count + 1 == cr.block_count) {
                    cr.path_count += cp.path_count;
                }
            }
        }

        if (case_n > 0)
            cout << endl;
        cout << crossings.back().back().path_count << endl;
    }

    return 0;
}
