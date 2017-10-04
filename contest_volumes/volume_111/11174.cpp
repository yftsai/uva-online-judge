// #arithmetic #modulo
// The main challenge is obtaining (a/b) % p from a' = a % p, b, and p.
// Given b is relatively prime to p, there is exactly one q within (0, p) such that
// (b * q) % p == 1. Similarly, r = (a' * q) % p is the only value within [0, p)
// such that (r * b) % p == a % p. Hence, it is equivalent to compute (a' * q) % p.
#include <iostream>
#include <vector>
using namespace std;

constexpr uint32_t p = 1000000007;  // the given prime number
constexpr uint16_t max_n = 40000;

// returns (a, b) where a * x + b * y = gcd(x, y) as x >= 1 and y >= 1
// Note: abs(a) <= y and abs(b) <= x, so overflow is impossible.
pair<int32_t, int32_t> gcd(uint32_t x, uint32_t y)
{
    if (x % y == 0)
        return pair<int32_t, int32_t>(0, 1);
    else {
        int32_t c = x / y;
        pair<int32_t, int32_t> ab = gcd(y, x % y);
        return pair<int32_t, int32_t>(ab.second, ab.first - ab.second * c);
    } 
}

// returns (tree size, combination count)
pair<uint16_t, uint32_t> count(
    const vector<uint32_t> &factorials,
    const vector<uint32_t> &inverses,
    const vector<vector<int>> &children,
    int i)
{
    uint16_t sz = 0;
    uint32_t cnt = 1;
    for (int j: children[i]) {
        pair<uint16_t, uint32_t> sc = count(factorials, inverses, children, j);
        cnt = (uint64_t(cnt) * sc.second) % p;
        cnt = (uint64_t(cnt) * inverses[sc.first]) % p;
        sz += sc.first;
    }
    cnt = (uint64_t(cnt) * factorials[sz]) % p;
    sz += 1;
    return pair<uint16_t, uint32_t>(sz, cnt);
}

int main()
{
    vector<uint32_t> factorials(max_n + 2), inverses(max_n + 2);
    factorials[0] = inverses[0] = 1;
    for (uint16_t i = 1; i <= max_n + 1; i++) {
        factorials[i] = uint32_t((uint64_t(factorials[i - 1]) * i) % p);
        auto ab = gcd(factorials[i], p);
        inverses[i] = (ab.first < 0) ? (ab.first + p) : ab.first;
    }

    int t, n, m;
    for (cin >> t; t > 0; t--) {
        cin >> n >> m;

        vector<bool> is_root(n + 1, true);
        vector<vector<int>> children(n + 1);
        for (int a, b; m > 0 && cin >> a >> b; m--) {
            is_root[a - 1] = false;
            children[b - 1].push_back(a - 1);
        }
        for (int i = 0; i < n; i++)
            if (is_root[i])
                children[n].push_back(i);
        pair<uint16_t, uint32_t> p = count(factorials, inverses, children, n);
        cout << p.second << endl;
    }
    return 0;
}
