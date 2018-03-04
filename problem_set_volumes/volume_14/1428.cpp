// #dynamic_programming
// There are other solutions using a binary indexed tree Since the range of
// ranks is larger than the range of player count, it may not be better. It is
// also possible to pass with an unrolled linked list.
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct node
{
    uint32_t rank;
    uint16_t size;
};

uint16_t left(uint16_t index)   { return index * 2u + 1u; }
uint16_t right(uint16_t index)  { return index * 2u + 2u; }

void init(vector<node> &tree, uint16_t index, const uint32_t *&ranks)
{
    if (index < tree.size()) {
        init(tree, left(index), ranks);
        tree[index].rank = *(ranks++);
        tree[index].size = 0;
        init(tree, right(index), ranks);
    }
}

uint16_t find(const vector<node> &tree, const uint32_t rank, pair<uint16_t, uint16_t> *counts)
{
    uint16_t index = 0;
    counts->first = counts->second = 0;
    while (tree[index].rank != rank)
        if (rank < tree[index].rank) {
            counts->second += tree[index].size - tree[left(index)].size;
            index = left(index);
        }
        else {
            counts->first += tree[index].size - tree[right(index)].size;
            index = right(index);
        }

    counts->first += (left(index) < tree.size()) ? tree[left(index)].size : 0;
    counts->second += (right(index) < tree.size()) ? tree[right(index)].size : 0;
    return index;
}

void increase(vector<node> &tree, const uint32_t rank, pair<uint16_t, uint16_t> *counts)
{
    uint16_t index = find(tree, rank, counts);
    for (; index > 0; index = (index - 1u) / 2u)
        tree[index].size++;
    tree[index].size++;
}

int main()
{
    const uint16_t max_n = 20000;
    uint16_t t, n;
    std::vector<uint32_t> ranks(max_n), unique_ranks(max_n);
    std::vector<pair<uint16_t, uint16_t>> prior_counts(max_n);
    std::vector<node> tree(max_n);

    for (cin >> t; t > 0 && cin >> n; t--) {
        ranks.resize(n);
        for (auto &rank: ranks)
            cin >> rank;

        unique_ranks.assign(ranks.begin(), ranks.end());
        unique_ranks.resize(unique(unique_ranks.begin(), unique_ranks.end()) - unique_ranks.begin());
        sort(unique_ranks.begin(), unique_ranks.end());

        const uint32_t *q = unique_ranks.data();
        tree.resize(unique_ranks.size());
        init(tree, 0, q);
        for (int i = 0; i < n; i++)
            increase(tree, ranks[i], &prior_counts[i]);

        uint64_t game_count = 0;
        for (int i = 1; i < n; i++) {
            pair<uint16_t, uint16_t> post_counts;
            find(tree, ranks[i], &post_counts);
            post_counts.first -= prior_counts[i].first;
            post_counts.second -= prior_counts[i].second;

            game_count += i * (n - 1 - i);
            game_count -= prior_counts[i].first * post_counts.first;
            game_count -= prior_counts[i].second * post_counts.second;
        }
        cout << game_count << endl;
    }

    return 0;
}
