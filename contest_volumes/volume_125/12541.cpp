// #trivial
#include <iostream>
#include <string>
using namespace std;

struct person
{
    string name;
    uint16_t d, m, y;

    bool operator<(const person &p) const
    {
        const pair<uint16_t, uint16_t> ts[] = {
            { y, p.y },
            { m, p.m },
            { d, p.d} };
        for (const auto &tpair: ts)
            if (tpair.first != tpair.second)
                return tpair.first < tpair.second;
        return false;
    }

    friend istream &operator>>(istream &is, person &p);
};

istream &operator>>(istream &is, person &p)
{
    is >> p.name >> p.d >> p.m >> p.y;
    return is;
}

int main()
{
    uint16_t n;
    person youngest, oldest;

    cin >> n;
    cin >> youngest;
    oldest = youngest;

    for (person p; n > 1 && cin >> p; n--) {
        if (youngest < p)
            youngest = p;
        else if (p < oldest)
            oldest = p;
    }
    cout << youngest.name << endl;
    cout << oldest.name << endl;

    return 0;
}
