// #topological_sorting
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
using namespace std;

struct porder
{
    int gt_count;
    set<char> lt_vars;
};

bool print(map<char, porder> &var_porders,
           set<char> &s,
           string &order)
{
    if (s.size() == 0 && order.size() / 2 != var_porders.size())
        return false;
    else if (s.size() == 0) {
        cout << (order.c_str() + 1) << endl;
        return true;
    }
    else {
        for (auto it = s.begin(); it != s.end(); ++it) {
            order.push_back(' ');
            order.push_back(*it);
            s.erase(it);
            for (char c: var_porders[order.back()].lt_vars)
                if ((--var_porders[c].gt_count) == 0)
                    s.insert(c);

            if (!print(var_porders, s, order))
                return false;
            for (char c: var_porders[order.back()].lt_vars) {
                var_porders[c].gt_count++;
                s.erase(c);
            }
            it = s.insert(order.back()).first;
            order.pop_back();
            order.pop_back();
        }
        return true;
    }
}

int main()
{
    int case_count;
    vector<char> buffer;
    for (cin >> case_count; case_count > 0; case_count--) {
        map<char, porder> var_porders;
        auto add_node = [&]() {
            var_porders[buffer.front()].gt_count = 0;
            buffer.erase(buffer.begin());
        };
        for (char c; (buffer.size() < 2 && cin >> c) || (buffer.size() >= 2 && buffer[1] != '<'); )
            if (buffer.size() < 2)
                buffer.push_back(c);
            else
                add_node();
        if (buffer.size() < 2)
            add_node();

        for (char c; (buffer.size() < 2 && cin >> c) || buffer[1] == '<'; )
            if (buffer.size() < 2)
                buffer.push_back(c);
            else if (buffer.size() < 3) {
                cin >> c;
                buffer.push_back(c);
            }
            else {
                var_porders[ buffer[0] ].lt_vars.insert(buffer[2]);
                buffer.erase(buffer.begin(), buffer.begin() + 3);
            }

        for (const auto &p: var_porders)
            for (char c: p.second.lt_vars)
                var_porders[c].gt_count++;

        set<char> s;
        for (auto &p: var_porders)
            if (p.second.gt_count == 0)
                s.insert(p.first);

        string order;
        if (!print(var_porders, s, order))
            cout << "NO" << endl;
        if (case_count > 1)
            cout << endl;
    }

    return 0;
}
