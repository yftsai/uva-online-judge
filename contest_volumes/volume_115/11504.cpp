#include <iostream>
#include <vector>
using namespace std;

void knock_over(const vector<vector<uint32_t>> &dominos, vector<bool> &is_fallen, uint32_t d, vector<uint32_t> &stack)
{
    for (is_fallen[d] = true, stack.push_back(d); stack.size() > 0; ) {
        d = stack.back();
        stack.pop_back();
        for (auto e: dominos[d])
            if (!is_fallen[e]) {
                is_fallen[e] = true;
                stack.push_back(e);
            }
    }
}

int main()
{
    vector<vector<uint32_t>> dominos;
    vector<bool> is_fallen;
    vector<uint32_t> stack, order;
    uint32_t case_count;
    for (cin >> case_count; case_count > 0; case_count--) {
        uint32_t n, m;
        cin >> n >> m;
        dominos.assign(n, vector<uint32_t>());
        for (uint32_t i = 0, x, y; i < m && cin >> x >> y; i++)
            dominos[x - 1].push_back(y - 1);

        is_fallen.assign(n, false);
        for (uint32_t i = 0; i < n; i++)
            if (!is_fallen[i]) {
                order.push_back(i);
                knock_over(dominos, is_fallen, i, stack);
            }

        uint32_t count = 0;
        is_fallen.assign(n, false);
        for (; order.size() > 0; order.pop_back())
            if (!is_fallen[order.back()]) {
                count++;
                knock_over(dominos, is_fallen, order.back(), stack);
            }
        cout << count << endl;
    }
    return 0;
}
