#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

typedef pair<int, int> point;

double sunny_distance(point p1, point p2, int h)
{
    if (p1.second<= h)
        return 0;
    else {
        double mx = p2.first + 1.0*(p1.first-p2.first)/(p1.second-p2.second)*(h-p2.second);
        double my = h;
       
        return (p1.first >= mx) ? 0 : sqrt(pow(mx-p1.first, 2) + pow(my-p1.second, 2));
    }
}

int main()
{
    int c, n;
    for (cin >> c; c>0; c--){
        vector<point> landscape;
        for (cin >> n; n>0; n--){
            int x, y;
            cin >> x >> y;
            landscape.push_back(pair<int, int>(x, y));
        }
        sort(landscape.begin(), landscape.end());

        double sdis = 0;
        int h = 0;

        for (vector<point>::const_reverse_iterator it = landscape.rbegin()+1; it != landscape.rend(); ++it){
            sdis += sunny_distance(*it, *(it-1), h);
            h = max(h, it->second);
            h = max(h, (it-1)->second);
        }
        cout << setprecision(2) << fixed << sdis << endl;
    }

    return 0;
}
