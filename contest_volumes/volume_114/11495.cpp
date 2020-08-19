// #sort
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool is_swap_count_even(const uint32_t size, uint32_t *xs, uint32_t *ys)
{
    if (size <= 1)
        return true;
    else {
        const uint32_t m = size / 2;
        bool is_even = is_swap_count_even(m, xs, ys);
        is_even = (is_even == is_swap_count_even(size - m, xs + m, ys + m));

        for (uint32_t i = 0, j = m, k = 0; k < size; ++k)
            if (j == size || (i < m && xs[i] <= xs[j]))
                ys[k] = xs[i++];
            else {
                ys[k] = xs[j++];
                is_even = (is_even == ((m - i) % 2 == 0));
            }
        copy(ys, ys + size, xs);

        return is_even;
    }
}

int main()
{
    vector<uint32_t> xs, ys;

    for (uint32_t n; cin >> n && n > 0; ) {
        xs.resize(n);
        for (auto &x: xs)
            cin >> x;
        ys.resize(n);

        cout << (is_swap_count_even(n, xs.data(), ys.data()) ? "Carlos" : "Marcelo") << endl;
    }

    return 0;
}
