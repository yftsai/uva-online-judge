// #dynamic_programming
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int m, n;
    while (cin >> m >> n) {
        vector<vector<int>> matrix(m, vector<int>(n)), steps(m, vector<int>(n-1));
        for (auto &row: matrix)
            for (auto &v: row)
                cin >> v;
        
        for (int col = n-2; col>=0; --col)
            for (int row = 0; row<m; ++row) {
                int &step = steps[row][col];
                step = (row+m-1)%m;
                for (int r: { row, (row+1)%m })
                    if ((matrix[r][col+1] < matrix[step][col+1]) || (matrix[r][col+1] == matrix[step][col+1] && r < step))
                        step = r;
                matrix[row][col] += matrix[step][col+1];
            }

        int p = 0;
        for (int i=1; i<m; ++i)
            if (matrix[i][0] < matrix[p][0])
                p = i;
        cout << (p+1);
        for (int i=0, j=p; i<n-1; ++i)
            cout << " " << ((j = steps[j][i]) + 1);
        cout << endl;
        cout << matrix[p][0] << endl;
    }
    return 0;
}
