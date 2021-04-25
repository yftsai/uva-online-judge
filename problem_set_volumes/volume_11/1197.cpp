// #set_union
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

int main()
{
    vector<uint16_t> reps(1000 * 30);   // representatives
    auto get_rep = [&reps](uint16_t i) {
        uint16_t s = i;
        while (reps[s] != s)
            s = reps[s];
        for (uint16_t j; reps[i] != s; i = j) {
            j = reps[i];
            reps[i] = s;
        }
        return s;
    };

    for (uint16_t n, m; cin >> n >> m && n > 0; ) {
        reps.resize(n);
        iota(reps.begin(), reps.end(), 0);
        for (uint16_t i = 0, k; i < m && cin >> k; i++)
            if (k > 0) {
                uint16_t r;
                cin >> r;
                r = get_rep(r);
                for (uint16_t j = 1, student; j < k && cin >> student; j++) {
                    student = get_rep(student);
                    reps[student] = r;
                }
            }

        const uint16_t suspect = get_rep(0);
        uint16_t count = 1;
        for (uint16_t i = 1; i < n; i++)
            if (get_rep(i) == suspect)
                count++;
        cout << count << endl;
    }

    return 0;
}
