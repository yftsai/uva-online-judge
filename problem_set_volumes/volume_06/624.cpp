// #dynamic_programming
#include <iostream>
#include <list>
#include <iterator>
using namespace std;

int main()
{
    for (uint32_t n, m; cin >> n >> m; ) {
        list<pair<uint32_t, uint32_t>> last_tracks;
        last_tracks.emplace(last_tracks.end(), 0, 0);
        for (uint32_t i = 0, len; i < m && cin >> len; ++i) {
            auto insertion_pos = last_tracks.end();
            for (auto it = last_tracks.end(); it != last_tracks.begin(); ) {
                --it;
                while (insertion_pos != last_tracks.begin() && it->first + len < prev(insertion_pos)->first)
                    --insertion_pos;
                if ((insertion_pos == last_tracks.begin() || it->first + len > prev(insertion_pos)->first)
                    && it->first + len <= n)
                    insertion_pos = last_tracks.emplace(insertion_pos, it->first + len, len);
            }
        }

        list<uint32_t> tracks;
        uint32_t s = last_tracks.back().first;
        for (uint32_t t = last_tracks.back().first; last_tracks.back().first != 0; last_tracks.pop_back())
            if (last_tracks.back().first == t) {
                tracks.push_front(last_tracks.back().second);
                t -= last_tracks.back().second;
            }
        for (auto &t: tracks)
            cout << t << " ";
        cout << "sum:" << s << endl;
    }

    return 0;
}
