// #string_comparison
/*
   A brute-force solution that encrypts word W and searches in text S can be
   accepted. This solution implements KMP to lazily encrypt W and continue the
   second matching.
 */
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

uint16_t get_index(char c)
{
    return (c <= '9') ? (c - '0')
         : (c <= 'Z') ? (10 + c - 'A')
         : (36 + c - 'a');
}

bool find(const string &s, const string &w, const char rep[62],
            string &ew, vector<uint16_t> &lengths)
{
    ew.clear();
    ew.push_back(rep[get_index(w[0])]);
    lengths.clear();
    lengths.push_back(0);   // mapping ew[:1] to ew[:0]

    uint32_t i = 0;
    uint16_t j = 0;
    for (; i < s.size() && j < w.size(); i++) {
        if (j >= ew.size()) {
            ew.push_back(rep[get_index(w[j])]);

            // matching against itself
            uint16_t len = lengths[j - 1];
            while (len > 0 && ew[len] != ew[j])
                len = lengths[len - 1];
            lengths.push_back(ew[len] == ew[j] ? len + 1 : 0);
        }

        while (j > 0 && s[i] != ew[j])
            j = lengths[j - 1];
        if (s[i] == ew[j])
            j++;
    }

    if (j < w.size())
        return false;
    else {
        // second match
        j = lengths[j - 1];
        for (; i < s.size() && j < w.size(); i++) {
            while (j > 0 && s[i] != ew[j])
                j = lengths[j - 1];
            if (s[i] == ew[j])
                j++;
        }
        return j < w.size();
    }
}

int main()
{
    uint32_t n;
    string a, w, s;
    char rep[62];   // replacements
    string ew;      // encrypted word
    vector<uint16_t> lengths;
    vector<uint16_t> solutions;

    ew.reserve(50000);
    lengths.reserve(50000);

    for (cin >> n; n > 0 && cin >> a >> w >> s; n--) {
        solutions.clear();
        ew.clear();
        lengths.resize(w.size());
        for (uint8_t shift = 0; shift < a.size(); shift++) {
            for (size_t i = 0; i < a.size(); i++)
                rep[get_index(a[i])] = a[(i + shift) % a.size()];

            if (find(s, w, rep, ew, lengths))
                solutions.push_back(shift);
        }

        uint16_t count = solutions.size();
        if (count == 0)
            cout << "no solution" << endl;
        else if (count == 1)
            cout << "unique: " << solutions.front() <<endl;
        else {
            cout << "ambiguous:";
            for (auto s: solutions)
                cout << " " << s;
            cout << endl;
        }
    }

    return 0;
}
