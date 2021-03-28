// #shortest_path
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <limits>
#include <algorithm>
using namespace std;

typedef pair<int16_t, int16_t> position;

struct state
{
    position bpos;
    position spos;

    bool operator<(const state &s) const
    {
        if (bpos != s.bpos)
            return bpos < s.bpos;
        else
            return spos < s.spos;
    }
};

struct path_score
{
    uint32_t push_count;
    uint32_t walk_count;

    static const path_score unvisited;

    bool operator<(const path_score &s) const
    {
        if (push_count != s.push_count)
            return push_count < s.push_count;
        else
            return push_count + walk_count < s.push_count + s.walk_count;
    }
};

typedef pair<path_score, state> path;       // intermediate state, ranked by its score

const path_score path_score::unvisited = { numeric_limits<uint32_t>::max(), numeric_limits<uint32_t>::max() };

static const char *walk_codes = "nswe";
static const char *push_codes = "NSWE";

typedef pair<int8_t, int8_t> direction;
static const direction dirs[4] = {
    direction(-1,  0),
    direction( 1,  0),
    direction( 0, -1),
    direction( 0,  1)
};

typedef pair<path_score, char> path_info;   // optimized path, reconstructable by the last char

position move(const position &p, const direction d)
{
    return position(p.first + d.first, p.second + d.second);
}

direction reverse(const direction d)
{
    return direction(-d.first, -d.second);
}

uint16_t get_index(const uint16_t c, const position p)
{
    return c * p.first + p.second;
}

path_info &get(const uint16_t c, const state &s, vector<vector<path_info>> &path_infos)
{
    return path_infos[get_index(c, s.bpos)][get_index(c, s.spos)];
}

state get_shortest_path(
    const vector<string> &maze,
    const position &tpos,
    const state init,
    vector<vector<path_info>> &path_infos)
{
    const uint16_t r = maze.size();
    const uint16_t c = maze[0].size();
    auto is_in_maze = [r, c](const position p) {
        return 0 <= p.first && p.first < r && 0 <= p.second && p.second < c;
    };

    const char dummy_code = ' ';
    path_infos.resize(r * c);
    for (auto &pis: path_infos)
        pis.assign(r * c, { path_score::unvisited, dummy_code});

    set<path> pq;
    auto enqueue = [&](const state s, const path_score score, const char code) {
        path_info &pi = get(c, s, path_infos);
        if (score < pi.first) {
            pq.erase({ pi.first, s});
            pq.emplace(score, s);
            pi = { score, code };
        }
    };

    for (enqueue(init, { 0, 0 }, dummy_code); !pq.empty(); ) {
        const path p = *pq.begin();
        pq.erase(pq.begin());

        for (uint16_t i = 0; i < 4; ++i) {
            const auto &d = dirs[i];
            const auto spos = move(p.second.spos, d);

            if (is_in_maze(spos) && maze[spos.first][spos.second] != '#') {
                const auto bpos = move(p.second.bpos, d);
                if (spos != p.second.bpos) {
                    enqueue({ p.second.bpos, spos },
                            { p.first.push_count, p.first.walk_count + 1},
                            walk_codes[i]);
                }
                else if (is_in_maze(bpos) && maze[bpos.first][bpos.second] != '#') {
                    enqueue({ bpos, spos },
                            { p.first.push_count + 1, p.first.walk_count },
                            push_codes[i]);
                    if (bpos == tpos)
                        return { bpos, spos };
                }
            }
        }
    }

    return { init.bpos, init.spos };
}

int main()
{
    vector<string> maze(20);
    vector<vector<path_info>> scores;
    string path;

    uint32_t maze_number = 1;
    for (uint16_t r, c; cin >> r >> c && r != 0; ++maze_number) {
        const char *cs = "BST";
        state init;
        position tpos;
        position * const ps[3] = { &init.bpos, &init.spos, &tpos};
        maze.resize(r);
        for (uint16_t i = 0; i < r && cin >> maze[i]; ++i)
            for (uint16_t j = 0; j < c; ++j)
                for (uint16_t k = 0; k < 3; ++k)
                    if (maze[i][j] == cs[k]) {
                        *ps[k] = position(i, j);
                        maze[i][j] = '.';
                    }

        state s = get_shortest_path(maze, tpos, init, scores);

        cout << "Maze #" << maze_number << endl;
        if (s.bpos == tpos) {
            const path_score init_score = { 0, 0 };

            path.clear();
            for (path_info ps; init_score < (ps = get(c, s, scores)).first; ) {
                path.push_back(ps.second);
                for (uint16_t i = 0; i < 4; ++i)
                    if (ps.second == walk_codes[i])
                        s.spos = move(s.spos, reverse(dirs[i]));
                    else if (ps.second == push_codes[i]) {
                        s.bpos = move(s.bpos, reverse(dirs[i]));
                        s.spos = move(s.spos, reverse(dirs[i]));
                    }
            }

            reverse(path.begin(), path.end());
            cout << path << endl;
        }
        else
            cout << "Impossible." << endl;
        cout << endl;
    }

    return 0;
}
