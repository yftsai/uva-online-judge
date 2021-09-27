// #easy
#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>
using namespace std;

int main()
{
    char matrix[9][9];
    uint16_t row_indexes[9], col_indexes[9];
    auto swap_row_or_col = [&](const bool row, uint16_t i, uint16_t j) {
        if (row)
            swap(row_indexes[i], row_indexes[j]);
        else
            swap(col_indexes[i], col_indexes[j]);
    };

    string operation;
    uint16_t t, n;
    cin >> t;

    for (uint16_t case_number = 1; case_number <= t && cin >> n; case_number++) {
        for (uint16_t r = 0; r < n; r++)
            for (uint16_t c = 0; c < n; c++)
                cin >> matrix[r][c];

        int16_t inc = 0;
        bool transposed = false;
        uint16_t m, a, b;
        iota(row_indexes, row_indexes + n, 0);
        iota(col_indexes, col_indexes + n, 0);

        for (cin >> m; m > 0 && cin >> operation; m--) {
            if (operation == "row") {
                cin >> a >> b;
                swap_row_or_col(!transposed, a - 1, b - 1);
            }
            else if (operation == "col") {
                cin >> a >> b;
                swap_row_or_col(transposed, a - 1, b - 1);
            }
            else if (operation == "inc")
                inc = (inc + 1) % 10;
            else if (operation == "dec")
                inc = (inc - 1) % 10;
            else
                transposed = !transposed;
        }

        if (transposed) {
            swap(row_indexes, col_indexes);
            for (uint16_t r = 0; r < n; r++)
                for (uint16_t c = r + 1; c < n; c++)
                    swap(matrix[r][c], matrix[c][r]);
        }

        cout << "Case #" << case_number << endl;
        for (uint16_t r = 0; r < n; r++) {
            for (uint16_t c = 0; c < n; c++) {
                char ch = matrix[ row_indexes[r] ][ col_indexes[c] ];
                ch = '0' + (ch - '0' + inc + 10) % 10;
                cout << ch;
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}
