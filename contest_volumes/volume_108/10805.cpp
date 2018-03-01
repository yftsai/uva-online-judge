// #shortest_path
// reference: https://yuting-zhang.github.io/uva/2016/12/21/UVa-10805.html
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int test_count, n, m;
    cin >> test_count;
    for (int x = 1; x <= test_count && (cin >> n >> m); x++) {
        int distances[n + m][n + m];
        for (int i = 0; i < n + m; i++)
            for (int j = 0; j < n + m; j++)
                distances[i][j] = 2 * m;
        for (int i = 0, j, k; i < m && (cin >> j >> k); i++)
            distances[j][n + i] = distances[n + i][j] = distances[n + i][k] = distances[k][n + i] = 1;

        for (int i = 0; i < n + m; i++)
            for (int j = 0; j < n + m; j++)
                for (int k = 0; k < n + m; k++)
                    distances[j][k] = min(distances[j][k], distances[j][i] + distances[i][k]);

        int ertime = m;
        for (int i = 0; i < n + m; i++)
            ertime = min(ertime, *max_element(distances[i], distances[i] + n));

        cout << "Case #" << x << ":" << endl;
        cout << ertime << endl;
        cout << endl;
    }

    return 0;
}
