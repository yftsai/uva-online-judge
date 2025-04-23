// #dynamic_programming
#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

typedef pair<int16_t, int16_t> location;
typedef vector<vector<uint16_t>> times;

void move(location m, location loc, queue<location> &q, times &tsleep, times &tawake)
{
    const uint16_t r = tsleep.size();
    const uint16_t c = tsleep[0].size();
    const uint16_t invalid = r * c * 4;
    static const location vecs[8] = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        { 1, -2}, { 1, 2}, { 2, -1}, { 2, 1} };

    auto add = [](location loc, location v) {
        return location(loc.first + v.first, loc.second + v.second);
    };
    auto is_valid = [r, c](location loc) {
        return 0 <= loc.first && loc.first < r && 0 <= loc.second && loc.second < c;
    };


    for (auto &ts: tsleep)
        fill(ts.begin(), ts.end(), invalid);
    for (auto &ts: tawake)
        fill(ts.begin(), ts.end(), invalid);

    tsleep[loc.first][loc.second] = 0;

    q.emplace(loc);
    while (!q.empty()) {
        loc = q.front();
        q.pop();

        uint16_t t = tsleep[loc.first][loc.second];
        if (loc != m)
            for (auto &v: vecs) {
                location loc_n = add(loc, v);
                if (is_valid(loc_n) && t + 1 < tsleep[loc_n.first][loc_n.second]) {
                    tsleep[loc_n.first][loc_n.second] = t + 1;
                    q.emplace(loc_n);
                }
            }
    }

    if (tsleep[m.first][m.second] < invalid) {
        tawake[m.first][m.second] = tsleep[m.first][m.second];
        q.emplace(m);
    }

    while (!q.empty()) {
        loc = q.front();
        q.pop();

        uint16_t t = tawake[loc.first][loc.second];
        for (auto &v: vecs) {
            location loc_n = add(loc, v);
            if (is_valid(loc_n) && t + 1 < tawake[loc_n.first][loc_n.second]) {
                tawake[loc_n.first][loc_n.second] = t + 1;
                q.emplace(loc_n);
            }
        }
    }

    tawake[m.first][m.second] = invalid;
}

int main()
{
    times tsmin, tamin, tsleep, tawake;
    queue<location> q;

    for (string s; cin >> s; ) {
        int16_t r, c;
        location locs[4];
        location m;

        cin >> r >> c;
        for (auto &loc: locs) {
            cin >> loc.first >> loc.second;
            loc.first--;
            loc.second--;
        }
        cin >> m.first >> m.second;
        m.first--;
        m.second--;

        const uint16_t invalid = r * c * 4;
        tsmin.resize(r);
        tamin.resize(r);
        for (uint16_t i = 0; i < r; i++) {
            tsmin[i].resize(c);
            tamin[i].resize(c);
        }
        move(m, locs[0], q, tsmin, tamin);

        tsleep.resize(r);
        tawake.resize(r);
        for (uint16_t i = 0; i < r; i++) {
            tsleep[i].resize(c);
            tawake[i].resize(c);
        }
        for (uint16_t k = 1; k < 4; k++) {
            move(m, locs[k], q, tsleep, tawake);
            for (uint16_t i = 0; i < r; i++)
                for (uint16_t j = 0; j < c; j++) {
                    tamin[i][j] = min<uint16_t>(tsmin[i][j] + tawake[i][j], tamin[i][j] + tsleep[i][j]);
                    tamin[i][j] = min<uint16_t>(tamin[i][j], invalid);
                    tsmin[i][j] = min<uint16_t>(tsmin[i][j] + tsleep[i][j], invalid);
                }
        }

        uint16_t tmeet = invalid;
        for (uint16_t i = 0; i < r; i++)
            for (uint16_t j = 0; j < c; j++)
                if (i != m.first || j != m.second)
                    tmeet = min(min(tsmin[i][j], tamin[i][j]), tmeet);

        cout << s << endl;
        if (tmeet >= invalid)
            cout << "Meeting is impossible." << endl;
        else
            cout << "Minimum time required is " << tmeet << " minutes." << endl;
    }

    return 0;
}
