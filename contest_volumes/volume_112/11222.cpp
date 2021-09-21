// #easy
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    array<vector<uint16_t>, 3> problems;
    vector<uint16_t> problem_sets[2], shared_problems;
    uint16_t t;

    cin >> t;
    for (uint16_t case_number = 1; case_number <= t; case_number++) {
        for (auto &ps: problems) {
            uint16_t s;
            cin >> s;
            ps.resize(s);
            for (auto &p: ps)
                cin >> p;

            sort(ps.begin(), ps.end());
            ps.erase(unique(ps.begin(), ps.end()), ps.end());
        }

        shared_problems.clear();
        for (uint16_t i = 0; i < problems.size(); i++)
            for (uint16_t j = i + 1; j < problems.size(); j++) {
                problem_sets[0].clear();
                set_intersection(
                    problems[i].begin(), problems[i].end(),
                    problems[j].begin(), problems[j].end(),
                    back_inserter(problem_sets[0]));
                problem_sets[1].swap(shared_problems);

                shared_problems.clear();
                set_union(
                    problem_sets[0].begin(), problem_sets[0].end(),
                    problem_sets[1].begin(), problem_sets[1].end(),
                    back_inserter(shared_problems));
            }

        for (auto &ps: problems)
            ps.erase(
                set_difference(
                    ps.begin(), ps.end(),
                    shared_problems.begin(), shared_problems.end(),
                    ps.begin()),
                ps.end());

        auto it = max_element(
            problems.begin(), problems.end(),
            [](const vector<uint16_t> &left, const vector<uint16_t> &right)
            {
                return left.size() < right.size();
            });

        cout << "Case #" << case_number << ":" << endl;
        for (uint16_t i = 0; i < problems.size(); i++)
            if (problems[i].size() == it->size()) {
                cout << (i + 1) << " " << it->size();
                for (const auto p: problems[i])
                    cout << " " << p;
                cout << endl;
            }
    }

    return 0;
}
