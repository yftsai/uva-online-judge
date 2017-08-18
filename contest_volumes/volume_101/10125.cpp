// #dynamic_programming
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <limits>
using namespace std;

const int not_found = numeric_limits<int>::max();

int find_d(vector<int> &s, const map<int, set<int>> &sum_ab)
{
    for (auto dit = s.rbegin(); dit != s.rend(); dit++)
        for (auto cit = s.rbegin(); cit != s.rend(); cit++)
            if (*cit != *dit) {
                auto it = sum_ab.find(*dit - *cit);
                if (it != sum_ab.end())
                    if (it->second.lower_bound(*cit) != it->second.begin())
                        return *dit;
            }
    return not_found;
}

int main()
{
    for (int n, x = 0; cin >> n && n != 0; x++) {
        vector<int> s(n);
        for (auto &e: s)
            cin >> e;
        sort(s.begin(), s.end());

        map<int, set<int>> sum_ab;
        for (auto ait = s.begin(); ait != s.end(); ait++)
            for (auto bit = next(ait); bit != s.end(); bit++)
                sum_ab[*ait + *bit].insert(*bit);

        int d = find_d(s, sum_ab);
        if (d == not_found)
            cout << "no solution" << endl;
        else
            cout << d << endl;
    }

    return 0;
}
