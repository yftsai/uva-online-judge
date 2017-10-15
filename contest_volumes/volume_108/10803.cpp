// #shortest_path
#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
using namespace std;

int main()
{
    constexpr double unreachable = numeric_limits<double>::max() / 4;
    cout << fixed << setprecision(4);

    int case_count, n;
    cin >> case_count;
    for (int case_number = 1; case_number <= case_count; case_number++) {
        cin >> n;
        double distances[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                distances[i][j] = unreachable;
        int locations[n][2];
        for (int i = 0; i < n && cin >> locations[i][0] >> locations[i][1]; i++)
            for (int j = 0; j < i; j++) {
                double d = sqrt(pow(locations[i][0] - locations[j][0], 2) + pow(locations[i][1] - locations[j][1], 2));
                if (d <= 10)
                    distances[i][j] = distances[j][i] = d;
            }
        for (int m = 0; m < n; m++)
           for (int i = 0; i < n; i++)
               for (int j = 0; j < n; j++)
                    distances[i][j] = min(distances[i][j], distances[i][m] + distances[m][j]);
        double d = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                d = max(d, distances[i][j]);

        cout << "Case #" << case_number << ":" << endl;
        if (d == unreachable)
            cout << "Send Kurdy" << endl;
        else
            cout << d << endl;
        cout << endl;
    }
    return 0;
}
