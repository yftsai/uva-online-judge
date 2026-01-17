// #search
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct prefix_t
{
    vector<pair<char, uint16_t>> seqs;
    uint16_t len;
    uint16_t ones;

    void clear();
    void push(char c, uint16_t count);
    void pop(uint16_t count);

    // use special states to present ambiguous
    bool is_ambiguous(uint16_t l) const { return len > 0 && len != l; }

    bool operator!=(const prefix_t &p) const;
    prefix_t &operator=(const prefix_t &p);
};

void prefix_t::clear()
{
    seqs.clear();
    len = 0;
    ones = 0;
}

void prefix_t::push(char c, uint16_t count)
{
    if (seqs.empty() || seqs.back().first != c)
        seqs.emplace_back(c, count);

    else
        seqs.back().second += count;

    len += count;
    if (c == '1')
        ones += count;
}

void prefix_t::pop(uint16_t count)
{
    if (seqs.back().first == '1')
        ones -= count;
    len -= count;

    seqs.back().second -= count;
    if (seqs.back().second == 0)
        seqs.pop_back();
}

bool prefix_t::operator!=(const prefix_t &p) const
{
    if (len != p.len || ones != p.ones || seqs.size() != p.seqs.size())
        return true;
    for (uint16_t i = 0; i < seqs.size(); i++)
        if (seqs[i] != p.seqs[i])
            return true;
    return false;
}

prefix_t &prefix_t::operator=(const prefix_t &p)
{
    seqs = p.seqs;
    len = p.len;
    return *this;
}

void decode(const string &comp, uint16_t l, uint16_t n,
            uint16_t i,
            prefix_t &pref,
            prefix_t &orig)
{
    // consume zeros
    uint16_t front = i;
    for (; front < comp.size() && comp[front] == '0'; front++)
        ;
    if (front != i)
        pref.push('0', front - i);

    if (front == comp.size()) {
        if (pref.len == l && pref.ones == n) {
            if (orig.seqs.empty())
                orig = pref;
            else if (orig != pref)
                orig.push('0', 1);  // make it ambiguous
        }
    }
    else {
        for (uint16_t back = front, count = 0; back < comp.size(); back++) {
            count = (count << 1) | (comp[back] - '0');

            // There is a special cases: both ...0110... and ...01110... are
            // compressed into ...0110....
            if (orig.is_ambiguous(l) || pref.len + (count == 3 ? 2 : count) > l)
                break;

            if (back + 1u == comp.size() || comp[back + 1] == '0') {
                if (count == 3) {
                    pref.push('1', 2);
                    decode(comp, l, n, back + 1, pref, orig);
                    pref.pop(2);
                }

                if (count != 2) {
                    pref.push('1', count);
                    decode(comp, l, n, back + 1, pref, orig);
                    pref.pop(count);
                }
            }
        }
    }

    if (front != i)
        pref.pop(front - i);
}

int main()
{
    uint16_t l, n;
    string comp;
    prefix_t orig, pref;

    for (uint32_t case_no = 1; cin >> l && l > 0 && cin >> n >> comp; case_no++) {
        pref.clear();
        orig.clear();
        decode(comp, l, n, 0, pref, orig);

        cout << "Case #" << case_no << ": ";
        if (orig.len == 0)
            cout << "NO" << endl;
        else if (orig.is_ambiguous(l))
            cout << "NOT UNIQUE" << endl;
        else
            cout << "YES" << endl;
    }

    return 0;
}
