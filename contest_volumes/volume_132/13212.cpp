// #sort
#include <iostream>
#include <vector>
using namespace std;

pair<uint32_t *, uint64_t> merge_sort(uint32_t *a, uint32_t *b, uint32_t size)
{
    if (size <= 1)
        return pair<uint32_t *, uint64_t>(a, 0);
    else {
        uint32_t m = size / 2;
        auto left  = merge_sort(a, b, m);
        auto right = merge_sort(a + m, b + m, size - m);

        uint32_t *out = (left.first == a) ? b : a;
        uint64_t inv_count = left.second + right.second;
        for (uint32_t i = 0, j = 0, k = 0; k < size; k++)
            if (i == m)
                out[k] = right.first[j++];
            else if (j == size - m || left.first[i] <= right.first[j])
                out[k] = left.first[i++];
            else {
                out[k] = right.first[j++];
                inv_count += m - i;
            }

        return pair<uint32_t *, uint64_t>(out, inv_count);
    }
}

int main()
{
    vector<uint32_t> a, b;
    for (uint32_t n; cin >> n && n > 0; ) {
        a.resize(n);
        for (auto &v: a)
            cin >> v;

        b.resize(n);
        cout << merge_sort(a.data(), b.data(), n).second << endl;
    }

    return 0;
}
