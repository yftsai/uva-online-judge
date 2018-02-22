// #artuculation_point #depth_first_search
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

int dfs(vector<set<int>> &graph, vector<int> &orders, int &order, int index, set<int> &articulations)
{
    int min_order = orders[index] = order++;

    for (auto it = graph[index].begin(); it != graph[index].end(); ) {
        graph[*it].erase(index);
        if (orders[*it] == INT_MAX) {
            int m = dfs(graph, orders, order, *it, articulations);
            if (m >= orders[index])
                articulations.insert(index);
            else
                min_order = min(min_order, m);
            ++it;
        }
        else {
            min_order = min(min_order, orders[*it]);
            it = graph[index].erase(it);
        }
    }

    return min_order;
}

int main()
{
    for (int n, r, map_count = 0; cin >> n && n != 0; map_count++) {
        vector<string> places(n);
        for (auto &place: places)
            cin >> place;
        sort(places.begin(), places.end());

        vector<set<int>> graph(n);
        cin >> r;
        string route[2];
        for (int i = 0; i < r && cin >> route[0] >> route[1]; i++) {
            int j = lower_bound(places.begin(), places.end(), route[0]) - places.begin();
            int k = lower_bound(places.begin(), places.end(), route[1]) - places.begin();
            graph[j].insert(k);
            graph[k].insert(j);
        }

        vector<int> orders(n, INT_MAX);
        set<int> articulations;
        for (int i = 0, order = 0; i < n; i++)
            if (orders[i] == INT_MAX) {
                dfs(graph, orders, order, i, articulations);
                if (graph[i].size() < 2)
                    articulations.erase(i);
            }

        if (map_count > 0)
            cout << endl;
        cout << "City map #" << (map_count + 1) << ": " << articulations.size() << " camera(s) found" << endl;
        for (int a: articulations)
            cout << places[a] << endl;
    }

    return 0;
}
