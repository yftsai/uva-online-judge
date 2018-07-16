// #dynamic_programming
#include <iostream>
#include <cctype>
#include <bitset>
#include <vector>
using namespace std;

constexpr uint16_t base = 3000;
typedef bitset<base * 2> value_set;

void compute(uint16_t accumulation, int16_t lp_count, const vector<pair<char, uint16_t>> &operations, uint16_t index,
             vector<vector<int16_t>> &computed_expressions, value_set &results)
{
    if (index >= computed_expressions.size())
        computed_expressions.resize(index + 1);
    if (accumulation >= computed_expressions[index].size())
        computed_expressions[index].resize(accumulation + 1, -1);

    if (lp_count <= computed_expressions[index][accumulation])
        ;
    else if (index >= operations.size())
        results.set(accumulation);
    else {
        if (lp_count > 0)
            compute(accumulation, lp_count - 1, operations, index, computed_expressions, results);

        char op = operations[index].first;
        bool is_add = ((lp_count % 2 == 0) == (op == '+'));
        int operand = operations[index].second;
        int acc = accumulation + (is_add ? operand : -operand);
        if (op == '-')
            compute(acc, lp_count + 1, operations, index + 1, computed_expressions, results);
        compute(acc, lp_count, operations, index + 1, computed_expressions, results);

        computed_expressions[index][accumulation] = lp_count;
    }
}

int main()
{
    vector<vector<int16_t>> computed_expressions;
    vector<pair<char, uint16_t>> operations;

    for (int accumulation; cin >> accumulation; computed_expressions.clear()) {
        for (operations.resize(1); cin >> operations.back().first && !isdigit(operations.back().first); operations.emplace_back())
            cin >> operations.back().second;
        cin.putback(operations.back().first);
        operations.pop_back();

        value_set results;
        compute(accumulation + base, 0, operations, 0, computed_expressions, results);
        cout << results.count() << endl;
    }

    return 0;
}
