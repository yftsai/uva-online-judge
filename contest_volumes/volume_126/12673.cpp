// #easy
#include <iostream>
using namespace std;

int main()
{
    for (uint32_t n, g; cin >> n >> g; ) {  // n could be greater than 100,000
        uint32_t points = 0, drawn = 0;
        uint32_t lost_counts[101] = { 0 };
        for (uint32_t i = 0, s, r; i < n && cin >> s >> r; i++)
            if (s > r)
                points += 3;
            else if (s < r)
                lost_counts[r - s]++;
            else {
                points += 1;
                drawn++;
            }

        uint32_t c = min(drawn, g);
        g -= c;
        points += 2 * c;

        for (uint16_t i = 1; i <= 100 && g >= i; i++)
            if (lost_counts[i] > 0) {
                c = min(lost_counts[i], g / (i + 1));
                g -= (i + 1) * c;
                points += 3 * c;

                if (c < lost_counts[i] && g == i) {
                    g = 0;
                    points += 1;
                }
            }

        cout << points << endl;
    }

    return 0;
}
