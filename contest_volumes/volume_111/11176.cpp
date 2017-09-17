// #dynamic_programming
// This approach was proposed on the forum, and run in O(n^2) better than the naive O(n^3).
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    cout.precision(6);

    double p;
    for (uint16_t n; cin >> n >> p && n > 0; ) {
        double probs[n + 1][n + 1];
        probs[0][0] = 1;
        for (uint16_t game_count = 1; game_count <=n; game_count++) {
            for (uint16_t streak_limit = 0; streak_limit < game_count - 1; streak_limit++) {
                uint16_t count = game_count - 2 - streak_limit;
                probs[game_count][streak_limit]
                    = probs[game_count - 1][streak_limit]
                        - probs[count][min(count, streak_limit)] * (1 - p) * pow(p, streak_limit + 1);
            }
            probs[game_count][game_count - 1] = 1 - pow(p, game_count);
            probs[game_count][game_count] = 1;
        }

        double exp = 0;
        for (uint16_t streak_length = 1; streak_length <= n; streak_length++)
            exp += streak_length * (probs[n][streak_length] - probs[n][streak_length - 1]);
        cout << fixed << exp << endl;
    }
    return 0;
}
