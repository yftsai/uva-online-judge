// #dynamic_programming
#include <iostream>
#include <array>
#include <algorithm>
using namespace std;

int main()
{
    array<uint64_t, 66> locked_counts;   // Case counts with the top drawer locked.
    array<uint64_t, 66> unlocked_counts; // Case counts with the top drawer unlocked.

    for (int16_t n, s; cin >> n >> s && n > 0; ) {
        fill(locked_counts.begin() + 1, locked_counts.begin() + s + 1, 0);
        fill(unlocked_counts.begin() + 1, unlocked_counts.begin() + s + 1, 0);

        // When there is only one drawer.
        locked_counts[0] = 0;
        locked_counts[1] = 1;   // One secure drawer if the drawer is locked.
        unlocked_counts[0] = 1; // No secure drawer if the drawer is unlocked.
        unlocked_counts[1] = 0;

        for (int16_t drawer_count = 2; drawer_count <= n; drawer_count++) {
            locked_counts[drawer_count] = 0;
            unlocked_counts[drawer_count] = 0;

            array<uint64_t, 2> last_lcs = { 0, 0 };
            for (auto count = min<int16_t>(drawer_count, s + 1); count >= 0; count--) {
                last_lcs[1] = last_lcs[0];
                last_lcs[0] = locked_counts[count];

                locked_counts[count] = count > 0 ? (unlocked_counts[count - 1] + locked_counts[count - 1]) : 0;
                unlocked_counts[count] += last_lcs[1];
            }
        }

        cout << locked_counts[s] + unlocked_counts[s] << endl;
    }

    return 0;
}
