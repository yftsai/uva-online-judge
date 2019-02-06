// #easy
#include <iostream>
#include <limits>
#include <algorithm>
using namespace std;

int main()
{
    for (uint16_t n; cin >> n && n > 0; ) {
        int max_streak = numeric_limits<int>::min(), streak = 0, bet;
        for (uint16_t i = 0; i < n && cin >> bet; ++i) {
            streak = (streak <= 0) ? bet : (streak + bet);
            max_streak = max(max_streak, streak);
        }
        if (max_streak <= 0)
            cout << "Losing streak." << endl;
        else
            cout << "The maximum winning streak is " << max_streak << "." << endl;
    }
    return 0;
}
