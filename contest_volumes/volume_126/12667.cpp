// #trivial
#include <iostream>
#include <bitset>
using namespace std;

int main()
{
    struct
    {
        bitset<100> teams;
        int16_t time, team;
    } problems[12];

    uint16_t n, t, m;
    uint16_t time, team;
    char problem, verdict[8];
    for (cin >> n >> t >> m; m > 0 && cin >> time >> team >> problem >> verdict; m--) {
        auto &p = problems[problem - 'A'];
        if (verdict[0] == 'Y' && !p.teams[team - 1]) {
            p.teams.set(team - 1);
            p.team = team;
            p.time = time;
        }
    }

    for (uint16_t i = 0; i < n; i++) {
        const auto &p = problems[i];

        cout << char('A' + i);
        if (p.teams.any())
            cout << " " << p.time << " " << p.team;
        else
            cout << " - -";
        cout << endl;
    }

    return 0;
}
