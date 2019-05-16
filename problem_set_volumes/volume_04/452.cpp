// #topological_sort
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    struct {
        uint16_t days;
        vector<uint16_t> successors;
        uint16_t pred_count;
        uint32_t completion_day;
    } tasks[26];
    vector<uint16_t> ready_tasks;
    vector<uint16_t> predecessors;

    string line;
    getline(cin, line);
    unsigned long test_count = stoul(line);
    for (getline(cin, line); test_count > 0; --test_count) {
        while (getline(cin, line) && line.size() > 0) {
            stringstream ss(line);
            char t;
            ss >> t;
            const uint16_t ti = t - 'A';
            ss >> tasks[ti].days;

            predecessors.clear();
            for (char p; ss >> p; )
                predecessors.push_back(p - 'A');
            tasks[ti].pred_count = uint16_t(predecessors.size());
            tasks[ti].completion_day = 0;

            if (tasks[ti].pred_count == 0)
                ready_tasks.push_back(ti);
            else
                for (uint16_t pi: predecessors)
                    tasks[pi].successors.push_back(ti);
        }

        uint32_t completion_day = 0;
        while (!ready_tasks.empty()) {
            uint16_t t = ready_tasks.back();
            ready_tasks.pop_back();
            tasks[t].completion_day += tasks[t].days;
            completion_day = max(completion_day, tasks[t].completion_day);
            for (uint16_t s: tasks[t].successors) {
                tasks[s].completion_day = max(tasks[s].completion_day, tasks[t].completion_day);
                if (--tasks[s].pred_count == 0)
                    ready_tasks.push_back(s);
            }
            tasks[t].successors.clear();
        }
        cout << completion_day << endl;
        if (test_count > 1)
            cout << endl;
    }

    return 0;
}
