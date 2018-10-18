#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <limits>
#include <iomanip>
using namespace std;

uint32_t encode(uint16_t x, uint16_t y)
{
    uint32_t e = 0;
    for (uint16_t m = 1 << 9; m > 0; m >>= 1) {
        e <<= 2;
        if (x & m)
            e |= 2;
        if (y & m)
            e |= 1;
    }
    return e;
}

typedef struct {
    uint32_t key;
    uint16_t x, y;
} point;

bool operator<(const point &p, const point &q)
{
    return p.key < q.key;
}

void match(const point *points, int count, bool *is_matched, double *min_distance, int index = 0, double d = 0)
{
    if (d <= *min_distance) {
        int i = find(is_matched + index, is_matched + count, false) - is_matched;
        if (i >= count)
            *min_distance = d;
        else {
            is_matched[i] = true;
            for (int j = i + 1; j < count; j++)
                if (!is_matched[j]) {
                    is_matched[j] = true;
                    double e = sqrt(pow(points[i].x - points[j].x, 2) + pow(points[i].y - points[j].y, 2));
                    match(points, count, is_matched, min_distance, index + 1, d + e);
                    is_matched[j] = false;
                }
            is_matched[i] = false;
        }
    }
}

int main()
{
    bool is_matched[16];
    string name;
    for (int n, case_number = 1; cin >> n && n != 0; case_number++) {
        point points[2 * n];
        for (int i = 0; i < 2 * n && cin >> name >> points[i].x >> points[i].y; i++)
            points[i].key = encode(points[i].x, points[i].y);
        sort(points, points + 2 * n);

        double distance = numeric_limits<double>::max();
        fill(is_matched, is_matched + 2 * n, false);
        match(points, 2 * n, is_matched, &distance);

        cout << "Case " << case_number << ": " << fixed << setprecision(2) << distance << endl;
    }
    return 0;
}
