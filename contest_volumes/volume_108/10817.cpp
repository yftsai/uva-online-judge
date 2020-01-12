// #dynamic_programming
#include <iostream>
#include <sstream>
#include <vector>
#include <bitset>
#include <algorithm>
using namespace std;

struct applicant
{
    uint16_t cost;
    vector<uint16_t> subjects;
};

uint16_t get_teacher_count(uint16_t teachers, uint16_t s)
{
    return (teachers >> (s * 2)) & 3;
}

uint16_t increase_teacher(uint16_t teachers, uint16_t s)
{
    const uint16_t c = get_teacher_count(teachers, s);
    const uint16_t a = 1 << (s * 2);
    return (c < 2) ? (teachers + a) : teachers;
}

struct employment
{
    bitset<100> is_employed;
    uint32_t cost;
};

int main()
{
    vector<employment> employments;
    vector<applicant> applicants;
    vector<vector<uint16_t>> subject_to_applicants;

    for (string line; getline(cin, line); ) {
        stringstream ss(line);
        uint16_t s, m, n;
        ss >> s >> m >> n;
        if (s == 0)
            break;

        uint16_t teachers = 0;
        uint32_t cost = 0;

        for (uint32_t i = 0; i < m && getline(cin, line); ++i) {
            stringstream ss(line);
            uint16_t c;
            ss >> c;
            cost += c;
            for (uint16_t s; ss >> s; )
                teachers = increase_teacher(teachers, s - 1);
        }

        applicants.resize(n);
        subject_to_applicants.assign(s, vector<uint16_t>());
        for (uint16_t a = 0; a < n && getline(cin, line); ++a) {
            stringstream ss(line);
            ss >> applicants[a].cost;
            applicants[a].subjects.clear();
            for (uint16_t s; ss >> s; ) {
                applicants[a].subjects.push_back(s - 1);
                subject_to_applicants[s - 1].push_back(a);
            }
        }

        constexpr uint16_t fully_employed = 0xAAAA;
        const uint16_t mask = (1 << (s * 2)) - 1;
        employments.resize((fully_employed & mask) + 1);
        employments[teachers].cost = cost;
        employments[teachers].is_employed.reset();
        for_each(
            employments.begin() + teachers + 1,
            employments.end(),
            [](employment &e) { e.cost = 0; });
        for (; teachers < employments.size(); ++teachers)
            if (employments[teachers].cost > 0) {
                const employment &e = employments[teachers];
                for (uint16_t subject = 0; subject < s; ++subject)
                    if (get_teacher_count(teachers, subject) < 2)
                        for (uint16_t a: subject_to_applicants[subject]) {
                            if (!e.is_employed[a]) {
                                uint16_t ts = teachers;
                                for (uint16_t s: applicants[a].subjects)
                                    ts = increase_teacher(ts, s);
                                if (employments[ts].cost == 0
                                    || e.cost + applicants[a].cost < employments[ts].cost) {
                                    employments[ts].cost = e.cost + applicants[a].cost;
                                    employments[ts].is_employed = e.is_employed;
                                    employments[ts].is_employed.set(a);
                                }
                            }
                        }
            }
        cout << employments.back().cost << endl;
    }

    return 0;
}
