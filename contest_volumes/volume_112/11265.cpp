// #convex_hull
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

constexpr double eps = 1E-9;

typedef struct{
    double x, y;
} point;

// The function, a * x + b * y + c = 0, is stored to avoid imprecision increase.
typedef struct {
    int a, b;
    int64_t c;
    point end;
} edge;

typedef vector<edge> polygon;

double evaluate(int a, double x, int b, double y, int64_t c)    { return a * x + b * y + c; }

point solve(int64_t a1, int b1, int64_t c1, int64_t a2, int b2, int64_t c2)
{
    double x = double(-c1 * b2 + c2 * b1) / (a1 * b2 - a2 * b1);
    double y = double(-c1 * a2 + c2 * a1) / (b1 * a2 - b2 * a1);
    return point({x, y});
}

void cut(int a, int b, int64_t c, polygon *p)
{
    polygon temp;
    double begin = evaluate(a, p->back().end.x, b, p->back().end.y, c), end;
    for (const edge &e: *p) {
        end = evaluate(a, e.end.x, b, e.end.y, c);
        if (begin > eps && end >= -eps)
            temp.push_back(e);
        else if (begin > eps)
            temp.push_back(edge({e.a, e.b, e.c, solve(e.a, e.b, e.c, a, b, c)}));
        else if (begin >= -eps && end >= -eps)
            temp.push_back(e);
        else if (begin >= -eps)
            ;
        else if (end > eps) {
            temp.push_back(edge({a, b, c, solve(a, b, c, e.a, e.b, e.c)}));
            temp.push_back(e);
        }
        else if (end >= -eps)
            temp.push_back(edge({a, b, c, solve(a, b, c, e.a, e.b, e.c)}));
        begin = end;
    }
    p->swap(temp);
}

double get_area(const polygon &p)
{
    double area = p.back().end.x * p.front().end.y - p.back().end.y * p.front().end.x;
    for (size_t i = 0; i < p.size() - 1; i++)
        area += p[i].end.x * p[i + 1].end.y - p[i].end.y * p[i + 1].end.x;
    return area / 2;
}

int main()
{
    for (int case_number = 1, n, w, h, x, y; cin >> n >> w >> h >> x >> y; case_number++) {
        polygon p = {
            {1, 0, 0,   { 0,        0} },
            {0, 1, 0,   { 1.0 * w,  0} },
            {1, 0, -w,  { 1.0 * w,  1.0 * h} },
            {0, 1, -h,  { 0,        1.0 * h} } };
        for (int x1, y1, x2, y2; n > 0 && cin >> x1 >> y1 >> x2 >> y2; n--) {
            const int a = (y2 - y1), b = (x1 - x2);
            const int64_t c = -int64_t(a) * x1 - int64_t(b) * y1;
            if (evaluate(a, x, b, y, c) < eps)
                cut(-a, -b, -c, &p);
            else
                cut(a, b, c, &p);
        }
        cout << "Case #" << case_number << ": " << fixed << setprecision(3) << get_area(p) << endl;
    }
    return 0;
}
