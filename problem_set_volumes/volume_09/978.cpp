// #easy
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    uint16_t n;
    uint32_t b, sg, sb;
    vector<uint16_t> gpowers, bpowers;
    vector<uint16_t> gwinners, bwinners;
    for (cin >> n; n > 0 && cin >> b >> sg >> sb; --n) {
        gpowers.resize(sg);
        for (auto &p: gpowers)
            cin >> p;
        make_heap(gpowers.begin(), gpowers.end());
        bpowers.resize(sb);
        for (auto &p: bpowers)
            cin >> p;
        make_heap(bpowers.begin(), bpowers.end());

        while (gpowers.size() > 0 && bpowers.size() > 0) {
            for (uint16_t i = 0; i < b && gpowers.size() > 0 && bpowers.size() > 0; ++i) {
                if (gpowers.front() < bpowers.front())
                    bwinners.push_back(bpowers.front() - gpowers.front());
                else if (gpowers.front() > bpowers.front())
                    gwinners.push_back(gpowers.front() - bpowers.front());
                pop_heap(gpowers.begin(), gpowers.end());
                gpowers.pop_back();
                pop_heap(bpowers.begin(), bpowers.end());
                bpowers.pop_back();
            }

            for (auto p: gwinners) {
                gpowers.push_back(p);
                push_heap(gpowers.begin(), gpowers.end());
            }
            gwinners.clear();
            for (auto p: bwinners) {
                bpowers.push_back(p);
                push_heap(bpowers.begin(), bpowers.end());
            }
            bwinners.clear();
        }

        auto &survivors = (gpowers.size() > 0) ? gpowers : bpowers;
        sort_heap(survivors.begin(), survivors.end());
        if (gpowers.size() == 0 && bpowers.size() == 0)
            cout << "green and blue died" << endl;
        else
            cout << ((gpowers.size() > 0) ? "green" : "blue") << " wins" << endl;
        for (auto it = survivors.rbegin(); it != survivors.rend(); ++it)
            cout << *it << endl;
        if (n > 1)
            cout << endl;
    }

    return 0;
}
