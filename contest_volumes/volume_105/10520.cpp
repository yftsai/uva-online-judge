// #easy #dynamic_programming
#include <iostream>
#include <limits>
using namespace std;

int64_t get_a(int64_t as[21][21], int n, int i, int j)
{
    if (as[i][j] == numeric_limits<int64_t>::max()) {
        if (i < j) {
            as[i][j] = 0;
            for (int k = i; k < j; k++)
                as[i][j] = max(as[i][j], get_a(as, n, i, k) + get_a(as, n, k + 1, j));
        }
        else {
            int64_t left = 0, right = 0;
            for (int k = i + 1; k <= n; k++)
                left = max(left, get_a(as, n, k, 1) + get_a(as, n, k, j));
            for (int k = 1; k < j; k++)
                right = max(right, get_a(as, n, i, k) + get_a(as, n, n, k));
            as[i][j] = left + right;
        }
    }
    return as[i][j];
}

int main()
{
    for (int n, a; cin >> n >> a; ) {
        int64_t as[21][21];
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                as[i][j] = numeric_limits<int64_t>::max();
        as[n][1] = a;
        cout << get_a(as, n, 1, n) << endl;
    }
}
