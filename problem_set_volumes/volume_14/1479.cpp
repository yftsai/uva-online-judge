// #set_union
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
using namespace std;

class sorted_list
{
    private:
        static const uint16_t segment_max_length = 128;
        vector<vector<int>> segments;

    public:
        void insert(int v);
        void remove(int v);
        void merge(sorted_list &&sl);
        int operator[](int index) const;
};

int sorted_list::operator[](int index) const
{
    if (index < 0)
        return 0;
    else {
        uint16_t sindex = 0;
        for (; sindex < segments.size() && (unsigned int)index >= segments[sindex].size(); index -= segments[sindex++].size())
            ;
        if (sindex >= segments.size())
            return 0;
        else
            return segments[sindex][index];
    }
}

void sorted_list::insert(int v)
{
    uint16_t sindex = 0;
    for (; sindex < segments.size() && v < segments[sindex].back(); sindex++)
        ;
    if (sindex == segments.size())
        segments.emplace_back(1, v);
    else {
        auto it = upper_bound(segments[sindex].begin(), segments[sindex].end(), v, std::greater<int>());
        segments[sindex].insert(it, v);

        if (segments[sindex].size() > segment_max_length) {
            it = segments[sindex].begin() + segment_max_length / 2u;
            segments.emplace(segments.begin() + sindex + 1u, it, segments[sindex].end());
            segments[sindex].erase(it, segments[sindex].end());
        }
    }
}

void sorted_list::remove(int v)
{
    auto cmp = [](const vector<int> &segment, int v) { return segment.back() > v; };
    auto it = lower_bound(segments.begin(), segments.end(), v, cmp);
    it->erase(prev(upper_bound(it->begin(), it->end(), v, std::greater<int>())));
    if (it->size() == 0)
        segments.erase(it);
}

void sorted_list::merge(sorted_list &&sl)
{
    vector<vector<int>> result;
    for (auto si = segments.begin(), sj = sl.segments.begin(); si != segments.end() || sj != sl.segments.end(); )
        if (si == segments.end() || (sj != sl.segments.end() && sj->back() >= si->front())) {
            if (result.size() == 0 || result.back().size() + sj->size() >= segment_max_length)
                result.push_back(move(*sj));
            else
                result.back().insert(result.back().end(), sj->begin(), sj->end());
            sj++;
        }
        else if (sj == sl.segments.end() || si->back() >= sj->front()) {
            if (result.size() == 0 || result.back().size() + si->size() >= segment_max_length)
                result.push_back(move(*si));
            else
                result.back().insert(result.back().end(), si->begin(), si->end());
            si++;
        }
        else {
            uint16_t i = 0, j = 0;
            while (i < si->size() && j < sj->size()) {
                if (result.size() == 0 || result.back().size() >= segment_max_length)
                    result.emplace_back();
                if ((*si)[i] >= (*sj)[j])
                    result.back().push_back((*si)[i++]);
                else
                    result.back().push_back((*sj)[j++]);
            }

            if (i >= si->size())
                si++, sj->erase(sj->begin(), sj->begin() + j);
            else
                sj++, si->erase(si->begin(), si->begin() + i);
        }
    swap(result, segments);
    vector<vector<int>> empty;
    sl.segments.swap(empty);
}

typedef struct
{
    int weight;
    uint16_t set_id;
    sorted_list connected_weights;
} node;

node &find(vector<node> &nodes, uint16_t i)
{
    uint16_t s;
    for (s = i; nodes[s].set_id != s; s = nodes[s].set_id)
        ;
    for (uint16_t t; (t = nodes[i].set_id) != s; i = t)
        nodes[i].set_id = s;
    return nodes[s];
}

void connect(vector<node> &nodes, uint16_t i, uint16_t j)
{
    node &n = find(nodes, i);
    node &m = find(nodes, j);
    if (n.set_id != m.set_id) {
        n.set_id = m.set_id;
        m.connected_weights.merge(move(n.connected_weights));
    }
}

typedef struct {
    char opcode;
    uint16_t x;
    int k;
} operation;

int main()
{
    vector<node> nodes;
    vector<pair<uint16_t, uint16_t>> edges;
    vector<operation> operations;

    cout.setf(ios::fixed);
    cout.precision(6);
    for (uint16_t n, m, case_number = 1; cin >> n >> m && n != 0; case_number++) {
        nodes.resize(n);
        for (node &n: nodes)
            cin >> n.weight;
        edges.resize(m);
        for (pair<uint16_t, uint16_t> &e: edges)
            cin >> e.first >> e.second;

        for (operations.resize(1); cin >> operations.back().opcode && operations.back().opcode != 'E'; operations.emplace_back()) {
            cin >> operations.back().x;

            if (operations.back().opcode == 'D')
                edges[operations.back().x - 1u].first += n;
            else if (operations.back().opcode == 'Q')
                cin >> operations.back().k;
            else {
                cin >> operations.back().k;
                swap(nodes[operations.back().x - 1u].weight, operations.back().k);
            }
        }

        for (uint16_t i = 0; i < n; i++) {
            nodes[i].set_id = i;
            (nodes[i].connected_weights = sorted_list()).insert(nodes[i].weight);
        }

        for (pair<uint16_t, uint16_t> &e: edges)
            if (e.first <= n)
                connect(nodes, e.first - 1u, e.second - 1u);
            else
                e.first -= n;

        int64_t query_sum = 0;
        uint32_t query_count = 0;
        operations.pop_back();
        reverse(operations.begin(), operations.end());
        for (operation &op: operations) {
            if (op.opcode == 'D')
                connect(nodes, edges[op.x - 1u].first - 1u, edges[op.x - 1u].second - 1u);
            else if (op.opcode == 'Q') {
                query_sum += find(nodes, op.x - 1u).connected_weights[op.k - 1];
                query_count++;
            }
            else {
                find(nodes, op.x - 1u).connected_weights.remove(nodes[op.x - 1u].weight);
                find(nodes, op.x - 1u).connected_weights.insert(op.k);
                swap(nodes[op.x - 1u].weight, op.k);
            }
        }

        cout << "Case " << case_number << ": " << double(query_sum)/query_count << endl;
    }

    return 0;
}
