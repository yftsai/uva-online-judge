// #maximum_flow
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <functional>
using namespace std;

struct flight
{
    int u, v, c, p, e;
    bool operator>(const flight &f) const
    {
        return p > f.p;
    }
};

int get_node_id(int city, int d)
{
    return city * 11 + d;
}

typedef map<int, map<int, int>> edges;

int get_max_flow(edges &flows, int src, int dst)
{
    while (true) {
        map<int, int> parents;
        queue<int> q;
        q.push(src);
        while (parents.find(dst) == parents.end() && !q.empty()) {
            const int n = q.front();
            q.pop();
            for (auto &p: flows[n])
                if (parents.find(p.first) == parents.end()) {
                    parents[p.first] = n;
                    q.push(p.first);
                }
        }

        if (parents.find(dst) == parents.end())
            break;
        else {
            int f = flows[ parents[dst] ][dst];
            for (int i = parents[dst]; i != src; i = parents[i])
                f = min(f, flows[ parents[i] ][i]);
            for (int i = dst, j; i != src; i = j) {
                j = parents[i];
                if (flows[i].find(j) == flows[i].end())
                    flows[i][j] = f;
                else
                    flows[i][j] += f;

                if (flows[j][i] == f)
                    flows[j].erase(i);
                else
                    flows[j][i] -= f;
            }
        }
    }

    int flow = 0;
    for (auto &p: flows[dst])
        flow += p.second;
    return flow;
}

int main()
{
    int case_count;
    vector<struct flight> flights;

    cin >> case_count;
    for (int case_number = 1; case_number <= case_count; case_number++) {
        int n, d, m;
        cin >> n >> d >> m;
        flights.resize(m);
        for (flight &f: flights)
            cin >> f.u >> f.v >> f.c >> f.p >> f.e;

        edges flows;
        const int src = 0, dst = get_node_id(n, d);
        int participant_count = 0;
        for (int i = 1, z; i <= n && cin >> z; i++) {
            participant_count += z;
            if (z != 0)
                flows[src][get_node_id(i, 0)] = z;
        }
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < d; j++)
                flows[get_node_id(i, j)][get_node_id(i, j + 1)] = participant_count;

        sort(flights.begin(), flights.end(), std::greater<flight>());
        int min_cost = 0, max_flow;
        while ((max_flow = get_max_flow(flows, src, dst)) != participant_count && !flights.empty()) {
            min_cost = flights.back().p;
            for (; !flights.empty() && flights.back().p <= min_cost; flights.pop_back()) {
                const flight &f = flights.back();
                const int n = get_node_id(f.u, f.e), m = get_node_id(f.v, f.e + 1);
                if (flows[n].find(m) == flows[n].end())
                    flows[n][m] = f.c;
                else
                    flows[n][m] += f.c;
            }
        }

        cout << "Case #" << case_number << ": ";
        if (max_flow == participant_count)
            cout << min_cost << endl;
        else
            cout << "Impossible" << endl;
    }

    return 0;
}
