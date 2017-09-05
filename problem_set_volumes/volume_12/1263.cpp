// #depth_first_search #strongly_connected_component
#include <iostream>
#include <vector>
using namespace std;

void explode(const vector<vector<int>> &outs, vector<bool> &is_exploded, int m)
{
    if (!is_exploded[m]) {
        is_exploded[m] = true;
        for (int n: outs[m])
            explode(outs, is_exploded, n);
    }
}

int main()
{
    int t, n;
    for (cin >> t; t > 0; t--) {
        cin >> n;
        vector<int> xs(n), ys(n), ds(n);
        vector<vector<int>> outs(n);
        for (int i = 0; i < n; i++) {
            cin >> xs[i] >> ys[i] >> ds[i];
            xs[i] *= 2;
            ys[i] *= 2;
            for (int j = 0; j < i; j++) {
                if (xs[j] - ds[j] <= xs[i] && xs[i] <= xs[j] + ds[j]
                    && ys[j] - ds[j] <= ys[i] && ys[i] <= ys[j] + ds[j])
                    outs[j].push_back(i);
                if (xs[i] - ds[i] <= xs[j] && xs[j] <= xs[i] + ds[i]
                    && ys[i] - ds[i] <= ys[j] && ys[j] <= ys[i] + ds[i])
                    outs[i].push_back(j);
            }
        }

        vector<bool> is_exploded(n, false);
        vector<int> inits;
        for (int i = 0; i < n; i++)
            if (!is_exploded[i]) {
                inits.push_back(i);
                explode(outs, is_exploded, i);
            }
        is_exploded.assign(n, false);
        int init_count = 0;
        for (; inits.size() > 0; inits.pop_back())
            if (!is_exploded[inits.back()]) {
                init_count++;
                explode(outs, is_exploded, inits.back());
            }
        cout << init_count << endl;
    }
    return 0;
}
