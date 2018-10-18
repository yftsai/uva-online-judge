// #longest_increasing_subsequence
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
    vector<pair<int, uint32_t>> numbers;        // number, predecessor index
    vector<pair<int, uint32_t>> last_numbers;   // last number, index

    for (int n, i = 0; cin >> n; i++) {
        auto it = lower_bound(
            last_numbers.begin(),
            last_numbers.end(),
            n,
            [](const pair<int, uint32_t> &p, const int n) { return p.first < n; });

        if (it == last_numbers.end()) {
            numbers.emplace_back(n, last_numbers.size() == 0 ? i : last_numbers.back().second);
            last_numbers.emplace_back(n, i);
        }
        else if (it->first == n) {
            numbers.emplace_back(n, numbers[it->second].second);
            it->second = i;
        }
        else {
            numbers.emplace_back(n, it == last_numbers.begin() ? i : prev(it)->second);
            *it = make_pair(n, i);
        }
    }

    cout << last_numbers.size() << endl;
    cout << "-" << endl;
    for (uint32_t i = last_numbers.size(), j = last_numbers.back().second; i > 0; i--, j = numbers[j].second)
        last_numbers[i - 1].first = numbers[j].first;
    for (pair<int, uint32_t> &p: last_numbers)
        cout << p.first << endl;

    return 0;
}
