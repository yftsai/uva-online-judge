// #easy
#include <iostream>
#include <vector>
using namespace std;

struct domino
{
    bool is_fallen;
    vector<uint16_t> knocks;

    domino(): is_fallen(false)  {}
};

int main()
{
    vector<domino> dominos;
    vector<uint16_t> stack;
    uint32_t ncase, n, m, l;

    for (cin >> ncase; ncase > 0 && cin >> n >> m >> l; ncase--) {
        dominos.clear();
        dominos.resize(n);
        for (uint32_t i = 0, x, y; i < m && cin >> x >> y; i++)
            dominos[x - 1].knocks.push_back(y - 1);

        uint32_t count = 0;
        for (uint32_t i = 0, z; i < l && cin >> z; i++) {
            if (!dominos[z - 1].is_fallen) {
                dominos[z - 1].is_fallen = true;
                stack.push_back(z - 1);
                count++;

                while (!stack.empty()) {
                    const uint16_t d = stack.back();
                    stack.pop_back();

                    for (auto e: dominos[d].knocks)
                        if (!dominos[e].is_fallen) {
                            dominos[e].is_fallen = true;
                            stack.push_back(e);
                            count++;
                        }
                }
            }
        }
        cout << count << endl;
    }
    return 0;
}
