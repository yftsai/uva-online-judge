// #n_queen
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

int count_placements(const vector<set<int>> &bad_squares, const vector<int> &order, int row, vector<int> &placement)
{
    if (row >= int(order.size()))
        return 1;
    else {
        int count = 0;
        for (int i = row; i < int(order.size()); i++) {
            swap(placement[row], placement[i]);
            bool is_attacked = false;
            for (int j = 0; j < row; j++)
                if (placement[j] + order[j] - row == placement[row]
                    || placement[j] - order[j] + row == placement[row]) {
                    is_attacked = true;
                    break;
                }
            if (!is_attacked && bad_squares[row].find(placement[row]) == bad_squares[row].end())
                count += count_placements(bad_squares, order, row+1, placement);
            swap(placement[row], placement[i]);
        }
        return count;
    }
}

int main()
{
    for (int n, case_number = 1; cin >> n && n != 0; case_number++) {
        vector<int> order(n), placement(n);
        vector<set<int>> bad_squares(n);
        for (int i = 0; i < n; i++) {
            order[i] = placement[i] = i;

            string line;
            cin >> line;
            for (int j = 0; j < n; j++)
                if (line[j] == '*')
                    bad_squares[i].insert(j);
        }
        auto less_bad_squares = [&](int &i, int &j) { return bad_squares[i].size() > bad_squares[j].size(); };
        sort(order.begin(), order.end(), less_bad_squares);

        cout << "Case " << case_number << ": " << count_placements(bad_squares, placement, 0, order) << endl;
    }
    return 0;
}
