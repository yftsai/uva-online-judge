// #blossom_algorithm
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

void augment(const vector<vector<uint16_t>> &graph,
             const vector<uint16_t> &path,
             vector<uint16_t> &matches)
{
    for (uint16_t i = 0; i < path.size(); i += 2) {
        matches[ path[i] ] = path[i + 1];
        matches[ path[i + 1] ] = path[i];
    }
}

void find_augment_path(const vector<vector<uint16_t>> &graph,
                       const vector<uint16_t> &matches,
                       uint16_t start,
                       vector<uint16_t> &rpath)
{
    const uint16_t node_count = graph.size(), invalid_node = graph.size();
    assert(matches[start] == matches.size());
    vector<uint16_t> parents(graph.size(), invalid_node);
    queue<uint16_t> q;
    rpath.resize(0);

    uint16_t end = invalid_node;
    for (q.push(start); q.size() > 0 && end == invalid_node; ) {
        const uint16_t m = q.front();
        q.pop();

        for (const uint16_t n: graph[m])
            if (matches[n] == invalid_node || parents[ matches[n] ] != invalid_node) {
                parents[end = n] = m;
                break;
            }
            else if (parents[n] == invalid_node) {
                parents[n] = m;
                q.push(matches[n]);
            }
    }

    if (end == invalid_node)
        ;
    else if (end != start && matches[end] == invalid_node) {
        for (int p; parents[end] != start; end = matches[p]) {
            rpath.push_back(end);
            rpath.push_back(p = parents[end]);
        }
        rpath.push_back(end);
        rpath.push_back(start);
    }
    else {
        vector<bool> blossom(node_count, false);
        for (uint16_t n = end; n != start; n = parents[ matches[n] ]) {
            blossom[n] = true;
            blossom[ matches[n] ] = true;
        }
        uint16_t lca = invalid_node;
        for (uint16_t n = parents[end]; n != start && lca == invalid_node; n = parents[ matches[n] ]) {
            if (blossom[n])
                lca = n;
            else
                blossom[n] = true;
            blossom[ matches[n] ] = true;
        }
        lca = (lca == invalid_node) ? start : lca;
        for (uint16_t m = parents[end], n = end; n != lca; n = parents[ matches[n] ]) {
            parents[n] = m;
            m = matches[n];
        }
        for (uint16_t m = end, n = parents[end]; n != lca; n = parents[ matches[n] ]) {
            parents[n] = m;
            m = matches[n];
        }
        for (uint16_t n = lca; n != start; n = parents[ matches[n] ])
            blossom[n] = blossom[ matches[n] ] = false;

        vector<vector<uint16_t>> g(graph.size());
        for (uint16_t i = 0; i < node_count; ++i) {
            uint16_t gi = blossom[i] ? lca : i;
            auto &es = g[gi];
            for (uint16_t j: graph[i]) {
                uint16_t gj = blossom[j] ? lca : j;
                if (gi != gj)
                    es.push_back(gj);
            }
            sort(es.begin(), es.end());
            es.erase(unique(es.begin(), es.end()), es.end());
        }

        vector<uint16_t> rp;
        find_augment_path(g, matches, start, rp);
        for (uint16_t i = 0; i < rp.size(); ++i) {
            if (rp[i] != lca)
                rpath.push_back(rp[i]);
            else {
                assert(i > 0 && rp[i - 1] != lca);
                uint16_t n = rp[i - 1];
                auto it = find_if(graph[n].begin(), graph[n].end(), [&](uint16_t m) { return blossom[m]; });
                if (it != graph[n].end())
                    for (n = *it; n != lca; n = parents[ matches[n] ]) {
                        assert(matches[n] != invalid_node);
                        assert(parents[ matches[n] ] != invalid_node);
                        rpath.push_back(n);
                        rpath.push_back(matches[n]);
                    }
                rpath.push_back(lca);
            }
        }

        assert(rpath.size() % 2 == 0);
    }
}

struct edge
{
    uint8_t i, j;
    int icpc;
    bool operator<(const edge &e)   { return icpc < e.icpc; }
};

int main()
{
    vector<edge> edges;
    vector<int> icpcs;
    vector<uint16_t> matches, path;

    uint32_t case_count;
    cin >> case_count;
    for (uint32_t case_number = 1, n; case_number <= case_count && cin >> n; ++case_number, edges.clear()) {
        const uint16_t node_count = 1 << n;
        for (uint8_t i = 0; i < node_count; ++i)
            for (int j = i + 1, icpc; j < node_count && cin >> icpc; ++j)
                edges.push_back(edge {i, uint8_t(j), icpc});
        sort(edges.begin(), edges.end());

        icpcs.resize(edges.size());
        transform(edges.begin(), edges.end(), icpcs.begin(), [](const edge &e) { return e.icpc; });
        icpcs.erase(unique(icpcs.begin(), icpcs.end()), icpcs.end());

        const uint16_t invalid_node = node_count;
        auto edges_begin = edges.begin();
        size_t icpcs_begin = 0, icpcs_end = icpcs.size();
        matches.assign(node_count, invalid_node);
        while (icpcs_begin + 1u < icpcs_end) {
            size_t icpcs_mid = (icpcs_begin + icpcs_end) / 2u;
            vector<vector<uint16_t>> graph(node_count);
            for (auto it = edges_begin; it != edges.end(); ++it)
                if (it->icpc >= icpcs[icpcs_mid]) {
                    graph[it->i].push_back(it->j);
                    graph[it->j].push_back(it->i);
                }
            uint16_t m;
            for (m = 0; m < node_count; ++m)
                if (matches[m] == invalid_node) {
                    find_augment_path(graph, matches, m, path);
                    if (path.size() > 0)
                        augment(graph, path, matches);
                    else
                        break;
                }

            if (m == node_count) {
                icpcs_begin = icpcs_mid;
                edges_begin = lower_bound(edges_begin, edges.end(), edge { 0, 0, icpcs[icpcs_mid] });
                matches.assign(node_count, invalid_node);
            }
            else
                icpcs_end = icpcs_mid;
        }
        cout << "Case " << case_number << ": " << icpcs[icpcs_begin] << endl;
    }

    return 0;
}
