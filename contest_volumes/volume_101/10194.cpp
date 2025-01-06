// #easy
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

struct team_t
{
    string name;
    uint16_t points;

    uint16_t wins;
    uint16_t ties;
    uint16_t losses;

    uint16_t goals;
    uint16_t goals_against;
    int16_t goal_diff;

    uint16_t games;

    string key;

    void init();
    bool operator<(const team_t &) const;
};

void team_t::init()
{
    points = 0;
    wins = ties = losses = 0;
    goals = goals_against = 0;
    goal_diff = 0;
    games = 0;

    key.resize(name.size());
    transform(name.begin(), name.end(), key.begin(),
        [](char c) { return tolower(c); });
}

bool team_t::operator<(const team_t &t) const
{
    if (points != t.points)
        return points > t.points;
    else if (wins != t.wins)
        return wins > t.wins;
    else if (goal_diff != t.goal_diff)
        return goal_diff > t.goal_diff;
    else if (goals != t.goals)
        return goals > t.goals;
    else if (games < t.games)
        return games < t.games;
    else
        return key < t.key;
}

int main()
{
    string line;
    vector<team_t> teams;
    unordered_map<string, uint16_t> indexes;

    getline(cin, line);
    for (uint16_t n = stoi(line); n > 0 && getline(cin, line); n--) {
        cout << line << endl;

        getline(cin, line);
        uint16_t t = stoi(line);
        indexes.clear();
        teams.resize(t);
        for (uint16_t i = 0; i < t && getline(cin, teams[i].name); i++) {
            indexes[teams[i].name] = i;
            teams[i].init();
        }

        getline(cin, line);
        for (uint16_t g = stoi(line); g > 0 && getline(cin, line); g--) {
            auto b = line.find('#');
            uint16_t t1 = indexes[line.substr(0, b)];
            auto e = line.find('@', b + 1);
            uint16_t g1 = stoi(line.substr(b + 1, e - b - 1));
            b = e + 1;
            e = line.find('#', b + 1);
            uint16_t g2 = stoi(line.substr(b, e - b));
            uint16_t t2 = indexes[line.substr(e + 1)];

            teams[t1].games++;
            teams[t1].goals += g1;
            teams[t1].goals_against += g2;
            teams[t1].goal_diff += g1;
            teams[t1].goal_diff -= g2;

            teams[t2].games++;
            teams[t2].goals += g2;
            teams[t2].goals_against += g1;
            teams[t2].goal_diff -= g1;
            teams[t2].goal_diff += g2;

            if (g1 > g2) {
                teams[t1].points += 3;
                teams[t1].wins++;
                teams[t2].losses++;
            }
            else if (g1 == g2) {
                teams[t1].points += 1;
                teams[t1].ties++;
                teams[t2].points += 1;
                teams[t2].ties++;
            }
            else {
                teams[t1].losses++;
                teams[t2].points += 3;
                teams[t2].wins++;
            }
        }

        sort(teams.begin(), teams.end());

        for (uint16_t i = 0; i < t; i++) {
            cout << (i + 1) << ") " << teams[i].name
                << " " << teams[i].points << "p, "
                << teams[i].games << "g ("
                << teams[i].wins << "-" << teams[i].ties << "-" << teams[i].losses << "), "
                << teams[i].goal_diff << "gd ("
                << teams[i].goals << "-" << teams[i].goals_against << ")"
                << endl;
        }

        if (n > 1) cout << endl;
    }

    return 0;
}
