// #minimum_spanning_tree
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef pair<double, double> point;

double operator-(const point &p, const point &q)
{
    return sqrt(pow(p.first - q.first, 2) + pow(p.second - q.second, 2));
}

int main()
{
    cout.setf(ios::showpoint | ios::fixed);
    cout.precision(2);

    int cases, n;
    for (cin >> cases; cases>0; cases--){
        cin >> n;

        point tree_node, p;
        vector<pair<point, double>> points(n-1);
        cin >> tree_node.first >> tree_node.second;
        for (auto &p: points) {
            cin >> p.first.first >> p.first.second;
            p.second = (p.first - tree_node);
        }

        // Prim's algorithm
        double length=0;
        while (!points.empty()) {
            for (size_t i=0; i < points.size()-1; ++i)
                if (points[i].second < points.back().second)
                    swap(points[i], points.back());

            tree_node = points.back().first;
            length += points.back().second;

            points.pop_back();
            for (auto &p: points)
                p.second = min(p.second, p.first - tree_node);
        }

        cout << length << endl;
        if (cases > 1)
            cout << endl;
    }

    return 0;
}
