// #strongly_connected_components
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<vector<uint16_t>> lights;
    vector<bool> is_on;
    vector<uint16_t> st, inits;

    auto turn_on = [&](uint16_t i) {
        is_on[i] = true;
        st.push_back(i);
        while (!st.empty()) {
            i = st.back();
            st.pop_back();
            for (auto j: lights[i])
                if (!is_on[j]) {
                    is_on[j] = true;
                    st.push_back(j);
                }
        }
    };

    uint32_t t, n, m;
    cin >> t;
    for (uint16_t tno = 1; tno <= t && cin >> n >> m; tno++) {
        lights.clear();
        lights.resize(n);
        for (uint32_t i = 0, a, b; i < m && cin >> a >> b; i++)
            lights[a - 1].push_back(b - 1);

        is_on.clear();
        is_on.resize(n, false);
        for (uint16_t i = 0; i < n; i++)
            if (!is_on[i]) {
                inits.push_back(i);
                turn_on(i);
            }

        uint16_t init_count = 0;
        is_on.clear();
        is_on.resize(n, false);
        for (; !inits.empty(); inits.pop_back())
            if (!is_on[inits.back()]) {
                init_count++;
                turn_on(inits.back());
            }

        cout << "Case " << tno << ": " << init_count << endl;
    }

    return 0;
}
