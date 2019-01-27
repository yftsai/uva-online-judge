// #greedy
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int main()
{
    vector<int> morning_hours, evening_hours;
    for (int n, d, r; cin >> n >> d >> r && n > 0; ) {
        morning_hours.resize(n);
        for (int &h: morning_hours)
            cin >> h;
        sort(morning_hours.begin(), morning_hours.end());

        evening_hours.resize(n);
        for (int &h: evening_hours)
            cin >> h;
        sort(evening_hours.begin(), evening_hours.end(), std::greater<int>());

        int amount = 0;
        for (auto mit = morning_hours.begin(), eit = evening_hours.begin(); mit != morning_hours.end(); ++mit, ++eit)
            if (*mit + *eit > d)
                amount += *mit + *eit - d;
        cout << (r * amount) << endl;
    }
    return 0;
}
