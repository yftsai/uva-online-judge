// #boolean_satisfiability
#include <iostream>
#include <string>
using namespace std;

bool is_triple_free(const string &p, uint8_t len)
{
    auto plen = p.begin() + len;
    for (uint8_t l = 1; l <= len/3; l++)
       if (equal(plen - l, plen, plen - l * 2) && equal(plen - l, plen, plen - l * 3))
           return false;
    return true;
}

uint32_t count(string &p, uint8_t i = 0)
{
    if (!is_triple_free(p, i))
        return 0;
    else if (i == p.size())
        return 1;
    else if (isdigit(p[i]))
        return count(p, i + 1);
    else {
        uint32_t c = 0;
        for (p[i] = '0'; p[i] <= '1'; p[i]++)
            c += count(p, i + 1);
        p[i] = '*';
        return c;
    }
}

int main()
{
    for (uint16_t n, case_number = 1; cin >> n && n != 0; case_number++) {
        string p;
        cin >> p;
        cout << "Case " << case_number << ": " << count(p) << endl;
    }
    return 0;
}
