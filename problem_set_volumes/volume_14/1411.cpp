// #divide_and_conquer
#include <iostream>
#include <algorithm>
using namespace std;

typedef struct
{
    int x, y, n;
} point;

void match(int colony_count, point *points, int point_count, int *matched_trees)
{
    if (point_count <= 0)
        ;
    else {
        for (int i = 1; i < point_count; i++)
            if (points[i].y < points[0].y || (points[i].y == points[0].y && points[i].x < points[i].x))
                swap(points[i], points[0]);
        auto less = [&] (const point &p, const point &q) {
            return (p.x - points[0].x) * (q.y - points[0].y) < (p.y - points[0].y) * (q.x - points[0].x);
        };
        sort(points + 1, points + point_count, less);
        int p = 0, c_count = 0, t_count = 0;
        for (int i = 1; i < point_count; i++) {
            if ((points[i].n < colony_count) != (points[0].n < colony_count) && c_count == t_count)
                if (abs(i - point_count / 2) < abs(p - point_count / 2))
                    p = i;
            (points[i].n < colony_count ? c_count : t_count)++;
        }
        if (points[0].n < colony_count)
            matched_trees[ points[0].n ] = points[p].n;
        else
            matched_trees[ points[p].n ] = points[0].n;
        match(colony_count, points + 1, p - 1, matched_trees);
        match(colony_count, points + p + 1, point_count - p - 1, matched_trees);
    }
}

int main()
{
    bool is_first = true;
    for (int n; cin >> n; is_first = false) {
        point points[2 * n];
        for (int i = 0; i < n * 2; i++) {
            cin >> points[i].x >> points[i].y;
            points[i].n = i;
        }

        int trees[n];
        match(n, points, 2 * n, trees);

        if (!is_first)
            cout << endl;
        for (int t: trees)
            cout << (t - n + 1) << endl;
    }
    return 0;
}
