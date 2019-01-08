// #minimum_spanning_tree
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
using namespace std;

struct connection
{
    int a, b, c;
    bool operator<(const connection &conn) const
    {
        return c < conn.c;
    };
};

int get_representative(vector<int> &reps, int a)
{
    int ra = reps[a];
    for (; ra != reps[ra]; ra = reps[ra])
        ;
    for (int r = reps[a], s; r != ra; r = s) {
        s = reps[r];
        reps[r] = ra;
    }
    return ra;
}

int main()
{
    vector<int> reps;
    vector<vector<int>> max_conns;
    vector<connection> conns, mst_conns;

    int t;
    for (cin >> t; t > 0; t--) {
        int n, m;
        cin >> n >> m;
        reps.resize(n + 1);
        iota(reps.begin(), reps.end(), 0);

        conns.resize(m);
        for (auto &conn: conns)
            cin >> conn.a >> conn.b >> conn.c;
        sort(conns.begin(), conns.end());

        mst_conns.clear();
        for (size_t i = 0; i < conns.size(); ++i) {
            const int ra = get_representative(reps, conns[i].a);
            const int rb = get_representative(reps, conns[i].b);
            if (ra != rb) {
                mst_conns.push_back(conns[i]);
                reps[ra] = rb;
            }
            else
                swap(conns[i], conns[i - mst_conns.size()]);
        }
        conns.resize(conns.size() - mst_conns.size());

        int s1 = 0;
        for (auto &conn: mst_conns)
            s1 += conn.c;

        int s2 = numeric_limits<int>::max();
        for (const connection &conn: conns) {
            int s = conn.c;
            iota(reps.begin(), reps.end(), 0);
            reps[conn.a] = conn.b;
            for (const connection &mst_conn: mst_conns) {
                const int ra = get_representative(reps, mst_conn.a);
                const int rb = get_representative(reps, mst_conn.b);
                if (ra != rb) {
                    s += mst_conn.c;
                    reps[ra] = rb;
                }
            }
            s2 = min(s2, s);
        }

        cout << s1 << " " << s2 << endl;
    }
    return 0;
}
