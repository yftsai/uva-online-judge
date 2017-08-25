// #easy
#include <iostream>
#include <queue>
#include <string>
#include <sstream>
using namespace std;

typedef int grids[99][99];
const int unknown = -1;
const int counted = -2;

void get_area(grids areas, const int n, const int m, int i, int j)
{
    typedef pair<int, int> grid;
    queue<grid> q, r;
    for (areas[i][j] = counted, q.push(grid(i, j)); !q.empty(); q.pop()) {
        const grid g = q.front();
        r.push(g);
        for (int i = max(0, g.first - 1); i <= min(n - 1, g.first + 1); i++)
            for (int j = max(0, g.second - 1); j <= min(m - 1, g.second + 1); j++)
                if (areas[i][j] == unknown) {
                    areas[i][j] = counted;
                    q.push(grid(i, j));
                }
    }

    int a = int(r.size());
    for (; !r.empty(); r.pop())
        areas[r.front().first][r.front().second] = a;
}

int main()
{
    string line;
    getline(cin, line);
    int test_count = stoi(line);

    getline(cin, line);
    for (; test_count > 0; test_count--){
        grids areas;
        unsigned int m, n;
        for (n = 0; getline(cin, line) && (line[0]=='L' || line[0]=='W'); n++)
            for (m = 0; m < line.size(); m++)
                areas[n][m] = (line[m] == 'L') ? 0 : unknown;

        do {
            int i, j;
            stringstream(line) >> i >> j;
            if (areas[i-1][j-1] == unknown)
                get_area(areas, n, m, i-1, j-1);
            cout << areas[i-1][j-1] << endl;
        } while (getline(cin, line) && line.size() > 0);
        if (test_count > 1)
            cout << endl;
    }

    return 0;
}
