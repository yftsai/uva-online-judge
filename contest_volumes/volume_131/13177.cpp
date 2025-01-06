// #easy #priority_queue
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct inst_t
{
    uint16_t musicians;
    uint16_t scores;
    uint16_t max_crowd;

    bool operator<(const inst_t &i) const;
};

bool inst_t::operator<(const inst_t &i) const
{
    return max_crowd < i.max_crowd;
}

int main()
{
    vector<inst_t> insts;
    for (uint32_t p, n; cin >> p >> n; ) {
        insts.resize(n);
        for (auto &inst: insts) {
            cin >> inst.musicians;
            inst.scores = 1;
            inst.max_crowd = inst.musicians;
        }

        make_heap(insts.begin(), insts.end());
        for (uint32_t i = n; i < p; i++) {
            pop_heap(insts.begin(), insts.end());
            auto &inst = insts.back();
            inst.scores++;
            inst.max_crowd = inst.musicians / inst.scores
                          + (inst.musicians % inst.scores == 0 ? 0 : 1);
            push_heap(insts.begin(), insts.end());
        }

        pop_heap(insts.begin(), insts.end());
        cout << insts.back().max_crowd << endl;
    }
    return 0;
}
