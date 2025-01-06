// #graph
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<vector<char>> matrix;
    uint16_t t, n, m;
    for (cin >> t; t > 0 && cin >> n >> m; t--) {
        matrix.resize(n);
        for (auto &row: matrix) {
            row.resize(m);
            for (auto &c: row)
                cin >> c;
        }

        bool is_valid = true;
        for (uint16_t e = 0; e < m && is_valid; e++) {
            uint16_t i, j;
            for (i = 0; i < n && matrix[i][e] == '0'; i++)
                ;
            for (j = i + 1; j < n && matrix[j][e] == '0'; j++)
                ;

            if (i >= n || j >= n)
                is_valid = false;

            for (uint16_t k = j + 1; k < n && is_valid; k++)
                if (matrix[k][e] == '1')
                    is_valid = false;
            for (uint16_t f = e + 1; f < m && is_valid; f++)
                if (matrix[i][f] == '1' && matrix[j][f] == '1')
                    is_valid = false;
        }

        cout << (is_valid ? "Yes" : "No") << endl;
    }

    return 0;
}
