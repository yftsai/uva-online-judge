// #minimum_spanning_tree
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct edge
{
    int x, y, z;

    bool operator<(const struct edge &e) const
    {
        return z < e.z;
    }
};

int main()
{
    vector<edge> edges;
    vector<int> reps;
    auto get_rep = [&reps](int i) {
        int j;
        for (j = reps[i]; reps[j] != j; j = reps[j])
            ;
        for (int k; i != j; i = k) {
            k = reps[i];
            reps[i] = j;
        }
        return j;
    };

    for (int m, n; cin >> m >> n && m > 0; ) {
        int road_length = 0;
        edges.resize(n);
        for (int i = 0; i < n && cin >> edges[i].x >> edges[i].y >> edges[i].z; i++)
            road_length += edges[i].z;
        sort(edges.begin(), edges.end());

        reps.resize(m);
        iota(reps.begin(), reps.end(), 0);

        int min_length = 0;
        for (const edge &e: edges) {
            int x = get_rep(e.x), y = get_rep(e.y);
            if (x != y) {
                min_length += e.z;
                reps[y] = x;
            }
        }
        cout << (road_length - min_length) << endl;
    }

    return 0;
}
