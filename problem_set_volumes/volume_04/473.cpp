// #dynamic_programming
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    uint32_t dataset_count, n, t, m;
    vector<vector<uint32_t>> song_counts;

    // disk represents an incomplete last disk
    // disk[disk_count - 1] = song_count
    vector<uint32_t> disk;

    auto increase_in_one_disk = [&m](uint32_t disk_count, uint32_t count, vector<uint32_t> *counts) {
        if (disk_count <= m) {
            if (disk_count > counts->size())
                counts->resize(disk_count, 0);
            (*counts)[disk_count - 1] = max((*counts)[disk_count - 1], count);
        }
    };
    auto increase = [&](uint32_t last_t, uint32_t disk_count, uint32_t count) {
        if (last_t <= t && disk_count <= m) {
            if (last_t >= song_counts.size())
                song_counts.resize(last_t + 1);
            increase_in_one_disk(disk_count, count, &song_counts[last_t]);
        }
    };

    for (cin >> dataset_count; dataset_count > 0 && cin >> n >> t >> m; --dataset_count) {
        song_counts.resize(1);
        song_counts.reserve(t + 1);
        song_counts[0].assign(1, 0);
        for (uint32_t i = 0, ti; i < n && cin >> ti; ++i) {
            char comma;
            if (i < n - 1)
                cin >> comma;

            disk.resize(0);
            for (size_t j = song_counts.size(); j > 0; --j) {
                const uint32_t last_t = j - 1;
                for (uint32_t disk_count = song_counts[j - 1].size(); disk_count > 0; --disk_count) {
                    if (song_counts[last_t][disk_count - 1] == 0 && (last_t != 0 || disk_count > 1))
                        ;
                    else if (last_t + ti <= t)
                        increase(
                            last_t + ti,
                            disk_count,
                            song_counts[last_t][disk_count - 1] + 1);
                    else if (ti <= t)
                        increase_in_one_disk(
                            disk_count + 1,
                            song_counts[last_t][disk_count - 1] + 1,
                            &disk);
                }
            }

            for (uint32_t disk_count = disk.size(); disk_count > 0; --disk_count)
                increase(ti, disk_count, disk[disk_count - 1]);
        }

        uint32_t max_count = 0;
        for (const auto &disk: song_counts)
            if (disk.size() > 0)
                max_count = max(max_count, disk.back());
        cout << max_count << endl;
        if (dataset_count > 1)
            cout << endl;
    }
    return 0;
}
