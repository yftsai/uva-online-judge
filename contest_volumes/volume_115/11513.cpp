// #breadth_first_search
#include <cstdint>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

void get_rows(uint64_t p, uint16_t rows[3])
{
    rows[0] = p >> 24;
    rows[1] = (p >> 12) & 0xFFF;
    rows[2] = p & 0xFFF;
}

enum class hdir_t { LEFT, RIGHT };

uint64_t hshift(const uint16_t rows[3], uint8_t i, hdir_t d)
{
    uint64_t p = 0;
    for (uint8_t j = 0; j < 3; j++)
        if (j != i)
            p = (p << 12) | rows[j];
        else if (d == hdir_t::LEFT)
            p = (p << 12) | ((rows[j] << 4) & 0xFF0) | (rows[j] >> 8);
        else
            p = (p << 12) | (rows[j] >> 4) | ((rows[j] & 0xF) << 8);
    return p;
}

enum class vdir_t { UP, DOWN };

uint64_t vshift(const uint16_t rows[3], uint8_t i, vdir_t d)
{
    constexpr uint16_t clear[3]   = { 0x0FF, 0xF0F, 0xFF0 };
    constexpr uint16_t extract[3] = { 0xF00, 0x0F0, 0x00F };
    uint64_t p = 0;
    int8_t shift = (d == vdir_t::UP) ? 1 : -1;
    for (int8_t j = 0; j < 3; j++)
        p = (p << 12) | (rows[j] & clear[i]) | (rows[(j + 3 + shift) % 3] & extract[i]);
    return p;
}

int main()
{
    uint8_t VBIT  = 0x4;
    uint8_t IMASK = 0x3;
    const uint8_t DONE = 3;
    unordered_map<uint64_t, uint8_t> moves;
    queue<uint64_t> q;
    uint16_t rows[3];

    uint64_t p = 0;
    for (uint64_t i = 1; i <= 9; i++)
        p = (p << 4) | i;

    moves.emplace(p, DONE);
    q.push(p);

    while (!q.empty()) {
        p = q.front();
        q.pop();

        get_rows(p, rows);
        for (uint16_t i = 0; i < 3; i++) {
            uint64_t p = hshift(rows, i, hdir_t::LEFT);
            if (moves.emplace(p, i).second)
                q.push(p);

            p = vshift(rows, i, vdir_t::DOWN);
            if (moves.emplace(p, VBIT | i).second)
                q.push(p);
        }
    }

    vector<uint8_t> seq;
    uint16_t sq;
    while (cin >> sq && sq != 0) {
        uint64_t p = sq;
        for (uint16_t i = 1, sq; i < 9 && cin >> sq; i++)
            p = (p << 4) | sq;

        auto it = moves.find(p);
        seq.clear();
        if (it == moves.end())
            cout << "Not solvable" << endl;
        else {
            for (; it->second != DONE; it = moves.find(p)) {
                seq.push_back(it->second);
                get_rows(p, rows);
                if ((seq.back() & VBIT) != 0)
                    p = vshift(rows, seq.back() & IMASK, vdir_t::UP);
                else
                    p = hshift(rows, seq.back(), hdir_t::RIGHT);
            }
            cout << seq.size() << " ";
            for (auto s: seq)
                cout << ((s & VBIT) == 0 ? 'H' : 'V') << ((s & IMASK) + 1);
            cout << endl;
        }
    }

    return 0;
}
