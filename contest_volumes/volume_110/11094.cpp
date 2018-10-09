// #easy
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const char LAND = 'L', WATER = 'W';

int count_regions(vector<string> &rows, int x, int y)
{
    const int m(rows.size()), n(rows[0].size()), base = 32;
    int region_count = 0;
    for (vector<int> s(1, base * x + y); !s.empty(); ) {
        x = s.back() / base, y = s.back() % base;
        s.pop_back();
        for (int i = max(0, x - 1); i < min(x + 2, m); i++)
            if (rows[i][y] == LAND) {
                rows[i][y] = WATER;
                region_count++;
                s.push_back(base * i + y);
            }
        for (int i = y - 1; i < y + 2; i++) {
            int j = (0 <= i && i < n) ? i : ((i + n) % n);
            if (rows[x][j] == LAND) {
                rows[x][j] = WATER;
                region_count++;
                s.push_back(base * x + j);
            }
        }
    }
    return region_count;
}

int main()
{
    vector<string> rows;
    for (int m, n; cin >> m >> n; ) {
        rows.resize(m);
        for (int i = 0; i < m; i++)
            cin >> rows[i];

        int x, y;
        cin >> x >> y;
        char land = rows[x][y];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (rows[i][j] == land)
                    rows[i][j] = LAND;
                else
                    rows[i][j] = WATER;
        count_regions(rows, x, y);

        int max_region_count = 0;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (rows[i][j] == LAND)
                    max_region_count = max(max_region_count, count_regions(rows, i, j));
        cout << max_region_count << endl;
    }
    return 0;
}
