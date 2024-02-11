// #parsing #easy
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

static bool is_comp(string &token) {
    const char *comps[] = { "<", ">", "<=", ">=", "=" };
    return find(begin(comps), end(comps), token) != end(comps);
}

int main()
{
    uint16_t p, g;
    cin >> p >> g;

    vector<pair<string, uint16_t>> nps(p);
    for (auto &np: nps) {
        uint16_t i, f;
        char dot;
        cin >> np.first >> i >> dot >> f;
        np.second = 10 * i + f;
    }

    sort(nps.begin(), nps.end());

    string token;
    for (uint16_t i = 1; i <= g; i++) {
        uint16_t sum = 0;
        while (cin >> token && !is_comp(token))
            if (token[0] != '+') {
                auto it = lower_bound(nps.begin(), nps.end(), token,
                        [](const pair<string, uint16_t> &np, const string &name) {
                            return np.first < name;
                        });
                sum += it->second;
            }

        uint16_t n;
        cin >> n;
        n *= 10;

        bool correctness;
        switch (token[0]) {
            case '<':
                correctness = (token.size() == 1) ? (sum < n) : (sum <= n);
                break;
            case '>':
                correctness = (token.size() == 1) ? (sum > n) : (sum >= n);
                break;
            default:
                correctness = sum == n;
        }

        cout << "Guess #" << i << " was " << (correctness ? "" : "in") << "correct." << endl;
    }

    return 0;
}
