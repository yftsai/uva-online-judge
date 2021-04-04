// #search
#include <iostream>
#include <array>
#include <bitset>
#include <string>
#include <queue>
#include <set>
using namespace std;

struct die
{
    bitset<6> faces;

    enum face { TOP, BOTTOM, NORTH, SOUTH, EAST, WEST };
    void enter(face f) { faces.set(f); }
    void leave(face f)  { faces.reset(f); }
    void roll(const char dir);

    bool is_occupied(face f) const      { return faces[f]; }
    bool operator!=(const die &d) const { return faces.to_ulong() != d.faces.to_ulong(); }
    bool operator<(const die &d) const  { return faces.to_ulong() < d.faces.to_ulong(); }
};

void die::roll(const char dir)
{
    array<uint16_t, 6> sources;
    switch (dir)
    {
        case 'n':
            sources = { SOUTH, NORTH, TOP, BOTTOM, EAST, WEST };
            break;
        case 'e':
            sources = { WEST, EAST, NORTH, SOUTH, TOP, BOTTOM };
            break;
        case 'w':
            sources = { EAST, WEST, NORTH, SOUTH, BOTTOM, TOP };
            break;
        default:
            sources = { NORTH, SOUTH, BOTTOM, TOP, EAST, WEST };
            break;
    }

    bitset<6> next_faces;
    for (uint16_t i = 0; i < 6; i++)
        next_faces[i] = faces[ sources[i] ];
    faces = next_faces;
}

struct state
{
    uint16_t t_count;           // count of fleas on tiles
    array<uint16_t, 6> tiles;
    uint16_t dpos;
    die d;

    state(): t_count(0) {}

    static uint16_t encode(uint16_t r, uint16_t c)      { return (r << 8) + c; }
    static pair<int16_t, int16_t> decode(uint16_t p)    { return pair<int16_t, int16_t>(p >> 8, p & 0xF); }

    void enter(uint16_t p);
    void leave(uint16_t p);
    bool is_flea_on(uint16_t p) const;
    state roll(char dir) const;

    bool operator<(const state &s) const;

    uint32_t estimate_step_count() const;
};

void state::enter(uint16_t p)
{
    tiles[t_count++] = p;
    for (uint16_t i = t_count - 1u; i > 0 && tiles[i - 1] >= tiles[i];  i--)
        swap(tiles[i - 1], tiles[i]);
}

void state::leave(uint16_t p)
{
    uint16_t i = 0;
    for (; i < t_count && tiles[i] != p; i++)
        ;
    for (; i + 1 < t_count; i++)
        tiles[i] = tiles[i + 1];
    t_count--;
}

bool state::is_flea_on(uint16_t p) const
{
    for (uint16_t i = 0; i < t_count; ++i)
        if (tiles[i] == p)
            return true;
    return false;
}

state state::roll(char dir) const
{
    auto next_dpos = decode(dpos);
    die next_d = d;
    switch (dir)
    {
        case 'n':
            next_dpos.first--;
            next_d.roll(dir);
            break;
        case 'e':
            next_dpos.second--;
            next_d.roll(dir);
            break;
        case 'w':
            next_dpos.second++;
            next_d.roll(dir);
            break;
        default:
            next_dpos.first++;
            next_d.roll(dir);
            break;
    }

    if (next_dpos.first < 0 || next_dpos.first >= 4
        || next_dpos.second < 0 || next_dpos.second >= 4)
        return *this;
    else {
        const auto p = encode(next_dpos.first, next_dpos.second);
        state s = *this;
        s.dpos = p;
        s.d = next_d;

        if (is_flea_on(p) && !next_d.is_occupied(die::BOTTOM)) {
            s.leave(p);
            s.d.enter(die::BOTTOM);
        }
        else if (!is_flea_on(p) && next_d.is_occupied(die::BOTTOM)) {
            s.enter(p);
            s.d.leave(die::BOTTOM);
        }

        return s;
    }
}

bool state::operator<(const state &s) const
{
    if (t_count != s.t_count)
        return t_count < s.t_count;
    else if (dpos != s.dpos)
        return dpos < s.dpos;
    else if (d != s.d)
        return d < s.d;
    else
        for (uint16_t i = 0; i < t_count; i++)
            if (tiles[i] != s.tiles[i])
                return tiles[i] < s.tiles[i];
    return false;
}

uint32_t state::estimate_step_count() const
{
    const auto p = decode(dpos);
    pair<uint16_t, uint16_t> xs(p.first, p.first), ys(p.second, p.second);
    for (uint16_t i = 0; i < t_count; i++) {
        const auto q = decode(tiles[i]);
        xs = make_pair(min<uint16_t>(xs.first, q.first),  max<uint16_t>(xs.second, q.first));
        ys = make_pair(min<uint16_t>(ys.first, q.second), max<uint16_t>(ys.second, q.second));
    }
    return max<uint32_t>(t_count, xs.second - xs.first + ys.second - ys.first);
}

struct task
{
    state s;
    int32_t step_count;
    int32_t min_step_count;

    task(state s, uint32_t sc):
        s(s),
        step_count(sc)
    {
        min_step_count = step_count + s.estimate_step_count();
    }

    bool operator<(const task &t) const
    {
        if (min_step_count != t.min_step_count)
            return min_step_count > t.min_step_count;
        else
            return step_count < t.step_count;
    }
};

int main()
{
    uint32_t test_count;
    string line;
    priority_queue<task> pq;
    set<state> states;

    for (cin >> test_count; test_count > 0; test_count--) {
        state s;
        for (uint16_t r = 0; r < 4 && cin >> line; r++)
            for (uint16_t c = 0; c < 4; c++)
                if (line[c] == 'X')
                    s.enter(state::encode(r, c));
                else if (line[c] == 'D')
                    s.dpos = state::encode(r, c);

        states.insert(s);
        pq.push(task(s, 0));
        while (pq.size() > 0 && pq.top().s.t_count > 0) {
            const task t = pq.top();
            pq.pop();

            for (char d: {'n', 'e', 'w', 's'}) {
                const auto s = t.s.roll(d);
                auto it = states.find(s);
                if (it == states.end()) {
                    states.insert(it, s);
                    pq.push(task(s, t.step_count + 1));
                }
            }
        }

        if (pq.size() > 0 && pq.top().s.t_count == 0)
            cout << pq.top().step_count << endl;
        else
            cout << "impossible" << endl;

        states.clear();
        while (pq.size() > 0)
            pq.pop();
    }

    return 0;
}
