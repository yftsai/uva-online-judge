// #geometry
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

struct pole
{
    int x;
    int16_t y, z;

    double t;
};

bool by_angle_distance(const pole &p, const pole &q)
{
    if (p.t != q.t)
        return p.t < q.t;
    else if (p.y != 0)
        return p.y < q.y;
    else if (p.x < 0)
        return p.x > q.x;
    else
        return p.x < q.x;
}

bool by_coordinate(const pole &p, const pole &q)
{
    if (p.x != q.x)
        return p.x < q.x;
    else
        return p.y < q.y;
}

int main()
{
    vector<pole> poles(100 * 1000);

    for (int data_set_number = 1, n; cin >> n && n > 0; ++data_set_number) {
        poles.resize(n);

        for (pole &p: poles) {
            cin >> p.x >> p.y >> p.z;
            if (p.x == 0)
                p.t = INFINITY;
            else if (p.y == 0)
                p.t = (p.x < 0) ? (-0.001 * 0.001) : (0.001 * 0.001);
            else
                p.t = double(p.y) / p.x;
        }
        sort(poles.begin(), poles.end(), by_angle_distance);

        size_t count = 0;
        for (uint32_t i = 0; i < poles.size(); ) {
            pole p = poles[i++];
            for (; i < poles.size() && poles[i].t == p.t; ++i)
                if (p.z >= poles[i].z)
                    poles[count++] = poles[i];
                else
                    p.z = poles[i].z;
        }
        poles.resize(count);

        cout << "Data set " << data_set_number << ":" << endl;
        if (poles.empty())
            cout << "All the lights are visible." << endl;
        else {
            sort(poles.begin(), poles.end(), by_coordinate);
            cout << "Some lights are not visible:" << endl;
            for (uint32_t i = 0; i < count; ++i)
                cout << "x = " << poles[i].x
                     << ", y = " << poles[i].y
                     << ((i != count - 1u) ? ';' : '.')
                     << endl;
        }
    }

    return 0;
}
