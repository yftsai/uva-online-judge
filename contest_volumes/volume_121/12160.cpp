// #easy #breadth_first_search
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

int main()
{
    bitset<10000> is_visited;
    vector<uint16_t> rvs, p, q;
    for (uint16_t case_number = 1, l, u, r; cin >> l >> u >> r && r > 0; ++case_number) {
        rvs.resize(r);
        for (auto &rv: rvs)
            cin >> rv;

        uint16_t press_count = 0;
        is_visited.reset();
        is_visited.set(l);
        p.assign(1, l);
        for (; !is_visited[u] && p.size() > 0; ++press_count, p.swap(q)) {
            q.clear();
            for (auto n: p)
                for (auto rv: rvs) {
                    auto m = (n + rv) % 10000;
                    if (!is_visited[m]) {
                        is_visited.set(m);
                        q.push_back(m);
                    }
                }
        }

        cout << "Case " << case_number << ": ";
        if (is_visited[u])
            cout << press_count << endl;
        else
            cout << "Permanently Locked" << endl;
    }

    return 0;
}
