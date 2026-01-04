// #shortest_path
#include <bitset>
#include <cstdint>
#include <iostream>
#include <limits>
#include <set>
#include <vector>
using namespace std;

constexpr uint16_t N = 20;
typedef bitset<N> state_t;

struct patch
{
    uint32_t time;
    state_t pre_present;
    state_t pre_mask;

    state_t post_and;
    state_t post_or;

    void init_precond(const char *);
    void init_postcond(const char *);

    bool can_apply(uint32_t s) const;
    uint32_t apply(uint32_t s) const;
};

void patch::init_precond(const char *p)
{
    pre_present = pre_mask = 0;
    for (uint32_t i = 0, b = 1; p[i] != '\0'; i++, b <<= 1)
        if (p[i] == '+')
            pre_present |= b;
        else if (p[i] == '-')
            pre_mask |= b;
    pre_mask |= pre_present;
}

void patch::init_postcond(const char *p)
{
    post_or = post_and = 0;
    for (uint32_t i = 0, b = 1; p[i] != '\0'; i++, b <<= 1)
        if (p[i] == '+')
            post_or |= b;
        else if (p[i] == '-')
            post_and |= b;
    post_and = ~post_and;
}

bool patch::can_apply(uint32_t s) const
{
    return (state_t(s) & pre_mask) == pre_present;
}

uint32_t patch::apply(uint32_t s) const
{
    return ((state_t(s) & post_and) | post_or).to_ulong();
}

int main()
{
    char cond[21];
    vector<patch> patches;
    vector<uint32_t> times;
    uint16_t n, m;

    for (uint32_t p = 1; cin >> n >> m && n != 0; p++) {
        patches.resize(m);
        for (auto &p: patches) {
            cin >> p.time;
            cin >> cond;
            p.init_precond(cond);
            cin >> cond;
            p.init_postcond(cond);
        }

        times.clear();
        times.resize(1u << n, numeric_limits<uint32_t>::max());
        const uint32_t s_init = (1u << n) - 1;
        times[s_init] = 0;

        set<pair<uint32_t, uint32_t>> pq;   // reachable time, status
        pq.emplace(times[s_init], s_init);

        while (!pq.empty() && pq.begin()->second != 0) {
            uint32_t t = pq.begin()->first;
            uint32_t s = pq.begin()->second;
            pq.erase(pq.begin());

            for (const auto &p: patches)
                if (p.can_apply(s)) {
                    uint32_t s_next = p.apply(s);
                    uint32_t t_next = t + p.time;

                    if (t_next < times[s_next]) {
                        pq.erase(decltype(pq)::key_type(times[s_next], s_next));
                        times[s_next] = t_next;
                        pq.emplace(decltype(pq)::key_type(times[s_next], s_next));
                    }
                }
        }

        cout << "Product " << p << endl;
        if (!pq.empty())
            cout << "Fastest sequence takes " << pq.begin()->first << " seconds." << endl;
        else
            cout << "Bugs cannot be fixed." << endl;
        cout << endl;
    }

    return 0;
}
