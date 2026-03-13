#include <cstdint>
#include <iostream>
#include <bitset>
#include <string>
#include <vector>
using namespace std;

typedef bitset<100> bin_t;

struct signature_t
{
    uint16_t size;
    bin_t bits;

    signature_t(const string &);
};

signature_t::signature_t(const string &s)
{
    size = s.size();
    for (uint16_t j = 0; j < s.size(); j++)
        if (s[j] == '1')
            bits.set(j);
}

uint16_t match(const bin_t &ones, const signature_t &clip, signature_t movie)
{
    uint16_t s = 0;
    bin_t mask = ones ^ clip.bits;
    for (; movie.size >= clip.size; movie.size--, movie.bits >>= 1) {
        auto matches = (movie.bits ^ mask) & ones;
        s = max<decltype(s)>(matches.count(), s);
    }
    return s;
}

int main()
{
    uint16_t m, q;
    cin >> m >> q;

    vector<signature_t> movies;
    movies.reserve(m);
    string binary;
    for (uint16_t i = 0; i < m && cin >> binary; i++)
        movies.emplace_back(binary);

    for (uint16_t i = 0; i < q && cin >> binary; i++) {
        signature_t clip(binary);
        bin_t ones;
        for (uint16_t j = 0; j < clip.size; j++)
            ones.set(j);

        uint16_t index = m, similarity = 0;
        for (uint16_t j = 0; j < m; j++)
            if (movies[j].size >= clip.size) {
                auto s = match(ones, clip, movies[j]);
                if (index == m || s > similarity) {
                    index = j;
                    similarity = s;
                }
            }
        cout << (index + 1) << endl;
    }

    return 0;
}
