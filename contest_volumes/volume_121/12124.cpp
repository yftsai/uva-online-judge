// #easy #dynamic_programming
#include <iostream>
#include <map>
using namespace std;

int main()
{
    int case_count;
    for (cin >> case_count; case_count > 0; case_count--) {
        int n, b, price, quality;
        string type, name;
        map<string, map<int, int>> prices;              // type -> quality -> price
        cin >> n >> b;
        for (int i = 0; i < n; i++) {
            cin >> type >> name >> price >> quality;
            if (prices[type].find(quality) == prices[type].end())
                prices[type][quality] = price;
            else
                prices[type][quality] = min(prices[type][quality], price);
        }

        map<int, int> costs = prices.begin()->second;   // quality -> cost
        for (auto it = next(prices.cbegin()); it != prices.cend(); it++) {
            map<int, int> cs;
            for (const auto config_q_c: costs)
                for (const auto comp_q_p: it->second) {
                    int q = min(config_q_c.first, comp_q_p.first);
                    int c = config_q_c.second + comp_q_p.second;
                    if (cs.find(q) == cs.end())
                        cs[q] = c;
                    else
                        cs[q] = min(cs[q], c);
                }
            costs.swap(cs);
        }

        while (costs.rbegin()->second > b)
            costs.erase(prev(costs.rbegin().base()));
        cout << costs.rbegin()->first << endl;
    }

    return 0;
}
