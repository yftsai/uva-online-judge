// #easy #binary_tree
#include <iostream>
using namespace std;

// returns (is_empty_tree, sum_existence)
pair<bool, bool> query(int sum, int path = 0)
{
    char c;
    int d;
    cin >> c >> d;
    if (cin.fail()) {
        cin.clear();
        cin >> c;
        return pair<bool, bool>(true, false);
    }
    else {
        pair<bool, bool> left = query(sum, path + d), right = query(sum, path + d);
        cin >> c;
        if (left.first && right.first)
            return pair<bool, bool>(false, path + d == sum);
        else
            return pair<bool, bool>(false, left.second || right.second);
    }
}

int main()
{
    for (int sum; cin >> sum; )
        cout << (query(sum) == pair<bool, bool>(false, true) ? "yes" : "no") << endl;
    return 0;
}
