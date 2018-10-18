// #geometry
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main()
{
    constexpr float eps = 0.000001, r = acos(-1) / 180;
    struct {
        float latitude, longitude;
        float x, y, z;
        float d;
    } airports[1000];

    cout << fixed << setprecision(2);
    for (uint16_t n; cin >> n; ) {
        for (uint16_t i = 0; i < n; i++) {
            auto &a = airports[i];
            cin >> a.latitude >> a.longitude;

            a.y = sin(a.latitude * r);
            const float xz = cos(a.latitude * r);
            a.x = xz * cos(a.longitude * r);
            a.z = xz * sin(a.longitude * r);
            a.d = 0;

            for (uint16_t j = 0; j < i; j++) {
                float d = acos(airports[j].x * a.x + airports[j].y * a.y + airports[j].z * a.z);
                airports[j].d = max(airports[j].d, d);
                a.d = max(a.d, d);
            }
        }

        uint16_t hub_index = 0;
        for (uint16_t i = 1; i < n; i++)
            if (airports[i].d < airports[hub_index].d + eps)
                hub_index = i;
        cout << airports[hub_index].latitude << " " << airports[hub_index].longitude << endl;
    }

    return 0;
}
