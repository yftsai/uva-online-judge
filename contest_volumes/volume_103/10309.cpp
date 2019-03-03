// #backtracking
#include <iostream>
#include <array>
#include <algorithm>
using namespace std;

constexpr uint16_t n = 10;
typedef array<array<bool, n>, n> grid;

void press(uint8_t r, uint8_t c, grid &lights)
{
    lights[r][c] = !lights[r][c];
    if (r > 0)
        lights[r - 1u][c] = !lights[r - 1u][c];
    if (r + 1u < lights.size())
        lights[r + 1u][c] = !lights[r + 1u][c];
    if (c > 0)
        lights[r][c - 1u] = !lights[r][c - 1u];
    if (c + 1u < lights[r].size())
        lights[r][c + 1u] = !lights[r][c + 1u];
}

int16_t turn_off(const array<pair<uint8_t, uint8_t>, n * n> &positions, uint8_t index, uint16_t count, grid &lights)
{
    int16_t min_count = lights.size() * lights[0].size() + 1;
    if (index < positions.size()) {
        auto r = positions[index].first, c = positions[index].second;
        if ((c == 0 || !lights[r][c - 1u])
            && (c + 1u < lights[index].size() || r == 0 || !lights[r - 1u][c]))
            min_count = min(min_count, turn_off(positions, index + 1u, count, lights));
        press(positions[index].first, positions[index].second, lights);
        if ((c == 0 || !lights[r][c - 1u])
            && (c + 1u < lights[index].size() || r == 0 || !lights[r - 1u][c]))
            min_count = min(min_count, turn_off(positions, index + 1u, count + 1u, lights));
        press(positions[index].first, positions[index].second, lights);
    }
    else {
        auto r = positions.back().first, c = positions.back().second;
        if (!lights[r][c] && !lights[r][c - 1])
            min_count = count;
    }

    return min_count;
}

int main()
{
    array<pair<uint8_t, uint8_t>, n * n> positions;
    for (uint8_t r = 0; r < n; ++r)
        for (uint8_t c = 0; c < n; ++c)
            positions[n * r + c] = pair<uint8_t, uint8_t>(r, c);
    auto comparer = [](const pair<uint8_t, uint8_t> &p, const pair<uint8_t, uint8_t> &q) {
        if (p.first + p.second != q.first + q.second)
            return p.first + p.second < q.first + q.second;
        else
            return p.second < q.second;
    };
    sort(positions.begin(), positions.end(), comparer);

    grid lights;
    for (string name, line; cin >> name && name != "end"; ) {
        for (uint8_t r = 0; r < lights.size() && cin >> line; ++r)
            for (uint8_t c = 0; c < line.size() && c < lights[r].size(); ++c)
                lights[r][c] = (line[c] == 'O');
        int16_t press_count = turn_off(positions, 0, 0, lights);
        cout << name << " " << ((press_count <= int16_t(lights.size() * lights[0].size())) ? press_count : -1) << endl;
    }

    return 0;
}
