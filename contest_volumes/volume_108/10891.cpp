// #dynamic_programming
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> numbers;
    vector<vector<int>> differences;
    for (int n; cin >>n && n != 0; ) {
        numbers.resize(n);
        for (int &n: numbers)
            cin >> n;

        differences.resize(n + 1);
        differences[0].resize(n + 1, 0);
        for (int len = 1; len <= n; len++) {
            differences[len].resize(n + 1 - len);

            for (int i = 0; i + len <= n; i++) {
                int s = numbers[i];
                differences[len][i] = s - differences[len - 1][i + 1];
                for (int j = 2; j <= len; j++) {
                    s += numbers[i + j - 1];
                    differences[len][i] = max(differences[len][i], s - differences[len - j][i + j]);
                }

                s = 0;
                for (int j = 1; j <= len; j++) {
                    s += numbers[i + len - j];
                    differences[len][i] = max(differences[len][i], s - differences[len - j][i]);
                }
            }
        }
        cout << differences[n][0] << endl;
    }

    return 0;
}
