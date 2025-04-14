// #geometry
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

struct grid_vector
{
    static constexpr int32_t limit = 32767;
    static vector<int32_t> starts;

    int16_t r;      // row
    int16_t h;      // horizontal

    grid_vector(int16_t rval = 0, int16_t hval = 0):
        r(rval),
        h(hval) {}

    bool is_valid() const   { return r != 0 || h != 0; }
    uint16_t length() const { return r == 0 ? abs(h) : abs(r); }

    static void init();
    static grid_vector from(int32_t p, int32_t q);
};

vector<int32_t> grid_vector::starts;

void grid_vector::init()
{
    grid_vector::starts.push_back(1);
    for (int32_t r = 1; grid_vector::starts.back() + r <= grid_vector::limit; r++)
        grid_vector::starts.push_back(grid_vector::starts.back() + r);
}

grid_vector grid_vector::from(int32_t p, int32_t q)
{
    auto sp = --upper_bound(starts.begin(), starts.end(), p);
    int16_t rp = sp - starts.begin();

    auto sq = --upper_bound(starts.begin(), starts.end(), q);
    int16_t rq = sq - starts.begin();

    if (rp == rq)
        return grid_vector(0, q - p);

    int32_t a = p + *sq - *sp;  // project `p` onto row q as `a` and `b`
    int32_t b = a + rq - rp;

    if (*sq <= a && a <= *sq + rq && q == a)
        return grid_vector(rq - rp, 0);
    else if (*sq <= b && b <= *sq + rq && q == b)
        return grid_vector(rq - rp, rq - rp);
    else
        return grid_vector(0, 0);
}

bool is_distinct(const vector<int32_t> &points)
{
    for (uint16_t i = 0; i < points.size(); i++)
        for (uint16_t j = i + 1; j < points.size(); j++)
            if (points[i] == points[j])
                return false;
    return true;
}

bool is_triangle(const vector<int32_t> &points)
{
    if (points.size() != 3 || !is_distinct(points))
        return false;

    grid_vector gvs[3];
    for (uint16_t i = 0; i < 3; i++) {
        gvs[i] = grid_vector::from(points[i], points[(i + 1) % 3]);
        if (!gvs[i].is_valid())
            return false;
    }

    uint16_t length = gvs[0].length();
    return gvs[0].r + gvs[1].r + gvs[2].r == 0
        && gvs[0].h + gvs[1].h + gvs[2].h == 0
        && gvs[1].length() == length
        && gvs[2].length() == length;
}

bool is_parallelogram(vector<int32_t> &points)
{
    if (points.size() != 4 || !is_distinct(points))
        return false;

    sort(points.begin(), points.end());
    swap(points[2], points[3]);

    grid_vector gvs[4];
    for (uint16_t i = 0; i < 4; i++) {
        gvs[i] = grid_vector::from(points[i], points[(i + 1) % 4]);
        if (!gvs[i].is_valid())
            return false;
    }

    uint16_t length = gvs[0].length();
    return gvs[0].r == -gvs[2].r && gvs[0].h == -gvs[2].h
        && gvs[1].r == -gvs[3].r && gvs[1].h == -gvs[3].h
        && gvs[1].length() == length;
}

bool is_hexagon(vector<int32_t> &points)
{
    if (points.size() != 6 || !is_distinct(points))
        return false;

    sort(points.begin(), points.end());
    swap(points[2], points[3]);
    swap(points[3], points[5]);

    grid_vector gvs[6];
    for (uint16_t i = 0; i < 6; i++) {
        gvs[i] = grid_vector::from(points[i], points[(i + 1) % 6]);
        if (!gvs[i].is_valid())
            return false;
    }

    int16_t len = gvs[0].length();
    return gvs[0].r == 0    && gvs[0].h == len
        && gvs[1].r == len  && gvs[1].h == len
        && gvs[2].r == len  && gvs[2].h == 0
        && gvs[3].r == 0    && gvs[3].h == -len
        && gvs[4].r == -len && gvs[4].h == -len
        && gvs[5].r == -len && gvs[5].h == 0;
}

int main()
{
    string line;
    vector<int32_t> points;

    grid_vector::init();

    while (getline(cin, line)) {
        stringstream ss(line);
        points.clear();
        for (int32_t p; ss >> p; )
            points.push_back(p);

        for (auto p: points)
            cout << p << " ";
        if (is_triangle(points))
            cout << "are the vertices of a triangle" << endl;
        else if (is_parallelogram(points))
            cout << "are the vertices of a parallelogram" << endl;
        else if (is_hexagon(points))
            cout << "are the vertices of a hexagon" << endl;
        else
            cout << "are not the vertices of an acceptable figure" << endl;
    }

    return 0;
}
