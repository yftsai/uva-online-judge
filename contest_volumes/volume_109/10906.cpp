// #easy #parsing
#include <iostream>
#include <map>
#include <string>
#include <cctype>
using namespace std;

struct definition
{
    pair<string, string> terms;
    char op;
};

void print(const map<string, definition> &simple_exprs, const definition &def)
{
    if (isdigit(def.terms.first[0]))
        cout << def.terms.first;
    else {
        auto &left_def = simple_exprs.find(def.terms.first)->second;
        const bool is_parenthesized = (left_def.op == '+' && def.op == '*');
        if (is_parenthesized) cout << '(';
        print(simple_exprs, left_def);
        if (is_parenthesized) cout << ')';
    }

    cout << def.op;
    if (isdigit(def.terms.second[0]))
        cout << def.terms.second;
    else {
        auto &right_def = simple_exprs.find(def.terms.second)->second;
        const bool is_parenthesized = !(def.op == '+' && right_def.op == '*');
        if (is_parenthesized) cout << '(';
        print(simple_exprs, right_def);
        if (is_parenthesized) cout << ')';
    }
}

int main()
{
    string variable;

    uint16_t t;
    cin >> t;
    for (uint16_t d = 1, n; d <= t && cin >> n; d++) {
        map<string, definition> simple_exprs;
        char eq;

        for (uint16_t i = 0; i < n && cin >> variable; i++) {
            auto &def = simple_exprs[variable];
            cin >> eq >> def.terms.first >> def.op >> def.terms.second;
        }

        cout << "Expression #" << d << ": ";
        print(simple_exprs, simple_exprs[variable]);
        cout << endl;
    }

    return 0;
}
