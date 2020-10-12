// #longest_increasing_subsequence #dynamic_programming
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct summary
{
    uint32_t inc_length;
    uint32_t dec_length;
    uint32_t max_inc_length;
    uint32_t max_dec_length;
};

pair<uint32_t, uint32_t> get(
    const vector<summary> &summaries,
    const uint32_t begin,
    const uint32_t size)
{
    const uint32_t m = begin + size / 2;
    return (size == 0)
        ? pair<uint32_t, uint32_t>(0, 0)
        : pair<uint32_t, uint32_t>(summaries[m].max_inc_length, summaries[m].max_dec_length);
}

void update(
    const pair<uint32_t, uint32_t> context,
    const vector<uint32_t> &sorted_heights,
    const uint32_t begin,
    const uint32_t size,
    const uint32_t height,
    const uint32_t width,
    vector<summary> &summaries)
{
    uint32_t m = begin + size / 2;

    if (height < sorted_heights[m]) {
        const auto right = get(summaries, begin + size / 2 + 1, size - size / 2 - 1);
        const uint32_t max_dec_length = max(max(context.second, right.second), summaries[m].dec_length);
        update(
            { context.first, max_dec_length },
            sorted_heights,
            begin,
            size / 2,
            height,
            width,
            summaries);

        const auto left = get(summaries, begin, size / 2);
        summaries[m].max_inc_length = max(left.first, summaries[m].max_inc_length);
        summaries[m].max_dec_length = max(left.second, summaries[m].max_dec_length);
    }
    else if (height == sorted_heights[m]) {
        const auto left = get(summaries, begin, size / 2);
        const auto right = get(summaries, begin + size / 2 + 1, size - size / 2 - 1);
        summaries[m].inc_length = max(
            max(context.first, left.first) + width,
            summaries[m].inc_length);
        summaries[m].dec_length =
            max(max(context.second, right.second) + width,
            summaries[m].dec_length);
        summaries[m].max_inc_length = max(summaries[m].inc_length, summaries[m].max_inc_length);
        summaries[m].max_dec_length = max(summaries[m].dec_length, summaries[m].max_dec_length);
    }
    else {
        auto left = get(summaries, begin, size / 2);
        const uint32_t max_inc_length = max(max(context.first, left.first), summaries[m].inc_length);

        update(
            { max_inc_length, context.second },
            sorted_heights,
            begin + size / 2 + 1,
            size - size / 2 - 1,
            height,
            width,
            summaries);

        const auto right = get(summaries, begin + size / 2 + 1, size - size / 2 - 1);
        summaries[m].max_inc_length = max(right.first, summaries[m].max_inc_length);
        summaries[m].max_dec_length = max(right.second, summaries[m].max_dec_length);
    }
}

int main()
{
    uint32_t case_count, n;
    cin >> case_count;

    vector<uint32_t> heights, sorted_heights, widths;
    vector<summary> summaries;

    for (uint32_t case_number = 1; case_number <= case_count && cin >> n; ++case_number) {
        heights.resize(n);
        for (auto &h: heights)
            cin >> h;

        sorted_heights.assign(heights.begin(), heights.end());
        sort(sorted_heights.begin(), sorted_heights.end());
        sorted_heights.erase(unique(sorted_heights.begin(), sorted_heights.end()), sorted_heights.end());

        summaries.assign(sorted_heights.size(), summary{ 0, 0, 0, 0 });

        widths.resize(n);
        for (auto &w: widths)
            cin >> w;

        for (uint32_t i = 0; i < n; ++i) {
            update(
                pair<uint32_t, uint32_t>(0, 0),
                sorted_heights,
                0,
                sorted_heights.size(),
                heights[i],
                widths[i],
                summaries);
        }

        uint32_t inc_length = 0, dec_length = 0;
        for (const auto &s: summaries) {
            inc_length = max(s.inc_length, inc_length);
            dec_length = max(s.dec_length, dec_length);
        }

        if (inc_length >= dec_length)
            cout << "Case " << case_number
                << ". Increasing (" << inc_length << ")"
                << ". Decreasing (" << dec_length << ")." << endl;
        else
            cout << "Case " << case_number
                << ". Decreasing (" << dec_length << ")"
                << ". Increasing (" << inc_length << ")." << endl;
    }

    return 0;
}
