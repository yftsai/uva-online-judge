// #binary_tree
#include <iostream>
#include <stack>
using namespace std;

struct entry
{
    uint16_t lb;    // lower bound
    uint16_t ub;    // upper bound
    uint16_t height;
};

int main()
{
    for (uint16_t case_number = 1, n, h; cin >> n >> h && n > 0; case_number++) {
        cout << "Case " << case_number << ":";
        if (n >= (uint32_t(1) << h))
            cout << " Impossible.";
        else {
            stack<entry> s;
            s.push(entry{ 1, uint16_t(n + 1), h });
            while (!s.empty()) {
                auto e = s.top();
                s.pop();

                const uint16_t rt_cap = (1 << (e.height - 1)) - 1;
                const uint16_t rt_size = min<uint16_t>(e.ub - e.lb - 1, rt_cap);
                const uint16_t root = e.ub - rt_size - 1;

                cout << " " << root;
                if (root + 1u < e.ub)
                    s.push(entry{ uint16_t(root + 1), e.ub, uint16_t(e.height - 1)});
                if (e.lb < root)
                    s.push(entry{ e.lb, root, uint16_t(e.height - 1)});
            }
        }
        cout << endl;
    }

    return 0;
}
