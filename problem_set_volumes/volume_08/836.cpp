// #dynamic_programming
#include <iostream>
#include <cstring>
using namespace std;


int main()
{
    int sums[26][26];
    for (int i = 0; i < 26; i++)
        sums[i][0] = sums[0][i] = 0;

    int case_count;
    for (cin >> case_count; case_count > 0; case_count--) {
        char line[26];
        cin >> line;
        int n = strlen(line);
        for (int i = 0; i < n; i++)
            sums[1][i+1] = sums[1][i] + (line[i] - '0');
        for (int i = 1; i < n && cin >> line; i++)
            for (int j = 0; j < n; j++)
                sums[i+1][j+1] = sums[i][j+1] + sums[i+1][j] - sums[i][j] + (line[j] - '0');

        int max_sum = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int s = i + 1; s <= n; s++)
                    for (int t = j + 1; t <= n; t++) {
                        int sum = sums[s][t] - sums[i][t] - sums[s][j] + sums[i][j];
                        if (sum == (s - i)*(t - j))
                            max_sum = max(max_sum, sum);
                    }
        cout << max_sum << endl;
        if (case_count > 1)
            cout << endl;
    }
    return 0;
}
