// #set_union
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main()
{
    vector<string> creatures(5000);
    vector<uint16_t> set_reps(5000);
    vector<uint16_t> set_sizes(5000);
    auto get_rep = [&set_reps](uint16_t i)-> uint16_t {
        uint16_t r = set_reps[i];
        while (r != set_reps[r])
            r = set_reps[r];
        for (uint16_t j; (j = set_reps[i]) != r; i = j)
            set_reps[i] = r;
        return r;
    };


    string prey, predator;
    for (uint16_t c, r; cin >> c >> r && c > 0; ) {
        set_reps.resize(c);
        iota(set_reps.begin(), set_reps.end(), 0);
        set_sizes.assign(c, 1);

        creatures.resize(c);
        for (auto &creature: creatures)
            cin >> creature;
        sort(creatures.begin(), creatures.end());

        uint16_t max_size = 1;
        for (uint16_t i = 0; i < r && cin >> prey >> predator; ++i) {
            const uint16_t j = get_rep(lower_bound(creatures.begin(), creatures.end(), prey) - creatures.begin());
            const uint16_t k = get_rep(lower_bound(creatures.begin(), creatures.end(), predator) - creatures.begin());
            if (j != k) {
                set_reps[j] = k;
                set_sizes[k] += set_sizes[j];
                max_size = max(max_size, set_sizes[k]);
            }
        }

        cout << max_size << endl;
    }

    return 0;
}
