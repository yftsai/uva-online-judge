// #dynamic_programming
#include <iostream>
using namespace std;

int main()
{
    int t, a, b, c, m, n;

    cin >> t;
    for (int case_number = 1; case_number <= t && cin >> a >> b >> c >> m >> n; case_number++) {
        a %= m;
        int count = (a == 0) ? 1 : 0;
        int sum_counts[m] = { 0 };
        sum_counts[0]++;
        sum_counts[a]++;
        for (int i = 1, sum = a, x = a, y; i < n; i++, x = y) {
            y = (x * b + c) % m + 1;
            sum = (sum + y) % m;
            count += (sum_counts[sum]++);
        }

        cout << "Case " << case_number << ": " << count << endl;
    }

    return 0;
}
