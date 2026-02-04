// #divide_and_conquer
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

typedef pair<uint32_t, uint16_t> track_t;

// The recursive calls are simulated by a stack to avoid excessive recursion.
struct frame_t
{
    uint32_t landmark;
    uint32_t index;
    uint32_t ret_energy;    // The energy to return from the lowest landmark
                            // with a friend

    frame_t(uint32_t lm)  {
        landmark = lm;
        index = 0;
        ret_energy = 0;
    }
};


int main()
{
    vector<vector<track_t>> tracks;
    vector<bool> is_friend_landmark;
    vector<frame_t> stack;

    for (uint32_t n, f; cin >> n >> f; ) {
        tracks.clear();
        tracks.resize(n);
        for (uint32_t i = 1, a, b, c; i < n && cin >> a >> b >> c; i++)
            tracks[a - 1].emplace_back(b - 1, c);

        is_friend_landmark.clear();
        is_friend_landmark.resize(n, false);
        for (uint32_t i = 0, lm; i < f && cin >> lm; i++)
            is_friend_landmark[lm - 1] = true;

        // DFS
        uint32_t energy = 0;
        stack.emplace_back(0);
        while (stack.size() > 1 || stack[0].index < tracks[0].size()) {
            if (stack.back().index < tracks[stack.back().landmark].size()) {
                // keep traversing
                auto &track = tracks[stack.back().landmark][stack.back().index];
                stack.emplace_back(track.first);
            }
            else {
                uint32_t re = stack.back().ret_energy;
                stack.pop_back();

                const auto &track = tracks[stack.back().landmark][stack.back().index];
                if (is_friend_landmark[track.first] || re > 0) {
                    re += track.second;
                    energy += min(stack.back().ret_energy, re);
                    stack.back().ret_energy = max(stack.back().ret_energy, re);
                }

                stack.back().index += 1;
            }
        }
        stack.pop_back();

        cout << energy << endl;
    }

    return 0;
}
