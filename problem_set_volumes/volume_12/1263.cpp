// #strongly_connected_component
#include <iostream>
#include <vector>
using namespace std;

void explode(const vector<vector<uint16_t>> &outs, vector<bool> &is_exploded, uint16_t m)
{
    if (!is_exploded[m]) {
        is_exploded[m] = true;
        for (const uint16_t n: outs[m])
            explode(outs, is_exploded, n);
    }
}

struct mine
{
    int x, y, d;

    bool trigger(const mine &m) const
    {
        return x - d <= m.x && m.x <= x + d
            && y - d <= m.y && m.y <= y + d;
    }
};


int main()
{
    constexpr uint16_t max_n = 2000;
    uint32_t t;
    uint16_t n;
    vector<mine> mines(max_n);
    vector<vector<uint16_t>> outs(max_n);
    vector<bool> is_exploded(max_n);
    vector<uint16_t> inits(max_n);

    for (cin >> t; t > 0 && cin >> n; t--) {
        mines.resize(n);
        outs.resize(n);

        for (uint16_t i = 0; i < n && cin >> mines[i].x >> mines[i].y >> mines[i].d; i++) {
            mines[i].x *= 2;
            mines[i].y *= 2;
            outs[i].clear();
            for (uint16_t j = 0; j < i; j++) {
                if (mines[j].trigger(mines[i]))
                    outs[j].push_back(i);
                if (mines[i].trigger(mines[j]))
                    outs[i].push_back(j);
            }
        }

        is_exploded.assign(n, false);
        inits.clear();
        for (uint16_t i = 0; i < n; i++)
            if (!is_exploded[i]) {
                inits.push_back(i);
                explode(outs, is_exploded, i);
            }
        is_exploded.assign(n, false);
        uint16_t init_count = 0;
        for (; inits.size() > 0; inits.pop_back())
            if (!is_exploded[inits.back()]) {
                init_count++;
                explode(outs, is_exploded, inits.back());
            }
        cout << init_count << endl;
    }
    return 0;
}
