// #breadth_first_search #easy
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    uint16_t e;
    cin >> e;
    vector<vector<uint16_t>> friends(e);

    for (auto &fs: friends) {
        uint16_t n;
        cin >> n;
        fs.resize(n);
        for (auto &f: fs)
            cin >> f;
    }

    uint16_t t;
    vector<bool> has_heard;
    vector<uint16_t> q, qnext;
    for (cin >> t; t > 0; --t) {
        uint16_t source;
        cin >> source;

        has_heard.assign(e, false);
        has_heard[source] = true;

        uint16_t m = 0, d = 0;
        q.assign(friends[source].begin(), friends[source].end());
        for (uint16_t day = 1; q.size() > 0; ++day, q.swap(qnext)) {
            uint16_t boom_size = 0;
            qnext.clear();
            for (uint16_t e: q)
                if (!has_heard[e]) {
                    has_heard[e] = true;
                    ++boom_size;
                    qnext.insert(qnext.end(), friends[e].begin(), friends[e].end());
                }
            if (boom_size > m) {
                m = boom_size;
                d = day;
            }
        }

        if (m == 0)
            cout << 0 << endl;
        else
            cout << m << " " << d << endl;
    }


    return 0;
}
