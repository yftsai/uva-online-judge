// #shortest_path
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <limits>
using namespace std;

int main()
{
    string line;
    getline(cin, line);
    int ncases = stoi(line);
    getline(cin, line);

    for (; ncases > 0; --ncases) {
        int n_firestation, n_intersection;
        getline(cin, line);
        stringstream(line) >> n_firestation >> n_intersection;

        set<int> firestations;
        for (int i=0; i<n_firestation && getline(cin, line); ++i)
            firestations.insert(stoi(line) - 1);

        vector<vector<int>> graph(n_intersection, vector<int>(n_intersection, numeric_limits<int>::max()));
        for (int i, j, length; getline(cin, line) && stringstream(line) >> i >> j >> length; )
            graph[i-1][j-1] = graph[j-1][i-1] = length;

        for (int m=0; m<n_intersection; ++m)
            for (int s=0; s<n_intersection; ++s)
                for (int d=0; d<n_intersection; ++d)
                    if (graph[s][m] < graph[s][d] && graph[m][d] < graph[s][d])
                        graph[s][d] = min(graph[s][d], graph[s][m] + graph[m][d]);

        int min_maxd = numeric_limits<int>::max();
        int station = numeric_limits<int>::max();
        for (int s = 0; s<n_intersection; ++s) {
            int maxd = numeric_limits<int>::min();
            for (int i=0; i<n_intersection; ++i) {
                int d = (i == s || firestations.find(i) != firestations.end()) ? 0 : graph[i][s];
                for (auto j: firestations)
                    d = min(d, graph[i][j]);
                maxd = max(maxd, d);
            }
            if (maxd < min_maxd) {
                min_maxd = maxd;
                station = s;
            }
        }

        cout << (station + 1) << endl;
        if (ncases > 1)
            cout << endl;
    }

    return 0;
}
