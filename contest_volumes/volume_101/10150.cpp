// #easy #breadth_first_search
#include <iostream>
#include <string>
#include <numeric>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

bool is_doublet(const string &v, const string &w)
{
    size_t vstart = 0, vend = v.size(), wstart = 0, wend = w.size();
    for (; vstart < vend && wstart < wend; )
        if (v[vstart] == w[wstart])
            vstart++, wstart++;
        else if (v[vend - 1] == w[wend - 1])
            vend--, wend--;
        else
            break;
    return (vend - vstart <= 1) && (wend - wstart <= 1);
}

int main()
{
    string words[25144];
    uint16_t word_count = 0;

    for (; getline(cin, words[word_count]) && words[word_count].size() > 0; word_count++)
        ;
    sort(words, words + word_count);

    map<uint16_t, vector<uint16_t>> word_indexes;
    vector<uint16_t> doublets[word_count];
    for (uint16_t i = 0; i < word_count; i++) {
        int h = accumulate(words[i].begin(), words[i].end(), 0);
        for (auto it = word_indexes.lower_bound(h - 26); it != word_indexes.upper_bound(h + 26); it++)
            for (auto j: it->second)
                if (is_doublet(words[i], words[j])) {
                    doublets[i].push_back(j);
                    doublets[j].push_back(i);
                }
        word_indexes[h].push_back(i);
    }

    bool is_first_case = true;
    for (string v, w; cin >> v >> w; ) {
        auto vp = lower_bound(words, words + word_count, v);
        auto wp = lower_bound(words, words + word_count, w);
        const uint16_t vindex = (vp - words >= word_count || *vp != v) ? word_count : (vp - words);
        const uint16_t windex = (wp - words >= word_count || *wp != w) ? word_count : (wp - words);

        uint16_t distances[word_count];
        for (auto &d: distances)
            d = word_count;

        if (vindex < word_count && windex < word_count) {
            queue<uint16_t> q;
            distances[vindex] = 0;
            q.push(vindex);
            while (!q.empty() && distances[windex] >= word_count) {
                uint16_t i = q.front();
                q.pop();
                for (auto j: doublets[i]) {
                    if (distances[i] + 1 < distances[j]) {
                        distances[j] = distances[i] + 1;
                        q.push(j);
                    }
                }
            }
        }

        if (is_first_case)
            is_first_case = false;
        else
            cout << endl;
        if (windex >= word_count || distances[windex] >= word_count)
            cout << "No solution." << endl;
        else {
            uint16_t indexes[ distances[windex] + 1 ];
            indexes[0] = windex;
            for (uint16_t i = 0; i < distances[windex]; i++) {
                for (uint16_t j: doublets[ indexes[i] ])
                    if (distances[ indexes[i] ] - 1 == distances[j]) {
                        indexes[i + 1] = j;
                        break;
                    }
            }
            reverse(indexes, indexes + distances[windex] + 1);
            for (auto &i: indexes)
                cout << words[i] << endl;
        }
    }
    return 0;
}
