// #exponentiation
#include <iostream>
#include <vector>
using namespace std;

typedef vector<uint16_t> row;
typedef vector<row> matrix;

ostream &operator<<(ostream &os, const matrix &m)
{
    for (auto &r: m) {
        for (size_t i = 0; i < r.size() - 1; i++)
            os << r[i] << " ";
        os << r.back() << endl;
    }
    return os;
}

matrix &operator+=(matrix &m, const matrix &n)
{
    for (size_t r = 0; r < m.size(); r++)
        for (size_t c = 0; c < m[r].size(); c++)
            m[r][c] = (m[r][c] + n[r][c]) % 10;
    return m;
}

matrix operator*(const matrix &m1, const matrix &m2)
{
    matrix m(m1.size(), row(m2[0].size(), 0));
    for (size_t r = 0; r < m1.size(); r++)
        for (size_t c = 0; c < m2[0].size(); c++)
            for (size_t j = 0; j < m1[0].size(); j++)
                m[r][c] = (m[r][c] + m1[r][j] * m2[j][c]) % 10;
    return m;
}

matrix power(const matrix &m, int e)
{
    vector<matrix> ms(1, m);
    for (int i = 2; i <= e; i *= 2)
        ms.push_back(ms.back() * ms.back());
    for (; ms.size() > 1; ms.pop_back())
        if ((e & (1 << (ms.size()-2))) == 0)
            ms[ms.size()-2].swap(ms.back());
        else
            ms[ms.size()-2] = ms[ms.size()-2] * ms.back();
    return ms[0];
}

matrix sum(const matrix &m, int k)
{
    if (k == 1)
        return m;
    else {
        matrix s = sum(m, k/2);
        matrix n = power(m, (k % 2 == 0) ? k/2 : (k/2 + 1));
        matrix o = n * s;
        if (k % 2 != 0)
            s += n;
        s += o;
        return s;
    }
}

int main()
{
    int n, k;
    while (cin >> n >> k && n != 0) {
        matrix m(n, row(n));
        for (auto &r: m)
            for (auto &e: r) {
                uint32_t v;
                cin >> v;
                e = v % 10;
            }
        m = sum(m, k);
        cout << m << endl;
    }

    return 0;
}
