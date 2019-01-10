#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int maximize_amount(int n, int m[8][8], uint16_t is_crossed, vector<int> *amounts);

int minimize_amount(int n, int m[8][8], uint16_t is_crossed, int row, vector<int> *amounts)
{
    int min_amount = numeric_limits<int>::max();
    for (uint16_t col = 0, cmask = 1u; col < n; ++col, cmask <<= 1)
        if (!(is_crossed & cmask))
            min_amount = min(min_amount, maximize_amount(n, m, is_crossed | cmask, amounts) + m[row][col]);
    return min_amount;
}

int maximize_amount(int n, int m[8][8], uint16_t is_crossed, vector<int> *amounts)
{
    int &max_amount = (*amounts)[is_crossed];
    if (max_amount == numeric_limits<int>::min())
        for (uint16_t row = 0, rmask = (1u << n); row < n; ++row, rmask <<= 1)
            if (!(is_crossed & rmask))
                max_amount = max(max_amount, minimize_amount(n, m, is_crossed | rmask, row, amounts));
    return max_amount;
}

int main()
{
    int t, n, m[8][8];
    vector<int> amounts;
    for (cin >> t; t > 0 && cin >> n; --t) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> m[i][j];
        amounts.assign(1 << (n * 2), numeric_limits<int>::min());
        amounts.back() = 0;
        cout << maximize_amount(n, m, 0, &amounts) << endl;
    }
    return 0;
}
