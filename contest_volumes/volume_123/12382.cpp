#include <iostream>
#include <set>
using namespace std;

int main()
{
    int t, m, n;
    for (cin >> t; t>0; --t) {
        cin >> m >> n;
        multiset<int, greater<int>> row, matched_col;
        for (int i=0, r; i<m && cin >> r; ++i)
            if (r>0)
                row.insert(r);
        for (int i=0, c; i<n && cin >> c; ++i)
            if (c>0)
                matched_col.insert(c);

        int count = 0;
        for (int r: row) {
            count += r;
            multiset<int, greater<int>> col;
            for (auto &c: matched_col)
                if (r==0)
                    col.insert(col.end(), c);
                else if (c>1)
                    --r, col.insert(col.end(), c-1);
                else
                    --r;
            swap(matched_col, col);
        }
        for (auto &c: matched_col)
            count += c;

        cout << count << endl;
    }

    return 0;
}
