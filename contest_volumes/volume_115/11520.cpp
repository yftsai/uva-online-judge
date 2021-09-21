// #greedy
#include <iostream>
using namespace std;

int main()
{
    uint32_t case_count;
    uint16_t n;
    char grid[10][11];

    auto check = [&grid](const uint16_t n, const uint16_t i, const uint16_t j) {
        const char a = grid[i][j];
        return !((i > 0 && grid[i - 1][j] == a)
            || (j > 0 && grid[i][j - 1] == a)
            || (i + 1 < n && a == grid[i + 1][j])
            || (j + 1 < n && a == grid[i][j + 1]));
    };

    cin >> case_count;
    for (uint32_t t = 1; t <= case_count && cin >> n; t++) {
        for (uint16_t i = 0; i < n; i++)
            cin >> grid[i];

        for (uint16_t i = 0; i < n; i++)
            for (uint16_t j = 0; j < n; j++)
                if (grid[i][j] == '.')
                    for (grid[i][j] = 'A'; !check(n, i, j); grid[i][j]++)
                        ;

        cout << "Case " << t << ":" << endl;
        for (uint16_t i = 0; i < n; i++)
            cout << grid[i] << endl;
    }
    return 0;
}
