// #shortest_path #easy
#include <iostream>
using namespace std;

int main()
{
    constexpr int max_n = 100;
    int lengths[max_n][max_n];

    int t;
    cin >> t;
    for (int case_number = 1, n, r; case_number <= t && cin >> n >> r; case_number++) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                lengths[i][j] = (i == j) ? 0 : n;
        for (int i = 0, b, c; i < r && cin >> b >> c; i++)
            lengths[b][c] = lengths[c][b] = 1;
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    lengths[i][j] = min(lengths[i][j], lengths[i][k] + lengths[k][j]);

        int s, d, min_time = 0;
        cin >> s >> d;
        for (int i = 0; i < n; i++)
            min_time = max(min_time, lengths[s][i] + lengths[i][d]);
        cout << "Case " << case_number << ": " << min_time << endl;
    }

    return 0;
}
